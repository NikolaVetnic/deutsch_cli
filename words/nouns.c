#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nouns.h"
#include "../utils/utils.h"
#include "../tests/global.h"
#include "w_sym.h"

char n_delim[] = ";";
int N_MAX_LENGTH = 42;

NounList *load_nouns_from_preset(char *filename);
NounData *process_noun_line(char *ptr);
void add_noun_list_node(NounList *list, NounListNode *list_node);
NounData get_noun_data(NounList *list, int idx);
void print_noun_list(NounList *list);
void print_noun_list_node(NounListNode *list_node);

NounList *load_nouns_from_preset(char *filename)
{
	FILE *file = fopen(filename, "r");

	NounList *n_list = malloc(sizeof(NounList));
	n_list->size = 0;
	n_list->root = NULL;

	char buf[500];

	while (fgets(buf, sizeof buf, file) != NULL)
	{
		if (buf[0] == '#')
			continue;

		buf[strcspn(buf, "\n")] = '\0';

		char *ptr = strtok(buf, n_delim);

		NounListNode *nln = malloc(sizeof(NounListNode));
		NounData *nd = process_noun_line(ptr);
		nln->noun = *nd;

		add_noun_list_node(n_list, nln);
		n_list->size++;
	}

	if (!feof(file))
		printf("an error interrupted the read \n");

	fclose(file);

	return n_list;
}

NounData *process_noun_line(char *ptr)
{
	int idx = 0;

	NounData *nd = malloc(sizeof(NounData));

	while (ptr != NULL)
	{
		switch (idx++)
		{
		case 0:
			nd->serb = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(nd->serb, ptr);
			break;
		case 1:
			nd->art = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(nd->art, ptr);
			break;
		case 2:
			nd->sg = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(nd->sg, ptr);
			break;
		case 3:
			nd->pl = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(nd->pl, ptr);
			trim_white_space(nd->pl);
			break;
		}

		ptr = strtok(NULL, n_delim);
	}

	return nd;
}

void add_noun_list_node(NounList *list, NounListNode *list_node)
{
	if (list->root == NULL)
	{
		list_node->noun.idx = 0;
		list_node->next = NULL;
		list->root = list_node;
	}
	else
	{
		NounListNode *curr = list->root;
		int idx = 1;

		while (curr->next != NULL)
		{
			curr = curr->next;
			idx++;
		}

		list_node->noun.idx = idx;
		list_node->next = curr->next;
		curr->next = list_node;
	}
}

NounData get_noun_data(NounList *list, int idx)
{
	NounListNode *curr = list->root;
	int curr_idx = 0;

	while (curr_idx++ < idx)
		curr = curr->next;

	return curr->noun;
}

void print_noun_list(NounList *list)
{
	NounListNode *curr = list->root;

	while (curr->next != NULL)
	{
		print_noun_list_node(curr);
		curr = curr->next;
	}

	print_noun_list_node(curr);
}

void print_noun_list_node(NounListNode *list_node)
{
	printf("\x1b[1m\x1b[44m[N] %-*s |\x1b[0m \n", (int)compensation(list_node->noun.serb) + N_MAX_LENGTH * 2 + 27, list_node->noun.serb);

	printf("\t\x1b[1m\x1b[45m|   %-*s |   %-*s |   %-4s  |\x1b[0m \n",
		   N_MAX_LENGTH + (int)compensation(list_node->noun.sg) + 2, list_node->noun.sg,
		   N_MAX_LENGTH + (int)compensation(list_node->noun.pl) + 2, list_node->noun.pl,
		   list_node->noun.art);

	printf("\n");
}
