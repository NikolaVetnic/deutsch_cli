#include <stdio.h>

void print_help()
{
	printf("\n");

	printf("USAGE \n");
	printf("\trun_test [num] [args] \n");
	printf("\n");

	printf("ARGS \n");
	printf("\tv | include [num] randomly chosen verbs \n");
	printf("\tn | include [num] randomly chosen nouns \n");
	printf("\ta | include [num] randomly chosen adjectives \n");
	printf("\tc | include [num] randomly chosenconnectors \n");
	printf("\te | include [num] randomly chosenexpressions \n");
	printf("\n");

	printf("EXAMPLE \n");
	printf("\ttest_run 5 --verbs -n \n");
	printf("\n");
}
