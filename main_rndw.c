#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./utils/params.h"
#include "./words/de/nouns.h"
#include "./words/de/verbs.h"

NounList *n_list;
VerbList *v_list;

void run_nouns_de();
void run_verbs_de();

int main(int argc, char **argv)
{
    time_t t;
    srand((unsigned)time(&t));

    setlocale(LC_CTYPE, ""); // for wide characters

    printf("\n");

    run_nouns_de();
    run_verbs_de();

    exit(EXIT_SUCCESS);
}

void run_nouns_de()
{
    n_list = load_nouns_from_preset("./base/de_nouns.csv");

    int tgt = rand() % n_list->size;
    int idx = -1;

    NounListNode *curr = n_list->root;

    while (idx++ < tgt)
        curr = curr->next;

    print_noun_list_node(curr);
}

void run_verbs_de()
{
    v_list = load_verbs_from_preset("./base/de_verbs.csv");

    int tgt = rand() % v_list->size;
    int idx = -1;

    VerbListNode *curr = v_list->root;

    while (idx++ < tgt)
        curr = curr->next;

    print_verb_list_node(curr);
}