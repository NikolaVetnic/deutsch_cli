#ifndef V_TEST_HU_H_    // include a guard
#define V_TEST_HU_H_

#include "../global.h"
#include "../../words/hu/verbs_hu.h"

AnswerData	*get_random_verb_hu(HuVerbList *v_list, int *excl, int excl_len, int tgt_lvl);

#endif				    // V_TEST_HU_H