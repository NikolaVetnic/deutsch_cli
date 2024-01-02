#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../../tests/global.h"
#include "ads.h"
#include "../../utils/utils.h"

char a_delim[] = ";";
int A_MAX_LENGTH = 30;

AdList *load_ads_from_preset(char *filename);
AdData *process_ad_line(char *ptr);
void add_ad_list_node(AdList *list, AdListNode *list_node);
AdData get_ad_data(AdList *list, int idx);
void print_ad_list(AdList *list);
void print_ad_list_node(AdListNode *list_node);

AdList *load_ads_from_preset(char *filename)
{
	FILE *file = fopen(filename, "r");

	AdList *a_list = malloc(sizeof(AdList));
	a_list->size = 0;
	a_list->root = NULL;

	char buf[500];

	while (fgets(buf, sizeof buf, file) != NULL)
	{
		if (buf[0] == '#')
			continue;

		buf[strcspn(buf, "\n")] = '\0';

		char *ptr = strtok(buf, a_delim);

		AdListNode *aln = malloc(sizeof(AdListNode));
		AdData *ad = process_ad_line(ptr);
		aln->ad = *ad;

		add_ad_list_node(a_list, aln);
		a_list->size++;
	}

	if (!feof(file))
		printf("an error interrupted the read \n");

	fclose(file);

	return a_list;
}

AdData *process_ad_line(char *ptr)
{
	int idx = 0;

	AdData *ad = malloc(sizeof(AdData));

	while (ptr != NULL)
	{
		switch (idx++)
		{
		case 0:
			ad->serb = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(ad->serb, ptr);
			break;
		case 1:
			ad->word = malloc(sizeof(char) * (strlen(ptr) + 1));
			strcpy(ad->word, ptr);
			break;
		}

		ptr = strtok(NULL, a_delim);
	}

	return ad;
}

void add_ad_list_node(AdList *list, AdListNode *list_node)
{
	if (list->root == NULL)
	{
		list_node->ad.idx = 0;
		list_node->next = NULL;
		list->root = list_node;
	}
	else
	{
		AdListNode *curr = list->root;
		int idx = 1;

		while (curr->next != NULL)
		{
			curr = curr->next;
			idx++;
		}

		list_node->ad.idx = idx;
		list_node->next = curr->next;
		curr->next = list_node;
	}
}

AdData get_ad_data(AdList *list, int idx)
{
	AdListNode *curr = list->root;
	int curr_idx = 0;

	while (curr_idx++ < idx)
		curr = curr->next;

	return curr->ad;
}

void print_ad_list(AdList *list)
{
	AdListNode *curr = list->root;

	while (curr->next != NULL)
	{
		print_ad_list_node(curr);
		curr = curr->next;
	}

	print_ad_list_node(curr);
}

void print_ad_list_node(AdListNode *list_node)
{
	int width = display_width(list_node->ad.serb);
	int field_width = A_MAX_LENGTH * 2 + 87 - width + (int)strlen(list_node->ad.serb);
	printf("\x1b[1m\x1b[44m[A] %-*s |\x1b[0m \n", field_width, list_node->ad.serb);

	printf("\t\x1b[1m\x1b[45m|   %-*s |\x1b[0m \n",
		   A_MAX_LENGTH + (int)compensation(list_node->ad.word) + 113, list_node->ad.word);

	printf("\n");
}
