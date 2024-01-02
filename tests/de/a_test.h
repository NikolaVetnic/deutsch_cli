#ifndef A_TEST_H_	// include a guard
#define A_TEST_H_

#include "../global.h"
#include "../../words/de/ads.h"

AnswerData	*get_random_ad_de(AdList *a_list, int *excl, int excl_len, int tgt_lvl);

#endif				// A_TEST_H
