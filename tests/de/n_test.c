#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../global.h"
#include "../../words/de/nouns.h"

Input *i_sg;
Input *i_pl;
Input *i_art;

// int MAX_NOUN_LENGTH = 32;
int MAX_NOUN_LENGTH = 64;

AnswerData *get_random_noun_de(NounList *n_list, int *excl, int excl_len, int tgt_lvl);
int process_noun_answ_de(int form_idx, NounData n_data);
float print_noun_answer_analysis_de(NounData nd, int num_correct);

AnswerData *get_random_noun_de(NounList *n_list, int *excl, int excl_len, int tgt_lvl)
{
	time_t t;
	srand((unsigned)time(&t));
	rand(); // intialize rand() with a random seed

	int cnt = 0;

	int idx = rand() % n_list->size;
	NounData n_data = get_noun_data(n_list, idx);

	while (is_contained_in(excl, excl_len, idx) || tgt_lvl != -1 && n_data.lvl != tgt_lvl)
	{
		idx = rand() % n_list->size;
		n_data = get_noun_data(n_list, idx);

		if (cnt++ == 100)
		{
			AnswerData *a_data = malloc(sizeof(AnswerData));
			a_data->idx = -1;
			a_data->pts = .0;
			a_data->should_break = true;

			return a_data;
		}
	}

	i_sg = malloc(sizeof(Input));
	i_pl = malloc(sizeof(Input));
	i_art = malloc(sizeof(Input));

	printf("\x1b[1m\x1b[44m==> %s \x1b[0m \n", n_data.serb);

	int num_correct = 0;

	num_correct += process_noun_answ_de(0, n_data);
	num_correct += process_noun_answ_de(1, n_data);
	num_correct += process_noun_answ_de(2, n_data);

	float res = print_noun_answer_analysis_de(n_data, num_correct);

	AnswerData *a_data = malloc(sizeof(AnswerData));
	a_data->idx = n_data.idx;
	a_data->pts = res;

	return a_data;
}

int process_noun_answ_de(int form_idx, NounData n_data)
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

float print_noun_answer_analysis_de(NounData nd, int num_correct)
{
	printf("\n");
	printf("\t\x1b[1m\x1b[45m|   %-*s |   %-*s |   %-3s  |\x1b[0m \n",
		   MAX_NOUN_LENGTH + (int)compensation(nd.sg), nd.sg,
		   MAX_NOUN_LENGTH + (int)compensation(nd.pl), nd.pl,
		   nd.art);
	printf("\t| %s %-*s | %s %-*s | %s %-3s  | \n",
		   	i_sg->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_NOUN_LENGTH + (int)compensation(i_sg->content), i_sg->content,
		   	i_pl->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_NOUN_LENGTH + (int)compensation(i_pl->content), i_pl->content,
		   	i_art->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", i_art->content);
	printf("\n");

	float res = num_correct / 3.0;

	printf("\tPOINTS : %.2f \n\n", res);

	return res;
}
