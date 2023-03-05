#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nouns_hu.h"
#include "../../utils/utils.h"
#include "../../tests/global.h"

char n_delim_hu[] = ";";
int N_MAX_LENGTH_HU = 32;

HuNounList *load_nouns_from_preset_hu(char *filename);
HuNounData *process_noun_line_hu(char *ptr);
void add_noun_list_node_hu(HuNounList *list, HuNounListNode *list_node);
HuNounData get_noun_data_hu(HuNounList *list, int idx);
void print_noun_list_node_hu(HuNounListNode *list_node);
void print_noun_list_hu(HuNounList *list);

HuNounList *load_nouns_from_preset_hu(char *filename)
{
    FILE *file = fopen(filename, "r");

    HuNounList *n_list = malloc(sizeof(HuNounList));
    n_list->size = 0;
    n_list->root = NULL;

    char buf[500];

    while (fgets(buf, sizeof buf, file) != NULL)
    {
        if (buf[0] == '#')
            continue;

        buf[strcspn(buf, "\n")] = '\0';

        char *ptr = strtok(buf, n_delim_hu);

        HuNounListNode *nln = malloc(sizeof(HuNounListNode));
        HuNounData *nd = process_noun_line_hu(ptr);
        nln->noun = *nd;

        add_noun_list_node_hu(n_list, nln);
        n_list->size++;
    }

    if (!feof(file))
        printf("an error interrupted the read \n");

    fclose(file);

    return n_list;
}

HuNounData *process_noun_line_hu(char *ptr)
{
    int idx = 0;

    HuNounData *nd = malloc(sizeof(HuNounData));

    nd->lvl = -1;

    while (ptr != NULL)
    {
        switch (idx++)
        {
        case 0:
            nd->serb = malloc(sizeof(char) * (strlen(ptr) + 1));
            strcpy(nd->serb, ptr);
            break;
        case 1:
            nd->sg = malloc(sizeof(char) * (strlen(ptr) + 1));
            strcpy(nd->sg, ptr);
            break;
        case 2:
            nd->pl = malloc(sizeof(char) * (strlen(ptr) + 1));
            strcpy(nd->pl, ptr);
            trim_white_space(nd->pl);
            break;
        case 3:
            if (strcmp(ptr, "c2") == 0)
                nd->lvl = 5;
            else if (strcmp(ptr, "c1") == 0)
                nd->lvl = 4;
            else if (strcmp(ptr, "b2") == 0)
                nd->lvl = 3;
            else if (strcmp(ptr, "b1") == 0)
                nd->lvl = 2;
            else if (strcmp(ptr, "a2") == 0)
                nd->lvl = 1;
            else if (strcmp(ptr, "a1") == 0)
                nd->lvl = 0;
            break;
        }

        ptr = strtok(NULL, n_delim_hu);
    }

    return nd;
}

void add_noun_list_node_hu(HuNounList *list, HuNounListNode *list_node)
{
    if (list->root == NULL)
    {
        list->root = list_node;
        list->root->next = NULL;
    }
    else
    {
        HuNounListNode *tmp = list->root;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = list_node;
        tmp->next->next = NULL;
    }
}

HuNounData get_noun_data_hu(HuNounList *list, int idx)
{
    HuNounListNode *curr = list->root;
    int curr_idx = 0;

    while (curr_idx++ < idx)
        curr = curr->next;

    return curr->noun;
}

void print_noun_list_hu(HuNounList *list)
{
    HuNounListNode *curr = list->root;

    while (curr->next != NULL)
    {
        print_noun_list_node_hu(curr);
        curr = curr->next;
    }

    print_noun_list_node_hu(curr);
}

void print_noun_list_node_hu(HuNounListNode *list_node)
{
    printf("\x1b[1m\x1b[44m[N] %-*s |\x1b[0m \n", (int)compensation(list_node->noun.serb) + N_MAX_LENGTH_HU * 2 + 27, list_node->noun.serb);

    printf("\t\x1b[1m\x1b[45m|   %-*s |   %-*s |\x1b[0m \n",
           N_MAX_LENGTH_HU + (int)compensation(list_node->noun.sg) + 7, list_node->noun.sg,
           N_MAX_LENGTH_HU + (int)compensation(list_node->noun.pl) + 7, list_node->noun.pl);

    printf("\n");
}