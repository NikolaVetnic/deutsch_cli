#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "global.h"
#include "../words/verbs.h"

typedef struct _INPUT
{
	char content[50];
	bool is_correct;
} Input;

Input *i_inf;
Input *i_pres;
Input *i_pret;
Input *i_pp;

AnswerData *get_random_verb(VerbList *v_list, int *excl, int excl_len);
bool is_contained_in(int *arr, int arr_len, int num);
int process_answ(int form_idx, VerbData v_data);
float print_answer_analysis(VerbData vd, int num_correct);

AnswerData *get_random_verb(VerbList *v_list, int *excl, int excl_len)
{
	time_t t;
	srand((unsigned)time(&t));

	int idx = rand() % v_list->size;

	while (is_contained_in(excl, excl_len, idx))
		idx = rand() % v_list->size;

	VerbData v_data = get_data(v_list, idx);

	i_inf = malloc(sizeof(Input));
	i_pres = malloc(sizeof(Input));
	i_pret = malloc(sizeof(Input));
	i_pp = malloc(sizeof(Input));

	printf("==> %s \n", v_data.serb);

	int num_correct = 0;

	num_correct += process_answ(0, v_data);
	num_correct += process_answ(1, v_data);
	num_correct += process_answ(2, v_data);
	num_correct += process_answ(3, v_data);

	float res = print_answer_analysis(v_data, num_correct);

	AnswerData *a_data = malloc(sizeof(AnswerData));
	a_data->idx = v_data.idx;
	a_data->pts = res;

	return a_data;
}

bool is_contained_in(int *arr, int arr_len, int num)
{
	for (int i = 0; i < arr_len; i++)
		if (arr[i] == num)
			return true;

	return false;
}

int process_answ(int form_idx, VerbData v_data)
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
	default:
		return 0;
	}
}

float print_answer_analysis(VerbData vd, int num_correct)
{
	printf("\n");
	printf("\t|   %-13s \t|   %-13s \t|   %-13s \t|   %-13s \t| \n",
		   vd.inf, vd.pres, vd.pret, vd.pp);
	printf("\t| %s %-13s \t| %s %-13s \t| %s %-13s \t| %s %-13s \t| \n",
		   i_inf->is_correct ? "\uf00c" : "\ueab8", i_inf->content,
		   i_pres->is_correct ? "\uf00c" : "\ueab8", i_pres->content,
		   i_pret->is_correct ? "\uf00c" : "\ueab8", i_pret->content,
		   i_pp->is_correct ? "\uf00c" : "\ueab8", i_pp->content);
	printf("\n");

	float res = num_correct / 4.0;

	printf("\tPOINTS : %.2f \n\n", res);

	return res;
}
