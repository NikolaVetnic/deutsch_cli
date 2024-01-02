#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../global.h"
#include "../../words/de/ads.h"

Input *i_word;

int AD_MAX_LENGTH = 142;
float AD_MAX_CORRECT_ANSWERS = 1.0;

AnswerData *get_random_ad_de(AdList *a_list, int *excl, int excl_len, int tgt_lvl);
int process_ad_answ_de(int form_idx, AdData a_data);
float print_ad_answer_analysis_de(AdData ad, int num_correct);

AnswerData *get_random_ad_de(AdList *a_list, int *excl, int excl_len, int tgt_lvl)
{
	time_t t;
	srand((unsigned)time(&t));

	int cnt = 0;

	int idx = rand() % a_list->size;
	AdData a_data = get_ad_data(a_list, idx);

	while (is_contained_in(excl, excl_len, idx) || tgt_lvl != -1 && a_data.lvl != tgt_lvl)
	{
		idx = rand() % a_list->size;
		a_data = get_ad_data(a_list, idx);

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

	printf("\x1b[1m\x1b[44m==> %s \x1b[0m \n", a_data.serb);

	int num_correct = 0;

	num_correct += process_ad_answ_de(0, a_data);

	float res = print_ad_answer_analysis_de(a_data, num_correct);

	AnswerData *ans_data = malloc(sizeof(AnswerData));
	ans_data->idx = a_data.idx;
	ans_data->pts = res;

	// for (int i = 0; i < excl_len; i++)
	// {
	// 	printf("excl[%d] = %d \n", i, excl[i]);
	// }

	return ans_data;
}

int process_ad_answ_de(int form_idx, AdData a_data)
{
	switch (form_idx)
	{
	case 0:
		printf("%s", "\tin German			: ");
		fgets(i_word->content, 50, stdin);
		i_word->content[strcspn(i_word->content, "\n")] = '\0';
		i_word->is_correct = strcmp(i_word->content, a_data.word) == 0;
		return i_word->is_correct ? 1 : 0;
	default:
		return 0;
	}
}

float print_ad_answer_analysis_de(AdData ad, int num_correct)
{
	printf("\n");
	printf("\t\x1b[1m\x1b[45m|   %-*s |\x1b[0m \n",
		   AD_MAX_LENGTH + (int)compensation(ad.word), ad.word);
	printf("\t| %s %-*s | \n",
		   	i_word->is_correct ? 
		   		"\x1b[32;1m\uf00c\x1b[0m" : 
				"\x1b[31;1m\ueab8\x1b[0m", AD_MAX_LENGTH + (int)compensation(i_word->content), i_word->content);
	printf("\n");

	float res = num_correct / AD_MAX_CORRECT_ANSWERS;

	printf("\tPOINTS : %.2f \n\n", res);

	return res;
}
