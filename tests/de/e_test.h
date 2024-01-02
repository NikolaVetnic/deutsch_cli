#ifndef E_TEST_H_	// include a guard
#define E_TEST_H_

#include "../global.h"
#include "../../words/de/expressions.h"

AnswerData	*get_random_expression_de(ExpressionList *e_list, int *excl, int excl_len, int tgt_lvl);

#endif				// E_TEST_H
