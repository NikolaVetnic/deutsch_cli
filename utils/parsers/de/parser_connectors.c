#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../../words/de/connectors.h"
#include "../../utils.h"

// function to parse a line and create a ConnectorData struct
ConnectorData parse_connector_line(const char *line) 
{
    ConnectorData connector = {0};
    
    if (strncmp(line, "(c) ", 4) == 0) {
        char *buffer = trim_white_space(strdup(line + 4));
        char *token;
        char *rest = buffer;

        token = strtok_r(rest, "-", &rest);
        connector.serb = token ? strdup(trim_white_space(token)) : "?";
        rest = trim_white_space(rest);

        token = strtok_r(rest, "[", &rest);
        connector.word = token ? strdup(trim_white_space(token)) : "?";

        token = token ? strtok_r(rest, "]", &rest) : "?";

        if (!token)
            connector.lvl = -1;
        else if (strcmp(token, "c2") == 0)
            connector.lvl = 5;
        else if (strcmp(token, "c1") == 0)
            connector.lvl = 4;
        else if (strcmp(token, "b2") == 0)
            connector.lvl = 3;
        else if (strcmp(token, "b1") == 0)
            connector.lvl = 2;
        else if (strcmp(token, "a2") == 0)
            connector.lvl = 1;
        else if (strcmp(token, "a1") == 0)
            connector.lvl = 0;
        else
            connector.lvl = -1;

        printf("'%s' | '%s' | '%d' \n", connector.serb, connector.word, connector.lvl);

        free(buffer);
    }

    return connector;
}

// read nouns from the markdown file and store them in NounList
ConnectorList *load_connectors_from_markdown(const char *filename) 
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    ConnectorList *c_list = malloc(sizeof(ConnectorList));
	c_list->size = 0;
	c_list->root = NULL;

    char line[512];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "(c)") != NULL) {
            ConnectorListNode *cln = malloc(sizeof(ConnectorListNode));
            ConnectorData connector = parse_connector_line(line);

            if (strcmp(connector.serb, "?") == 0 || strcmp(connector.word, "?") == 0)
                continue;

            cln->connector = connector;

            add_connector_list_node(c_list, cln);
		    c_list->size++;

            print_connector_list_node(cln);
        }
    }

	if (!feof(file))
		printf("an error interrupted the read \n");

    fclose(file);

    return c_list;
}

// function to write connectors to a CSV file
void write_connectors_to_csv(const char *filename, ConnectorList *list) 
{
    FILE *file = fopen(filename, "w");

    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "# Serbian;German;level\n");

    // iterate over the list and write each noun to the file
    ConnectorListNode *current = list->root;
    
    while (current != NULL) 
    {
        char *lvl = malloc(2 * sizeof(char));

        switch (current->connector.lvl) 
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

        fprintf(file, "%s;%s;%s\n", current->connector.serb, current->connector.word, lvl);
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
    snprintf(outputFilename, 256, "%s%s_%s", "/Users/nikolavetnic/Documents/Code/deutsch_cli/base/_complete/de/", buffer, "connectors.csv");

    return outputFilename;
}

// free connector list
void free_connector_list(ConnectorList *list) 
{
    if (list == NULL)
        return;

    ConnectorListNode *current = list->root;
    while (current != NULL) 
    {
        ConnectorListNode *temp = current;
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

    printf("Parsing connectors from '%s' ...\n", inputFilename);

    ConnectorList *connectors = load_connectors_from_markdown(inputFilename);
    write_connectors_to_csv(outputFilename, connectors);

    free_connector_list(connectors);

    return 0;
}
