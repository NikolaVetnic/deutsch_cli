#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../../words/de/ads.h"
#include "../../../words/de/nouns.h"
#include "../../utils.h"

// function to parse a line and create a AdData struct
AdData parse_ad_line(const char *line) 
{
    AdData ad = {0};
    
    if (strncmp(line, "(a) ", 4) == 0) {
        char *buffer = trim_white_space(strdup(line + 4));
        char *token;
        char *rest = buffer;

        token = strtok_r(rest, "-", &rest);
        ad.serb = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, "[", &rest);
        ad.word = token ? strdup(trim_white_space(token)) : "?";

        token = token ? strtok_r(rest, "]", &rest) : "?";

        if (!token)
            ad.lvl = -1;
        else if (strcmp(token, "c2") == 0)
            ad.lvl = 5;
        else if (strcmp(token, "c1") == 0)
            ad.lvl = 4;
        else if (strcmp(token, "b2") == 0)
            ad.lvl = 3;
        else if (strcmp(token, "b1") == 0)
            ad.lvl = 2;
        else if (strcmp(token, "a2") == 0)
            ad.lvl = 1;
        else if (strcmp(token, "a1") == 0)
            ad.lvl = 0;
        else
            ad.lvl = -1;

        printf("'%s' | '%s' | '%d' \n", ad.serb, ad.word, ad.lvl);

        free(buffer);
    }

    return ad;
}

// read ads from the markdown file and store them in AdList
AdList *load_ads_from_markdown(const char *filename) 
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    AdList *a_list = malloc(sizeof(AdList));
	a_list->size = 0;
	a_list->root = NULL;

    char line[512];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "(a)") != NULL) {
            AdListNode *aln = malloc(sizeof(AdListNode));
            AdData ad = parse_ad_line(line);

            if (strcmp(ad.serb, "?") == 0 || strcmp(ad.word, "?") == 0)
                continue;

            aln->ad = ad;

            add_ad_list_node(a_list, aln);
		    a_list->size++;

            print_ad_list_node(aln);
        }
    }

	if (!feof(file))
		printf("an error interrupted the read \n");

    fclose(file);

    return a_list;
}

// function to write ads to a CSV file
void write_ads_to_csv(const char *filename, AdList *list) 
{
    FILE *file = fopen(filename, "w");

    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "# Serbian;German;level\n");

    // iterate over the list and write each noun to the file
    AdListNode *current = list->root;
    
    while (current != NULL) 
    {
        char *lvl = malloc(2 * sizeof(char));

        switch (current->ad.lvl) 
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

        fprintf(file, "%s;%s;%s\n", current->ad.serb, current->ad.word, lvl);
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
    snprintf(outputFilename, 256, "%s%s_%s", "/Users/nikolavetnic/Documents/Code/deutsch_cli/base/_complete/de/", buffer, "ads.csv");

    return outputFilename;
}

// free ad list
void free_ad_list(AdList *list) 
{
    if (list == NULL)
        return;

    AdListNode *current = list->root;
    while (current != NULL) 
    {
        AdListNode *temp = current;
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

    printf("Parsing adjectives and adverbs from '%s' ...\n", inputFilename);

    AdList *ads = load_ads_from_markdown(inputFilename);
    write_ads_to_csv(outputFilename, ads);

    free_ad_list(ads);

    return 0;
}
