#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./utils/params.h"
#include "./words/nouns.h"
#include "./words/verbs.h"
#include "./tests/n_test.h"
#include "./tests/v_test.h"

Options *opt;
float score;

int curr_question;
int total_questions;

NounList *n_list;
int *n_excl;
int n_excl_len;

VerbList *v_list;
int *v_excl;
int v_excl_len;

void run_nouns();
void run_verbs();

int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned)time(&t));

	setlocale(LC_CTYPE, ""); // for wide characters

	printf("\n");

	opt = process_params(argc, argv);

	run_nouns();
	run_verbs();

	int used_total =
		opt->q_n_curr +
		opt->q_v_curr +
		opt->q_a_curr +
		opt->q_c_curr +
		opt->q_e_curr;

	printf("==> TOTAL SCORE : %.2f / %.2f \n\n", score, used_total * 1.0);

	exit(EXIT_SUCCESS);
}

void run_nouns()
{
	if (!opt->include_nouns)
		return;

	n_list = load_nouns_from_preset("./base/nouns.txt");
	n_excl = malloc(sizeof(int) * total_questions);
	n_excl_len = 0;

	opt->q_total += opt->q_step;

	while (opt->include_nouns && n_excl_len < n_list->size && opt->q_n_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_noun(n_list, n_excl, n_excl_len);
		n_excl[n_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_n_curr++;
	}
}

void run_verbs()
{
	if (!opt->include_verbs)
		return;

	v_list = load_verbs_from_preset("./base/verbs.txt");
	v_excl = malloc(sizeof(int) * total_questions);
	v_excl_len = 0;

	opt->q_total += opt->q_step;

	while (opt->include_verbs && v_excl_len < v_list->size && opt->q_v_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_verb(v_list, v_excl, v_excl_len);
		v_excl[v_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_v_curr++;
	}
}
