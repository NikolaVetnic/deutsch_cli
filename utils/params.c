#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "params.h"

Options *process_params(int argc, char **argv)
{
	Options *opt = malloc(sizeof(Options));

	opt->include_verbs = false;
	opt->include_nouns = false;
	opt->include_adjectives = false;
	opt->include_connectors = false;
	opt->include_expressions = false;

	if (argc == 1)
		print_help();

	opt->q_step	  = strtol(argv[1], NULL, 10);
	opt->q_total  = 0;
	opt->q_n_curr = 0;
	opt->q_v_curr = 0;
	opt->q_a_curr = 0;
	opt->q_c_curr = 0;
	opt->q_e_curr = 0;

	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbs") == 0)
			opt->include_verbs = true;
		else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--nouns") == 0)
			opt->include_nouns = true;
		else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--adjectives") == 0)
			opt->include_adjectives = true;
		else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--connectors") == 0)
			opt->include_connectors = true;
		else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--expressions") == 0)
			opt->include_expressions = true;
		else
			printf("\t%s is an invalid arg, ignored \n", argv[i]);
	}

	return opt;
}
