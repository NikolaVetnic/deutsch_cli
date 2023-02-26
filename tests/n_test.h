#ifndef N_TEST_H_	// include a guard
#define N_TEST_H_

#include "global.h"
#include "../words/nouns.h"

AnswerData	*get_random_noun(NounList *n_list, int *excl, int excl_len);

#endif				// N_TEST_H
