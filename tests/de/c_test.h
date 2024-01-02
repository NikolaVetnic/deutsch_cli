#ifndef C_TEST_H_	// include a guard
#define C_TEST_H_

#include "../global.h"
#include "../../words/de/connectors.h"

AnswerData	*get_random_connector_de(ConnectorList *c_list, int *excl, int excl_len, int tgt_lvl);

#endif				// C_TEST_H
