#ifndef V_TEST_H_	// include a guard
#define V_TEST_H_

#include "../global.h"
#include "../../words/de/verbs.h"

AnswerData	*get_random_verb_de(VerbList *v_list, int *excl, int excl_len, int tgt_lvl);

#endif				// V_TEST_H_ 
