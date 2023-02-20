#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./utils/params.h"
#include "./words/verbs.h"
#include "./tests/v_test.h"

Options *opt;
float score;

int curr_question;
int total_questions;

VerbList *v_list;
int *v_excl;
int v_excl_len;

int main(int argc, char **argv)
{
	printf("\n");

	opt = process_params(argc, argv);

	if (opt->include_verbs)
	{
		v_list = load_verbs_from_preset("./base/verbs.txt");
		v_excl = malloc(sizeof(int) * total_questions);
		v_excl_len = 0;
	}

	while (v_excl_len < v_list->size && opt->q_curr++ < opt->q_total)
	{
		AnswerData *a_data = get_random_verb(v_list, v_excl, v_excl_len);
		v_excl[v_excl_len++] = a_data->idx;
		score += a_data->pts;
	}

	printf("==> TOTAL SCORE : %.2f / %.2f \n\n", score, (opt->q_curr - 1) * 1.0);

	exit(EXIT_SUCCESS);
}
