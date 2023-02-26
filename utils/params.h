#ifndef PARAMS_H_	// include a guard
#define PARAMS_H_

#include <stdbool.h>

typedef struct
{
	int q_step;
	int q_total;
	int q_n_curr;
	int q_v_curr;
	int q_a_curr;
	int q_c_curr;
	int q_e_curr;
	
	bool include_verbs;
	bool include_nouns;
	bool include_adjectives;
	bool include_connectors;
	bool include_expressions;
} Options;

Options *process_params(int argc, char **argv);

#endif				// PARAMS_H_
