#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../../tests/global.h"
#include "expressions.h"
#include "../../utils/utils.h"

char e_delim[] = ";";
int E_MAX_LENGTH = 30;

ExpressionList *load_expressions_from_preset(char *filename);
ExpressionData *process_expression_line(char *ptr);
void add_expression_list_node(ExpressionList *list, ExpressionListNode *list_node);
ExpressionData get_expression_data(ExpressionList *list, int idx);
void print_expression_list(ExpressionList *list);
void print_expression_list_node(ExpressionListNode *list_node);

ExpressionList *load_expressions_from_preset(char *filename)
{
	FILE *file = fopen(filename, "r");

	ExpressionList *e_list = malloc(sizeof(ExpressionList));
	e_list->size = 0;
	e_list->root = NULL;

	char buf[500];

	while (fgets(buf, sizeof buf, file) != NULL)
	{
		if (buf[0] == '#')
			continue;

		buf[strcspn(buf, "\n")] = '\0';

		char *ptr = strtok(buf, e_delim);

		ExpressionListNode *eln = malloc(sizeof(ExpressionListNode));
		ExpressionData *ed = process_expression_line(ptr);
		eln->expression = *ed;

		add_expression_list_node(e_list, eln);
		e_list->size++;
	}

	if (!feof(file))
		printf("an error interrupted the read \n");

	fclose(file);

	return e_list;
}

ExpressionData *process_expression_line(char *ptr)
{
	int idx = 0;

	ExpressionData *ed = malloc(sizeof(ExpressionData));

	while (ptr != NULL)
	{
		switch (idx++)
		{
		case 0:
			ed->serb = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(ed->serb, ptr);
			break;
		case 1:
			ed->word = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(ed->word, ptr);
			break;
		}

		ptr = strtok(NULL, e_delim);
	}

	return ed;
}

void add_expression_list_node(ExpressionList *list, ExpressionListNode *list_node)
{
	if (list->root == NULL)
	{
		list_node->expression.idx = 0;
		list_node->next = NULL;
		list->root = list_node;
	}
	else
	{
		ExpressionListNode *curr = list->root;
		int idx = 1;

		while (curr->next != NULL)
		{
			curr = curr->next;
			idx++;
		}

		list_node->expression.idx = idx;
		list_node->next = curr->next;
		curr->next = list_node;
	}
}

ExpressionData get_expression_data(ExpressionList *list, int idx)
{
	ExpressionListNode *curr = list->root;
	int curr_idx = 0;

	while (curr_idx++ < idx)
		curr = curr->next;

	return curr->expression;
}

void print_expression_list(ExpressionList *list)
{
	ExpressionListNode *curr = list->root;

	while (curr->next != NULL)
	{
		print_expression_list_node(curr);
		curr = curr->next;
	}

	print_expression_list_node(curr);
}

void print_expression_list_node(ExpressionListNode *list_node)
{
	int width = display_width(list_node->expression.serb);
	int field_width = E_MAX_LENGTH * 2 + 87 - width + (int)strlen(list_node->expression.serb);
	printf("\x1b[1m\x1b[44m[E] %-*s |\x1b[0m \n", field_width, list_node->expression.serb);

	printf("\t\x1b[1m\x1b[45m|   %-*s |\x1b[0m \n",
		   E_MAX_LENGTH + (int)compensation(list_node->expression.word) + 113, list_node->expression.word);

	printf("\n");
}
