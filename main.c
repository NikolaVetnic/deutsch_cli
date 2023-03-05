#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./utils/params.h"
#include "./words/de/nouns.h"
#include "./words/de/verbs.h"
#include "./words/hu/nouns_hu.h"
#include "./words/hu/verbs_hu.h"
#include "./tests/de/n_test.h"
#include "./tests/de/v_test.h"
#include "./tests/hu/n_test_hu.h"
#include "./tests/hu/v_test_hu.h"

Options *opt;
float score;

int curr_question;
int total_questions;

NounList *n_list;
HuNounList *n_list_hu;
int *n_excl;
int n_excl_len;

VerbList *v_list;
HuVerbList *v_list_hu;
int *v_excl;
int v_excl_len;

void run_nouns_de();
void run_verbs_de();

void run_nouns_hu();
void run_verbs_hu();

int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned)time(&t));

	setlocale(LC_CTYPE, ""); // for wide characters

	printf("\n");

	opt = process_params(argc, argv);

	if (opt->lang == 0)
	{
		run_nouns_de();
		run_verbs_de();
	}

	if (opt->lang == 1)
	{
		run_nouns_hu();
		run_verbs_hu();
	}

	printf("==> TOTAL SCORE : %.2f / %.2f (%.1f%%) \n\n", score, opt->q_total * 1.0, opt->q_total == 0 ? .0f : score / (opt->q_total * 1.0) * 100.0);

	exit(EXIT_SUCCESS);
}

void run_nouns_de()
{
	if (!opt->include_nouns)
		return;

	n_list = load_nouns_from_preset("./base/de_nouns.csv");
	n_excl = malloc(sizeof(int) * total_questions);
	n_excl_len = 0;

	// print_noun_list(n_list);

	opt->q_total += opt->q_step;

	while (opt->include_nouns && n_excl_len < n_list->size && opt->q_n_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_noun_de(n_list, n_excl, n_excl_len);
		n_excl[n_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_n_curr++;
	}
}

void run_verbs_de()
{
	if (!opt->include_verbs)
		return;

	v_list = load_verbs_from_preset("./base/de_verbs.csv");
	v_excl = malloc(sizeof(int) * total_questions);
	v_excl_len = 0;

	// print_verb_list(v_list);

	opt->q_total += opt->q_step;

	while (opt->include_verbs && v_excl_len < v_list->size && opt->q_v_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_verb_de(v_list, v_excl, v_excl_len, opt->tgt_lvl);

		if (a_data->should_break)
		{
			printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m no (more) verbs that match the target level were found in the database \n\n");
			break;
		}

		v_excl[v_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_v_curr++;
	}
}

void run_nouns_hu()
{
	if (!opt->include_nouns)
		return;

	HuNounList *n_list = load_nouns_from_preset_hu("./base/hu_nouns.csv");

	n_list_hu = load_nouns_from_preset_hu("./base/hu_nouns.csv");
	n_excl = malloc(sizeof(int) * total_questions);
	n_excl_len = 0;

	// print_noun_list_hu(n_list);

	opt->q_total += opt->q_step;

	while (opt->include_nouns && n_excl_len < n_list->size && opt->q_n_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_noun_hu(n_list, n_excl, n_excl_len);
		n_excl[n_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_n_curr++;
	}
}

void run_verbs_hu()
{
	if (!opt->include_verbs)
		return;

	v_list_hu = load_verbs_from_preset_hu("./base/hu_verbs.csv");
	v_excl = malloc(sizeof(int) * total_questions);
	v_excl_len = 0;

	// print_verb_list_hu(v_list_hu);

	opt->q_total += opt->q_step;

	while (opt->include_verbs && v_excl_len < v_list_hu->size && opt->q_v_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_verb_hu(v_list_hu, v_excl, v_excl_len, opt->tgt_lvl);

		if (a_data->should_break)
		{
			printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m no (more) verbs that match the target level were found in the database \n\n");
			break;
		}

		v_excl[v_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_v_curr++;
	}
}