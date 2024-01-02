#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../../tests/global.h"
#include "connectors.h"
#include "../../utils/utils.h"

char c_delim[] = ";";
int C_MAX_LENGTH = 30;

ConnectorList *load_connectors_from_preset(char *filename);
ConnectorData *process_connector_line(char *ptr);
void add_connector_list_node(ConnectorList *list, ConnectorListNode *list_node);
ConnectorData get_connector_data(ConnectorList *list, int idx);
void print_connector_list(ConnectorList *list);
void print_connector_list_node(ConnectorListNode *list_node);

ConnectorList *load_connectors_from_preset(char *filename)
{
	FILE *file = fopen(filename, "r");

	ConnectorList *c_list = malloc(sizeof(ConnectorList));
	c_list->size = 0;
	c_list->root = NULL;

	char buf[500];

	while (fgets(buf, sizeof buf, file) != NULL)
	{
		if (buf[0] == '#')
			continue;

		buf[strcspn(buf, "\n")] = '\0';

		char *ptr = strtok(buf, c_delim);

		ConnectorListNode *cln = malloc(sizeof(ConnectorListNode));
		ConnectorData *cd = process_connector_line(ptr);
		cln->connector = *cd;

		add_connector_list_node(c_list, cln);
		c_list->size++;
	}

	if (!feof(file))
		printf("an error interrupted the read \n");

	fclose(file);

	return c_list;
}

ConnectorData *process_connector_line(char *ptr)
{
	int idx = 0;

	ConnectorData *cd = malloc(sizeof(ConnectorData));

	while (ptr != NULL)
	{
		switch (idx++)
		{
		case 0:
			cd->serb = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(cd->serb, ptr);
			break;
		case 1:
			cd->word = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(cd->word, ptr);
			break;
		}

		ptr = strtok(NULL, c_delim);
	}

	return cd;
}

void add_connector_list_node(ConnectorList *list, ConnectorListNode *list_node)
{
	if (list->root == NULL)
	{
		list_node->connector.idx = 0;
		list_node->next = NULL;
		list->root = list_node;
	}
	else
	{
		ConnectorListNode *curr = list->root;
		int idx = 1;

		while (curr->next != NULL)
		{
			curr = curr->next;
			idx++;
		}

		list_node->connector.idx = idx;
		list_node->next = curr->next;
		curr->next = list_node;
	}
}

ConnectorData get_connector_data(ConnectorList *list, int idx)
{
	ConnectorListNode *curr = list->root;
	int curr_idx = 0;

	while (curr_idx++ < idx)
		curr = curr->next;

	return curr->connector;
}

void print_connector_list(ConnectorList *list)
{
	ConnectorListNode *curr = list->root;

	while (curr->next != NULL)
	{
		print_connector_list_node(curr);
		curr = curr->next;
	}

	print_connector_list_node(curr);
}

void print_connector_list_node(ConnectorListNode *list_node)
{
	int width = display_width(list_node->connector.serb);
	int field_width = C_MAX_LENGTH * 2 + 87 - width + (int)strlen(list_node->connector.serb);
	printf("\x1b[1m\x1b[44m[C] %-*s |\x1b[0m \n", field_width, list_node->connector.serb);

	printf("\t\x1b[1m\x1b[45m|   %-*s |\x1b[0m \n",
		   C_MAX_LENGTH + (int)compensation(list_node->connector.word) + 113, list_node->connector.word);

	printf("\n");
}
