#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../global.h"
#include "../../words/de/expressions.h"

Input *i_word;

int EXPRESSIONS_MAX_LENGTH = 142;
float EXPRESSIONS_MAX_CORRECT_ANSWERS = 1.0;

AnswerData *get_random_expression_de(ExpressionList *c_list, int *excl, int excl_len, int tgt_lvl);
int process_expression_answ_de(int form_idx, ExpressionData a_data);
float print_expression_answer_analysis_de(ExpressionData ad, int num_correct);

AnswerData *get_random_expression_de(ExpressionList *c_list, int *excl, int excl_len, int tgt_lvl)
{
	time_t t;
	srand((unsigned)time(&t));
	rand(); // intialize rand() with a random seed

	int cnt = 0;

	int idx = rand() % c_list->size;
	ExpressionData c_data = get_expression_data(c_list, idx);

	while (is_contained_in(excl, excl_len, idx) || tgt_lvl != -1 && c_data.lvl != tgt_lvl)
	{
		idx = rand() % c_list->size;
		c_data = get_expression_data(c_list, idx);

		if (cnt++ == 100)
		{
			AnswerData *a_data = malloc(sizeof(AnswerData));
			a_data->idx = -1;
			a_data->pts = .0;
			a_data->should_break = true;

			return a_data;
		}
	}

	i_word = malloc(sizeof(Input));

	printf("\x1b[1m\x1b[44m==> %s \x1b[0m \n", c_data.serb);

	int num_correct = 0;

	num_correct += process_expression_answ_de(0, c_data);

	float res = print_expression_answer_analysis_de(c_data, num_correct);

	AnswerData *ans_data = malloc(sizeof(AnswerData));
	ans_data->idx = c_data.idx;
	ans_data->pts = res;

	return ans_data;
}

int process_expression_answ_de(int form_idx, ExpressionData c_data)
{
	switch (form_idx)
	{
	case 0:
		printf("%s", "\tin German			: ");
		fgets(i_word->content, 50, stdin);
		i_word->content[strcspn(i_word->content, "\n")] = '\0';
		i_word->is_correct = strcmp(i_word->content, c_data.word) == 0;
		return i_word->is_correct ? 1 : 0;
	default:
		return 0;
	}
}

float print_expression_answer_analysis_de(ExpressionData expression, int num_correct)
{
	printf("\n");
	printf("\t\x1b[1m\x1b[45m|   %-*s |\x1b[0m \n",
		   EXPRESSIONS_MAX_LENGTH + (int)compensation(expression.word), expression.word);
	printf("\t| %s %-*s | \n",
		   	i_word->is_correct ? 
		   		"\x1b[32;1m\uf00c\x1b[0m" : 
				"\x1b[31;1m\ueab8\x1b[0m", EXPRESSIONS_MAX_LENGTH + (int)compensation(i_word->content), i_word->content);
	printf("\n");

	float res = num_correct / EXPRESSIONS_MAX_CORRECT_ANSWERS;

	printf("\tPOINTS : %.2f \n\n", res);

	return res;
}
