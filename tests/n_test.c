#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "global.h"
#include "../words/nouns.h"

Input *i_sg;
Input *i_pl;
Input *i_art;

AnswerData *get_random_noun(NounList *n_list, int *excl, int excl_len);
int process_noun_answ(int form_idx, NounData n_data);
float print_noun_answer_analysis(NounData nd, int num_correct);

AnswerData *get_random_noun(NounList *n_list, int *excl, int excl_len)
{
	time_t t;
	srand((unsigned)time(&t));

	int idx = rand() & n_list->size;
		idx = idx == n_list->size ? 0 : idx;

	while (is_contained_in(excl, excl_len, idx))
	{
		idx = rand() & n_list->size;
		idx = idx == n_list->size ? 0 : idx;
	}

	NounData n_data = get_noun_data(n_list, idx);

	i_sg = malloc(sizeof(Input));
	i_pl = malloc(sizeof(Input));
	i_art = malloc(sizeof(Input));

	printf("==> %s \n", n_data.serb);

	int num_correct = 0;

	num_correct += process_noun_answ(0, n_data);
	num_correct += process_noun_answ(1, n_data);
	num_correct += process_noun_answ(2, n_data);

	float res = print_noun_answer_analysis(n_data, num_correct);

	AnswerData *a_data = malloc(sizeof(AnswerData));
	a_data->idx = n_data.idx;
	a_data->pts = res;

	return a_data;
}

int process_noun_answ(int form_idx, NounData n_data)
{
	switch (form_idx)
	{
		case 0:
			printf("%s", "\tsingular			: ");
			fgets(i_sg->content, 50, stdin);
			i_sg->content[strcspn(i_sg->content, "\n")] = '\0';
			i_sg->is_correct = strcmp(i_sg->content, n_data.sg) == 0;
			return i_sg->is_correct ? 1 : 0;
		case 1:
			printf("%s", "\tplurar				: ");
			fgets(i_pl->content, 50, stdin);
			i_pl->content[strcspn(i_pl->content, "\n")] = '\0';
			i_pl->is_correct = strcmp(i_pl->content, n_data.pl) == 0;
			return i_pl->is_correct ? 1 : 0;
		case 2:
			printf("%s", "\tarticle				: ");
			fgets(i_art->content, 50, stdin);
			i_art->content[strcspn(i_art->content, "\n")] = '\0';
			i_art->is_correct = strcmp(i_art->content, n_data.art) == 0;
			return i_art->is_correct ? 1 : 0;
		default:
			return 0;
	}
}

float print_noun_answer_analysis(NounData nd, int num_correct)
{
	printf("\n");
	printf("\t\x1b[1m\x1b[45m|   %-20s |   %-20s \t|   %-3s |\x1b[0m \n",
		   nd.sg, nd.pl, nd.art);
	printf("\t| %s %-20s | %s %-20s \t\t| %s %-3s | \n",
		    i_sg->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m",  i_sg->content,
		    i_pl->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m",  i_pl->content,
		   i_art->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", i_art->content);
	printf("\n");

	float res = num_correct / 3.0;

	printf("\tPOINTS : %.2f \n\n", res);

	return res;
}
