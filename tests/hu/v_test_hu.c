#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../global.h"
#include "../../words/hu/verbs_hu.h"

Input *i_pres;

int MAX_VERB_LENGTH_HU = 32;

AnswerData *get_random_verb_hu(HuVerbList *v_list, int *excl, int excl_len, int tgt_lvl);
int process_verb_answ_hu(int form_idx, HuVerbData n_data);
float print_verb_answer_analysis_hu(HuVerbData nd, int num_correct);

AnswerData *get_random_verb_hu(HuVerbList *v_list, int *excl, int excl_len, int tgt_lvl)
{
    time_t t;
    srand((unsigned)time(&t));

    int cnt = 0;

    int idx = rand() % v_list->size;
    HuVerbData v_data = get_verb_data_hu(v_list, idx);

    while (is_contained_in(excl, excl_len, idx) || tgt_lvl != -1 && v_data.lvl != tgt_lvl)
    {
        idx = rand() % v_list->size;
        v_data = get_verb_data_hu(v_list, idx);

        if (cnt++ == 100)
        {
            AnswerData *a_data = malloc(sizeof(AnswerData));
            a_data->idx = -1;
            a_data->pts = .0;
            a_data->should_break = true;

            return a_data;
        }
    }

    i_pres = malloc(sizeof(Input));

    printf("\x1b[1m\x1b[44m==> %s \x1b[0m \n", v_data.serb);

    int num_correct = 0;

    num_correct += process_verb_answ_hu(0, v_data);

    float res = print_verb_answer_analysis_hu(v_data, num_correct);

    AnswerData *a_data = malloc(sizeof(AnswerData));
    a_data->idx = v_data.idx;
    a_data->pts = res;

    return a_data;
}

int process_verb_answ_hu(int form_idx, HuVerbData v_data)
{
    switch (form_idx)
    {
    case 0:
        printf("%s", "\t3rd person singular		: ");
        fgets(i_pres->content, 50, stdin);
        i_pres->content[strcspn(i_pres->content, "\n")] = '\0';
        i_pres->is_correct = strcmp(i_pres->content, v_data.pres) == 0;
        return i_pres->is_correct ? 1 : 0;
    default:
        return 0;
    }
}

float print_verb_answer_analysis_hu(HuVerbData vd, int num_correct)
{
    printf("\n");
    printf("\t\x1b[1m\x1b[45m|   %-*s |\x1b[0m \n",
           MAX_VERB_LENGTH_HU + (int)compensation(vd.pres), vd.pres);
    printf("\t| %s %-*s | \n",
           i_pres->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_VERB_LENGTH_HU + (int)compensation(i_pres->content), i_pres->content);
    printf("\n");

    float res = num_correct / 1.0;

    printf("\tPOINTS : %.2f \n\n", res);

    return res;
}