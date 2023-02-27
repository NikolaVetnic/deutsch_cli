#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./utils/params.h"
#include "./words/nouns.h"
#include "./words/verbs.h"

NounList *n_list;
VerbList *v_list;

void run_nouns();
void run_verbs();

int main(int argc, char **argv)
{
    time_t t;
    srand((unsigned)time(&t));

    setlocale(LC_CTYPE, ""); // for wide characters

    printf("\n");

    run_nouns();
    run_verbs();

    exit(EXIT_SUCCESS);
}

void run_nouns()
{
    n_list = load_nouns_from_preset("./base/nouns.txt");

    int tgt = rand() % n_list->size;
    int idx = -1;

    NounListNode *curr = n_list->root;

    while (idx++ < tgt)
        curr = curr->next;

    print_noun_list_node(curr);
}

void run_verbs()
{
    v_list = load_verbs_from_preset("./base/verbs.txt");

    int tgt = rand() % v_list->size;
    int idx = -1;

    VerbListNode *curr = v_list->root;

    while (idx++ < tgt)
        curr = curr->next;

    print_verb_list_node(curr);
}