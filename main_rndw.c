#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./utils/params.h"
#include "./words/de/ads.h"
#include "./words/de/connectors.h"
#include "./words/de/expressions.h"
#include "./words/de/nouns.h"
#include "./words/de/verbs.h"

AdList *a_list;
ConnectorList *c_list;
ExpressionList *e_list;
NounList *n_list;
VerbList *v_list;

void run_nouns_de();
void run_verbs_de();
void run_ads_de();
void run_connectors_de();
void run_expressions_de();

int main(int argc, char **argv)
{
    time_t t;
    srand((unsigned)time(&t));

    setlocale(LC_CTYPE, ""); // for wide characters

    printf("\n");

    run_nouns_de();
    run_verbs_de();
    run_ads_de();
    run_connectors_de();
    run_expressions_de();

    exit(EXIT_SUCCESS);
}

void run_nouns_de()
{
    n_list = load_nouns_from_preset("./base/de_nouns.csv");

    int tgt = rand() % n_list->size;
    int idx = -1;

    NounListNode *curr = n_list->root;

    while (idx++ < tgt)
    {
        if (idx < tgt)
            curr = curr->next;
    }

    print_noun_list_node(curr);
}

void run_verbs_de()
{
    v_list = load_verbs_from_preset("./base/de_verbs.csv");

    int tgt = rand() % v_list->size;
    int idx = -1;

    VerbListNode *curr = v_list->root;

    while (idx++ < tgt)
    {
        if (idx < tgt)
            curr = curr->next;
    }

    print_verb_list_node(curr);
}

void run_ads_de()
{
    a_list = load_ads_from_preset("./base/de_ads.csv");

    int tgt = rand() % a_list->size;
    int idx = -1;

    AdListNode *curr = a_list->root;

    while (idx++ < tgt)
    {
        if (idx < tgt)
            curr = curr->next;
    }

    print_ad_list_node(curr);
}

void run_connectors_de()
{
    c_list = load_connectors_from_preset("./base/de_connectors.csv");

    int tgt = rand() % c_list->size;
    int idx = -1;

    ConnectorListNode *curr = c_list->root;

    while (idx++ < tgt)
    {
        if (idx < tgt)
            curr = curr->next;
    }

    print_connector_list_node(curr);
}

void run_expressions_de()
{
    e_list = load_expressions_from_preset("./base/de_expressions.csv");

    int tgt = rand() % e_list->size;
    int idx = -1;

    ExpressionListNode *curr = e_list->root;

    while (idx++ < tgt)
    {
        if (idx < tgt)
            curr = curr->next;
    }

    print_expression_list_node(curr);
}