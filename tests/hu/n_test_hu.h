#ifndef N_TEST_HU_H_    // include a guard
#define N_TEST_HU_H_

#include "../global.h"
#include "../../words/hu/nouns_hu.h"

AnswerData	*get_random_noun_hu(HuNounList *n_list, int *excl, int excl_len);

#endif				    // N_TEST_HU_H