#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../tests/global.h"
#include "verbs_hu.h"

char v_delim_hu[] = ";";
int V_MAX_LENGTH_HU = 30;

HuVerbList *load_verbs_from_preset_hu(char *filename);
HuVerbData *process_verb_line_hu(char *ptr);
void add_verb_list_node_hu(HuVerbList *list, HuVerbListNode *list_node);
HuVerbData get_verb_data_hu(HuVerbList *list, int idx);
void print_verb_list_hu(HuVerbList *list);
void print_verb_list_node_hu(HuVerbListNode *list_node);

HuVerbList *load_verbs_from_preset_hu(char *filename)
{
    FILE *file = fopen(filename, "r");

    HuVerbList *v_list = malloc(sizeof(HuVerbList));
    v_list->size = 0;
    v_list->root = NULL;

    char buf[500];

    while (fgets(buf, sizeof buf, file) != NULL)
    {
        if (buf[0] == '#')
            continue;

        buf[strcspn(buf, "\n")] = '\0';

        char *ptr = strtok(buf, v_delim_hu);

        HuVerbListNode *vln = malloc(sizeof(HuVerbListNode));
        HuVerbData *vd = process_verb_line_hu(ptr);
        vln->verb = *vd;

        add_verb_list_node_hu(v_list, vln);
        v_list->size++;
    }

    if (!feof(file))
        printf("an error interrupted the read \n");

    fclose(file);

    return v_list;
}

HuVerbData *process_verb_line_hu(char *ptr)
{
    int idx = 0;

    HuVerbData *vd = malloc(sizeof(HuVerbData));

    while (ptr != NULL)
    {
        switch (idx++)
        {
        case 0:
            vd->serb = malloc(sizeof(char) * strlen(ptr) + 1);
            strcpy(vd->serb, ptr);
            break;
        case 1:
            vd->pres = malloc(sizeof(char) * strlen(ptr) + 1);
            strcpy(vd->pres, ptr);
            break;
        case 2:
            if (strcmp(ptr, "c2") == 0)
                vd->lvl = 5;
            else if (strcmp(ptr, "c1") == 0)
                vd->lvl = 4;
            else if (strcmp(ptr, "b2") == 0)
                vd->lvl = 3;
            else if (strcmp(ptr, "b1") == 0)
                vd->lvl = 2;
            else if (strcmp(ptr, "a2") == 0)
                vd->lvl = 1;
            else if (strcmp(ptr, "a1") == 0)
                vd->lvl = 0;
            break;
        }

        ptr = strtok(NULL, v_delim_hu);
    }

    return vd;
}

void add_verb_list_node_hu(HuVerbList *list, HuVerbListNode *list_node)
{
    if (list->root == NULL)
    {
        list_node->verb.idx = 0;
        list_node->next = NULL;
        list->root = list_node;
    }
    else
    {
        HuVerbListNode *curr = list->root;
        int idx = 1;

        while (curr->next != NULL)
        {
            curr = curr->next;
            idx++;
        }

        list_node->verb.idx = idx;
        list_node->next = curr->next;
        curr->next = list_node;
    }
}

HuVerbData get_verb_data_hu(HuVerbList *list, int idx)
{
    HuVerbListNode *curr = list->root;
    int curr_idx = 0;

    while (curr_idx++ < idx)
        curr = curr->next;

    return curr->verb;
}

void print_verb_list_hu(HuVerbList *list)
{
    HuVerbListNode *curr = list->root;

    while (curr->next != NULL)
    {
        print_verb_list_node_hu(curr);
        curr = curr->next;
    }

    print_verb_list_node_hu(curr);
}

void print_verb_list_node_hu(HuVerbListNode *list_node)
{
    printf("\x1b[1m\x1b[44m[V] %-*s |\x1b[0m \n", (int)compensation(list_node->verb.serb) + V_MAX_LENGTH_HU + 61, list_node->verb.serb);

    printf("\t\x1b[1m\x1b[45m|   %-*s |\x1b[0m \n",
           V_MAX_LENGTH_HU * 2 + 23 + (int)compensation(list_node->verb.pres), list_node->verb.pres);

    printf("\n");
}