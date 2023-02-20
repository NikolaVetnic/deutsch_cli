#ifndef PARAMS_H_	// include a guard
#define PARAMS_H_

#include <stdbool.h>

typedef struct
{
	int q_total;
	int q_curr;
	
	bool include_verbs;
	bool include_nouns;
	bool include_adjectives;
	bool include_connectors;
	bool include_expressions;
} Options;

Options *process_params(int argc, char **argv);

#endif				// PARAMS_H_
