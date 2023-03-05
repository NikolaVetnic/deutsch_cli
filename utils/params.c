#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "params.h"
#include "utils.h"

void parse_lang(Options *opt, int argc, char **argv);
void parse_q_step(Options *opt, int argc, char **argv);
void parse_tgt_lvl(Options *opt, int argc, char **argv);
void print_params(Options *opt);

Options *process_params(int argc, char **argv)
{
	Options *opt = malloc(sizeof(Options));

	opt->include_verbs = false;
	opt->include_nouns = false;
	opt->include_adjectives = false;
	opt->include_connectors = false;
	opt->include_expressions = false;

	parse_lang(opt, argc, argv);
	parse_q_step(opt, argc, argv);
	parse_tgt_lvl(opt, argc, argv);

	int start_idx = 3;

	if (opt->tgt_lvl != -1)
		start_idx = 4;

	for (int i = start_idx; i < argc; i++)
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

	print_params(opt);

	return opt;
}

void parse_lang(Options *opt, int argc, char **argv)
{
	opt->lang = -1;

	if (strcmp(argv[1], "-de") == 0)
		opt->lang = 0;
	else if (strcmp(argv[1], "-hu") == 0)
		opt->lang = 1;

	if (opt->lang == -1)
	{
		print_err("invalid language specified as arg1");
		exit(EXIT_FAILURE);
	}
}

void parse_q_step(Options *opt, int argc, char **argv)
{
	if (isdigit(argv[2][0]) == 0)
	{
		print_err("invalid q_step specified as arg2");
		exit(EXIT_FAILURE);
	}

	opt->q_step = strtol(argv[2], NULL, 10);
	opt->q_total = 0;

	opt->q_v_curr = 0;
	opt->q_n_curr = 0;
	opt->q_a_curr = 0;
	opt->q_c_curr = 0;
	opt->q_e_curr = 0;
}

void parse_tgt_lvl(Options *opt, int argc, char **argv)
{
	opt->tgt_lvl = -1;

	if (strcmp(argv[3], "-a1") == 0)
		opt->tgt_lvl = 0;
	else if (strcmp(argv[3], "-a2") == 0)
		opt->tgt_lvl = 1;
	else if (strcmp(argv[3], "-b1") == 0)
		opt->tgt_lvl = 2;
	else if (strcmp(argv[3], "-b2") == 0)
		opt->tgt_lvl = 3;
	else if (strcmp(argv[3], "-c1") == 0)
		opt->tgt_lvl = 4;
	else if (strcmp(argv[3], "-c2") == 0)
		opt->tgt_lvl = 5;
}

void print_params(Options *opt)
{
	printf("\x1b[1m\x1b[44m| %-30s |\x1b[0m \n", "QUIZ PARAMETERS");

	printf("\x1b[1m\x1b[45m| %-27s %2s |\x1b[0m \n", "language", opt->lang == 0 ? "de" : "hu");
	printf("\x1b[1m\x1b[45m| %-25s %4d |\x1b[0m \n", "words per group", opt->q_step);
	printf("\x1b[1m\x1b[45m| %-25s %4s |\x1b[0m \n", "target level", opt->tgt_lvl == -1 ? "all" : opt->tgt_lvl == 0 ? "a1"
																							  : opt->tgt_lvl == 1	? "a2"
																							  : opt->tgt_lvl == 2	? "b1"
																							  : opt->tgt_lvl == 3	? "b2"
																							  : opt->tgt_lvl == 4	? "c1"
																													: "c2");

	printf("\x1b[1m\x1b[45m| %-20s ", "included");
	printf("%s ", opt->include_verbs ? "\x1b[44mV\x1b[45m" : "_");
	printf("%s ", opt->include_nouns ? "\x1b[44mN\x1b[45m" : "_");
	printf("%s ", opt->include_adjectives ? "\x1b[44mA\x1b[45m" : "_");
	printf("%s ", opt->include_connectors ? "\x1b[44mC\x1b[45m" : "_");
	printf("%s ", opt->include_expressions ? "\x1b[44mE\x1b[45m" : "_");
	printf("|\x1b[0m \n");

	printf("\n");
}