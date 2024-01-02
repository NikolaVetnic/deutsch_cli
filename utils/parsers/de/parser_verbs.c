#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../../words/de/nouns.h"
#include "../../../words/de/verbs.h"
#include "../../utils.h"

// function to parse a line and create a VerbData struct
VerbData parse_verb_line(const char *line) 
{
    VerbData vd = {0};
    
    if (strncmp(line, "(v) ", 4) == 0) {
        char *buffer = trim_white_space(strdup(line + 4));
        char *token;
        char *rest = buffer;

        token = strtok_r(rest, "-", &rest);
        vd.serb = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, "|", &rest);
        vd.inf = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, "|", &rest);
        vd.pres = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, "|", &rest);
        vd.pret = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, "|", &rest);
        vd.pp = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, "[", &rest);
        vd.hv = token ? strdup(trim_white_space(token)) : "?";

        token = token ? strtok_r(rest, "]", &rest) : "?";

        if (!token)
            vd.lvl = -1;
        else if (strcmp(token, "c2") == 0 || strcmp(token, "C2") == 0)
            vd.lvl = 5;
        else if (strcmp(token, "c1") == 0 || strcmp(token, "C1") == 0)
            vd.lvl = 4;
        else if (strcmp(token, "b2") == 0 || strcmp(token, "B2") == 0)
            vd.lvl = 3;
        else if (strcmp(token, "b1") == 0 || strcmp(token, "B1") == 0)
            vd.lvl = 2;
        else if (strcmp(token, "a2") == 0 || strcmp(token, "A2") == 0)
            vd.lvl = 1;
        else if (strcmp(token, "a1") == 0 || strcmp(token, "A1") == 0)
            vd.lvl = 0;
        else
            vd.lvl = -1;

        free(buffer);
    }

    return vd;
}

// read verbs from the markdown file and store them in VerbList
VerbList *load_verbs_from_markdown(const char *filename) 
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    VerbList *v_list = malloc(sizeof(VerbList));
	v_list->size = 0;
	v_list->root = NULL;

    char line[512];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "(v)") != NULL) {
            VerbListNode *vln = malloc(sizeof(VerbListNode));
            VerbData vd = parse_verb_line(line);

            if (strcmp(vd.serb,     "?") == 0 || 
                strcmp(vd.inf,      "?") == 0 || 
                strcmp(vd.pres,     "?") == 0 || 
                strcmp(vd.pret,     "?") == 0 || 
                strcmp(vd.pp,       "?") == 0 || 
                strcmp(vd.hv,       "?") == 0)
                continue;

            vln->verb = vd;

            add_verb_list_node(v_list, vln);
		    v_list->size++;

            print_verb_list_node(vln);
        }
    }

	if (!feof(file))
		printf("an error interrupted the read \n");

    fclose(file);

    return v_list;
}

// function to write verbs to a CSV file
void write_verbs_to_csv(const char *filename, VerbList *list) 
{
    FILE *file = fopen(filename, "w");

    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "# Serbian;infinitive;present 3rd person sg.;preterite 3rd person sg.;past participle;modal verb;level\n");

    VerbListNode *current = list->root;
    
    while (current != NULL) 
    {
        char *lvl = malloc(2 * sizeof(char));

        switch (current->verb.lvl) 
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

        fprintf(file, "%s;%s;%s;%s;%s;%s;%s\n", current->verb.serb, current->verb.inf, current->verb.pres, current->verb.pret, current->verb.pp, current->verb.hv, lvl);

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
    snprintf(outputFilename, 256, "%s%s_%s", "/Users/nikolavetnic/Documents/Code/deutsch_cli/base/_complete/de/", buffer, "verbs.csv");

    return outputFilename;
}

// free verb list
void free_verb_list(VerbList *vl) 
{
    if (vl == NULL)
        return;

    VerbListNode *current = vl->root;
    while (current != NULL) 
    {
        VerbListNode *temp = current;
        current = current->next;
        free(temp);
    }

    free(vl);
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

    printf("Parsing verbs from %s ...\n", inputFilename);

    VerbList *verbs = load_verbs_from_markdown(inputFilename);
    write_verbs_to_csv(outputFilename, verbs);

    free_verb_list(verbs);

    return 0;
}
