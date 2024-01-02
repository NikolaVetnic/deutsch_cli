#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./utils/params.h"
#include "./words/de/nouns.h"
#include "./words/de/verbs.h"
#include "./words/de/ads.h"
#include "./words/de/connectors.h"
#include "./words/de/expressions.h"
#include "./words/hu/nouns_hu.h"
#include "./words/hu/verbs_hu.h"
#include "./tests/de/n_test.h"
#include "./tests/de/v_test.h"
#include "./tests/de/a_test.h"
#include "./tests/de/c_test.h"
#include "./tests/de/e_test.h"
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

AdList *a_list;
int *a_excl;
int a_excl_len;

ConnectorList *c_list;
int *c_excl;
int c_excl_len;

ExpressionList *e_list;
int *e_excl;
int e_excl_len;

void run_nouns_de();
void run_verbs_de();
void run_ads_de();
void run_connectors_de();
void run_expressions_de();

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
		run_ads_de();
		run_connectors_de();
		run_expressions_de();
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

	if (n_list->size < opt->q_step)
	{
		printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m requested %d nouns, but the target database only contains %d ... \n\n", opt->q_step, n_list->size);
		return;
	}

	// print_noun_list(n_list);

	opt->q_total += opt->q_step;

	while (opt->include_nouns && n_excl_len < n_list->size && opt->q_n_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_noun_de(n_list, n_excl, n_excl_len, opt->tgt_lvl);

		if (a_data->should_break)
		{
			printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m no (more) nouns that match the target level were found in the database ... \n\n");
			break;
		}

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

	if (v_list->size < opt->q_step)
	{
		printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m requested %d verbs, but the target database only contains %d ... \n\n", opt->q_step, v_list->size);
		return;
	}

	// print_verb_list(v_list);

	opt->q_total += opt->q_step;

	while (opt->include_verbs && v_excl_len < v_list->size && opt->q_v_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_verb_de(v_list, v_excl, v_excl_len, opt->tgt_lvl);

		if (a_data->should_break)
		{
			printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m no (more) verbs that match the target level were found in the database ... \n\n");
			break;
		}

		v_excl[v_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_v_curr++;
	}
}

void run_ads_de()
{
	if (!opt->include_adjectives)
		return;

	a_list = load_ads_from_preset("./base/de_ads.csv");
	a_excl = malloc(sizeof(int) * total_questions);
	a_excl_len = 0;

	if (a_list->size < opt->q_step)
	{
		printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m requested %d adjectives, but the target database only contains %d ... \n\n", opt->q_step, a_list->size);
		return;
	}

	// print_ad_list(a_list);

	opt->q_total += opt->q_step;

	while (opt->include_adjectives && a_excl_len < a_list->size && opt->q_a_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_ad_de(a_list, a_excl, a_excl_len, opt->tgt_lvl);

		if (a_data->should_break)
		{
			printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m no (more) adjectives or adverbs that match the target level were found in the database ... \n\n");
			break;
		}

		a_excl[a_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_a_curr++;
	}
}

void run_connectors_de()
{
	if (!opt->include_connectors)
		return;

	c_list = load_connectors_from_preset("./base/de_connectors.csv");
	c_excl = malloc(sizeof(int) * total_questions);
	c_excl_len = 0;

	if (c_list->size < opt->q_step)
	{
		printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m requested %d connectors, but the target database only contains %d ... \n\n", opt->q_step, c_list->size);
		return;
	}

	// print_connector_list(c_list);

	opt->q_total += opt->q_step;

	while (opt->include_connectors && c_excl_len < c_list->size && opt->q_c_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_connector_de(c_list, c_excl, c_excl_len, opt->tgt_lvl);

		if (a_data->should_break)
		{
			printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m no (more) connectors that match the target level were found in the database ... \n\n");
			break;
		}

		c_excl[c_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_c_curr++;
	}
}

void run_expressions_de()
{
	if (!opt->include_expressions)
		return;

	e_list = load_expressions_from_preset("./base/de_expressions.csv");
	e_excl = malloc(sizeof(int) * total_questions);
	e_excl_len = 0;

	if (e_list->size < opt->q_step)
	{
		printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m requested %d expressions, but the target database only contains %d ... \n\n", opt->q_step, c_list->size);
		return;
	}

	print_expression_list(e_list);

	opt->q_total += opt->q_step;

	while (opt->include_expressions && e_excl_len < e_list->size && opt->q_e_curr < opt->q_step)
	{
		AnswerData *a_data = get_random_expression_de(e_list, e_excl, e_excl_len, opt->tgt_lvl);

		if (a_data->should_break)
		{
			printf("\x1b[1m\x1b[44m| WARNING |\x1b[0m no (more) verbs that match the target level were found in the database ... \n\n");
			break;
		}

		e_excl[e_excl_len++] = a_data->idx;
		score += a_data->pts;

		opt->q_e_curr++;
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