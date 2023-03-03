#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tests/global.h"
#include "verbs.h"

char v_delim[] = ";";
int V_MAX_LENGTH = 20;

VerbList *load_verbs_from_preset(char *filename);
VerbData *process_verb_line(char *ptr);
void add_verb_list_node(VerbList *list, VerbListNode *list_node);
VerbData get_verb_data(VerbList *list, int idx);
void print_verb_list(VerbList *list);
void print_verb_list_node(VerbListNode *list_node);

VerbList *load_verbs_from_preset(char *filename)
{
	FILE *file = fopen(filename, "r");

	VerbList *v_list = malloc(sizeof(VerbList));
	v_list->size = 0;
	v_list->root = NULL;

	char buf[500];

	while (fgets(buf, sizeof buf, file) != NULL)
	{
		if (buf[0] == '#')
			continue;

		buf[strcspn(buf, "\n")] = '\0';

		char *ptr = strtok(buf, v_delim);

		VerbListNode *vln = malloc(sizeof(VerbListNode));
		VerbData *vd = process_verb_line(ptr);
		vln->verb = *vd;

		add_verb_list_node(v_list, vln);
		v_list->size++;
	}

	if (!feof(file))
		printf("an error interrupted the read \n");

	fclose(file);

	return v_list;
}

VerbData *process_verb_line(char *ptr)
{
	int idx = 0;

	VerbData *vd = malloc(sizeof(VerbData));

	while (ptr != NULL)
	{
		switch (idx++)
		{
		case 0:
			vd->serb = malloc(sizeof(char) * strlen(ptr) + 1);
			strcpy(vd->serb, ptr);
			break;
		case 1:
			vd->inf = malloc(sizeof(char) * strlen(ptr) + 1);
			strcpy(vd->inf, ptr);
			break;
		case 2:
			vd->pres = malloc(sizeof(char) * strlen(ptr) + 1);
			strcpy(vd->pres, ptr);
			break;
		case 3:
			vd->pret = malloc(sizeof(char) * strlen(ptr) + 1);
			strcpy(vd->pret, ptr);
			break;
		case 4:
			vd->pp = malloc(sizeof(char) * strlen(ptr) + 1);
			strcpy(vd->pp, ptr);
			break;
		case 5:
			vd->hv = malloc(sizeof(char) * strlen(ptr) + 1);
			strcpy(vd->hv, ptr);
			break;
		case 6:
			if (strcmp(ptr, "c2") == 0)
				vd->lvl = 5;
			else if (strcmp(ptr, "c1") == 0)
				vd->lvl = 4;
			else if (strcmp(ptr, "b2") == 0)
				vd->lvl = 3;
			else if (strcmp(ptr, "b1") == 0)
				vd->lvl = 2;
			else if (strcmp(ptr, "a2") == 0)
				vd->lvl = 1;
			else if (strcmp(ptr, "a1") == 0)
				vd->lvl = 0;
			break;
		}

		ptr = strtok(NULL, v_delim);
	}

	return vd;
}

void add_verb_list_node(VerbList *list, VerbListNode *list_node)
{
	if (list->root == NULL)
	{
		list_node->verb.idx = 0;
		list_node->next = NULL;
		list->root = list_node;
	}
	else
	{
		VerbListNode *curr = list->root;
		int idx = 1;

		while (curr->next != NULL)
		{
			curr = curr->next;
			idx++;
		}

		list_node->verb.idx = idx;
		list_node->next = curr->next;
		curr->next = list_node;
	}
}

VerbData get_verb_data(VerbList *list, int idx)
{
	VerbListNode *curr = list->root;
	int curr_idx = 0;

	while (curr_idx++ < idx)
		curr = curr->next;

	return curr->verb;
}

void print_verb_list(VerbList *list)
{
	VerbListNode *curr = list->root;

	while (curr->next != NULL)
	{
		print_verb_list_node(curr);
		curr = curr->next;
	}

	print_verb_list_node(curr);
}

void print_verb_list_node(VerbListNode *list_node)
{
	printf("\x1b[1m\x1b[44m[V] %-*s |\x1b[0m \n", (int)compensation(list_node->verb.serb) + V_MAX_LENGTH * 4 + 31, list_node->verb.serb);

	printf("\t\x1b[1m\x1b[45m|   %-*s |   %-*s |   %-*s |   %-*s |   %-3s |\x1b[0m \n",
		   V_MAX_LENGTH + (int)compensation(list_node->verb.inf), list_node->verb.inf,
		   V_MAX_LENGTH + (int)compensation(list_node->verb.pres), list_node->verb.pres,
		   V_MAX_LENGTH + (int)compensation(list_node->verb.pret), list_node->verb.pret,
		   V_MAX_LENGTH + (int)compensation(list_node->verb.pp), list_node->verb.pp,
		   list_node->verb.hv);

	printf("\n");
}
