#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../global.h"
#include "../../words/hu/nouns_hu.h"

Input *i_sg;
Input *i_pl;

int MAX_NOUN_LENGTH_HU = 32;

AnswerData *get_random_noun_hu(HuNounList *n_list, int *excl, int excl_len);
int process_noun_answ_hu(int form_idx, HuNounData n_data);
float print_noun_answer_analysis_hu(HuNounData nd, int num_correct);

AnswerData *get_random_noun_hu(HuNounList *n_list, int *excl, int excl_len)
{
    time_t t;
    srand((unsigned)time(&t));

    int idx = rand() % n_list->size;

    HuNounData n_data = get_noun_data_hu(n_list, idx);

    i_sg = malloc(sizeof(Input));
    i_pl = malloc(sizeof(Input));

    printf("\x1b[1m\x1b[44m==> %s \x1b[0m \n", n_data.serb);

    int num_correct = 0;

    num_correct += process_noun_answ_hu(0, n_data);
    num_correct += process_noun_answ_hu(1, n_data);

    float res = print_noun_answer_analysis_hu(n_data, num_correct);

    AnswerData *a_data = malloc(sizeof(AnswerData));
    a_data->idx = n_data.idx;
    a_data->pts = res;

    return a_data;
}

int process_noun_answ_hu(int form_idx, HuNounData n_data)
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
    default:
        return 0;
    }
}

float print_noun_answer_analysis_hu(HuNounData nd, int num_correct)
{
    printf("\n");
    printf("\t\x1b[1m\x1b[45m|   %-*s |   %-*s |\x1b[0m \n",
           MAX_NOUN_LENGTH_HU + (int)compensation(nd.sg), nd.sg,
           MAX_NOUN_LENGTH_HU + (int)compensation(nd.pl), nd.pl);
    printf("\t| %s %-*s | %s %-*s | \n",
           i_sg->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_NOUN_LENGTH_HU + (int)compensation(i_sg->content), i_sg->content,
           i_pl->is_correct ? "\x1b[32;1m\uf00c\x1b[0m" : "\x1b[31;1m\ueab8\x1b[0m", MAX_NOUN_LENGTH_HU + (int)compensation(i_pl->content), i_pl->content);
    printf("\n");

    float res = num_correct / 2.0;

    printf("\tPOINTS : %.2f \n\n", res);

    return res;
}