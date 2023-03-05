#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../global.h"
#include "../../words/de/verbs.h"

Input *i_inf;
Input *i_pres;
Input *i_pret;
Input *i_pp;
Input *i_hv;

// int MAX_VERB_LENGTH = 14;
int MAX_VERB_LENGTH = 30;

AnswerData *get_random_verb_de(VerbList *v_list, int *excl, int excl_len, int tgt_lvl);
int process_verb_answ_de(int form_idx, VerbData v_data);
float print_verb_answer_analysis_de(VerbData vd, int num_correct);

AnswerData *get_random_verb_de(VerbList *v_list, int *excl, int excl_len, int tgt_lvl)
{
	time_t t;
	srand((unsigned)time(&t));

	int cnt = 0;

	int idx = rand() % v_list->size;
	VerbData v_data = get_verb_data(v_list, idx);

	while (is_contained_in(excl, excl_len, idx) || tgt_lvl != -1 && v_data.lvl != tgt_lvl)
	{
		idx = rand() % v_list->size;
		v_data = get_verb_data(v_list, idx);

		if (cnt++ == 100)
		{
			AnswerData *a_data = malloc(sizeof(AnswerData));
			a_data->idx = -1;
			a_data->pts = .0;
			a_data->should_break = true;

			return a_data;
		}
	}

	i_inf = malloc(sizeof(Input));
	i_pres = malloc(sizeof(Input));
	i_pret = malloc(sizeof(Input));
	i_pp = malloc(sizeof(Input));
	i_hv = malloc(sizeof(Input));

	printf("\x1b[1m\x1b[44m==> %s \x1b[0m \n", v_data.serb);

	int num_correct = 0;

	num_correct += process_verb_answ_de(0, v_data);
	num_correct += process_verb_answ_de(1, v_data);
	num_correct += process_verb_answ_de(2, v_data);
	num_correct += process_verb_answ_de(3, v_data);
	num_correct += process_verb_answ_de(4, v_data);

	float res = print_verb_answer_analysis_de(v_data, num_correct);

	AnswerData *a_data = malloc(sizeof(AnswerData));
	a_data->idx = v_data.idx;
	a_data->pts = res;
	a_data->should_break = false;

	return a_data;
}

int process_verb_answ_de(int form_idx, VerbData v_data)
{
	switch (form_idx)
	{
	case 0:
		printf("%s", "\tinfinitiv       : ");
		fgets(i_inf->content, 50, stdin);
		i_inf->content[strcspn(i_inf->content, "\n")] = '\0';
		i_inf->is_correct = strcmp(i_inf->content, v_data.inf) == 0;
		return i_inf->is_correct ? 1 : 0;
	case 1:
		printf("%s", "\tpräsens         : ");
		fgets(i_pres->content, 50, stdin);
		i_pres->content[strcspn(i_pres->content, "\n")] = '\0';
		i_pres->is_correct = strcmp(i_pres->content, v_data.pres) == 0;
		return i_pres->is_correct ? 1 : 0;
	case 2:
		printf("%s", "\tpräteritum      : ");
		fgets(i_pret->content, 50, stdin);
		i_pret->content[strcspn(i_pret->content, "\n")] = '\0';
		i_pret->is_correct = strcmp(i_pret->content, v_data.pret) == 0;
		return i_pret->is_correct ? 1 : 0;
	case 3:
		printf("%s", "\tplusquamperfekt : ");
		fgets(i_pp->content, 50, stdin);
		i_pp->content[strcspn(i_pp->content, "\n")] = '\0';
		i_pp->is_correct = strcmp(i_pp->content, v_data.pp) == 0;
		return i_pp->is_correct ? 1 : 0;
	case 4:
		printf("%s", "\tauxiliary verb	: ");
		fgets(i_hv->content, 3, stdin);

		// check if fgets() obtained '\n', if yes consume chars up to '\n'
		if (!strchr(i_hv->content, '\n'))
		{
			int ch;
			while (((ch = getchar()) != EOF) && (ch != '\n'))
				;
		}

		i_hv->content[strcspn(i_hv->content, "\n")] = '\0';
		i_hv->is_correct = strcmp(i_hv->content, v_data.hv) == 0;

		return i_hv->is_correct ? 1 : 0;
	default:
		return 0;
	}
}

float print_verb_answer_analysis_de(VerbData vd, int num_correct)
{
	printf("\n");
	printf("\t\x1b[1m\x1b[45m|   %-*s |   %-*s |   %-*s |   %-*s |   %-2s |\x1b[0m \n",
		   MAX_VERB_LENGTH + (int)compensation(vd.inf), vd.inf,
		   MAX_VERB_LENGTH + (int)compensation(vd.pres), vd.pres,
		   MAX_VERB_LENGTH + (int)compensation(vd.pret), vd.pret,
		   MAX_VERB_LENGTH + (int)compensation(vd.pp), vd.pp,
		   vd.hv);
	printf("\t| %s %-*s | %s %-*s | %s %-*s | %s %-*s | %s %-2s | \n",
		   i_inf->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_VERB_LENGTH + (int)compensation(i_inf->content), i_inf->content,
		   i_pres->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_VERB_LENGTH + (int)compensation(i_pres->content), i_pres->content,
		   i_pret->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_VERB_LENGTH + (int)compensation(i_pret->content), i_pret->content,
		   i_pp->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_VERB_LENGTH + (int)compensation(i_pp->content), i_pp->content,
		   i_hv->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", i_hv->content);
	printf("\n");

	float res = num_correct / 5.0;

	printf("\tPOINTS : %.2f \n\n", res);

	return res;
}
