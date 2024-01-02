#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../../words/de/nouns.h"
#include "../../utils.h"

// function to parse a line and create a NounData struct
NounData parse_noun_line(const char *line) 
{
    NounData nd = {0};
    
    if (strncmp(line, "(n) ", 4) == 0) {
        char *buffer = trim_white_space(strdup(line + 4));
        char *token;
        char *rest = buffer;

        token = strtok_r(rest, "-", &rest);
        nd.serb = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, " ", &rest);
        nd.art = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, ",", &rest);
        nd.sg = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, "[", &rest);
        nd.pl = token ? strdup(trim_white_space(token)) : "?";

        token = token ? strtok_r(rest, "]", &rest) : "?";

        if (!token)
            nd.lvl = -1;
        else if (strcmp(token, "c2") == 0 || strcmp(token, "C2") == 0)
            nd.lvl = 5;
        else if (strcmp(token, "c1") == 0 || strcmp(token, "C1") == 0)
            nd.lvl = 4;
        else if (strcmp(token, "b2") == 0 || strcmp(token, "B2") == 0)
            nd.lvl = 3;
        else if (strcmp(token, "b1") == 0 || strcmp(token, "B1") == 0)
            nd.lvl = 2;
        else if (strcmp(token, "a2") == 0 || strcmp(token, "A2") == 0)
            nd.lvl = 1;
        else if (strcmp(token, "a1") == 0 || strcmp(token, "A1") == 0)
            nd.lvl = 0;
        else
            nd.lvl = -1;

        free(buffer);
    }

    return nd;
}

// read nouns from the markdown file and store them in NounList
NounList *load_nouns_from_markdown(const char *filename) 
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    NounList *n_list = malloc(sizeof(NounList));
	n_list->size = 0;
	n_list->root = NULL;

    char line[512];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "(n)") != NULL) {
            NounListNode *nln = malloc(sizeof(NounListNode));
            NounData nd = parse_noun_line(line);

            if (strcmp(nd.serb, "?") == 0 || strcmp(nd.art, "?") == 0 || strcmp(nd.sg, "?") == 0 || strcmp(nd.pl, "?") == 0)
                continue;

            nln->noun = nd;

            add_noun_list_node(n_list, nln);
		    n_list->size++;

            print_noun_list_node(nln);
        }
    }

	if (!feof(file))
		printf("an error interrupted the read \n");

    fclose(file);

    return n_list;
}

// function to write nouns to a CSV file
void write_nouns_to_csv(const char *filename, NounList *list) 
{
    FILE *file = fopen(filename, "w");

    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "# Serbian;article;singular;plural;level\n");

    // iterate over the list and write each noun to the file
    NounListNode *current = list->root;
    
    while (current != NULL) 
    {
        char *lvl = malloc(2 * sizeof(char));

        switch (current->noun.lvl) 
        {
            case 0:
                strcpy(lvl, "A1");
                break;
            case 1:
                strcpy(lvl, "A2");
                break;
            case 2:
                strcpy(lvl, "B1");
                break;
            case 3:
                strcpy(lvl, "B2");
                break;
            case 4:
                strcpy(lvl, "C1");
                break;
            case 5:
                strcpy(lvl, "C2");
                break;
            default:
                strcpy(lvl, "?");
                break;
        }

        fprintf(file, "%s;%s;%s;%s;%s\n", current->noun.serb, current->noun.art, current->noun.sg, current->noun.pl, lvl);
        current = current->next;
    }

    fclose(file);
}

// get time based output filename
char *get_default_output_filename() 
{
    time_t now;
    struct tm *tm_info;
    char buffer[16];

    time(&now);
    tm_info = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M", tm_info);

    char *outputFilename = malloc(256 * sizeof(char)); 
    // snprintf(outputFilename, 256, "%s%s_%s", "/Users/nikolavetnic/Documents/Code/deutsch_cli/base/_complete/de/", buffer, "nouns.csv");
    snprintf(outputFilename, 256, "%s", "/Users/nikolavetnic/Documents/Code/deutsch_cli/base/_complete/de/parsed/nouns.csv");

    return outputFilename;
}

// free noun list
void free_noun_list(NounList *list) 
{
    if (list == NULL)
        return;

    NounListNode *current = list->root;
    while (current != NULL) 
    {
        NounListNode *temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}

int main(int argc, char **argv) 
{
    if (argc < 2) 
    {
        printf("Usage: %s <input_filename> [output_filename]\n", argv[0]);
        return 1;
    }

    const char *inputFilename = argv[1];
    const char *outputFilename = argc < 3 ? get_default_output_filename() : argv[2];

    printf("Parsing nouns from %s ...\n", inputFilename);

    NounList *nouns = load_nouns_from_markdown(inputFilename);
    write_nouns_to_csv(outputFilename, nouns);

    free_noun_list(nouns);

    return 0;
}
