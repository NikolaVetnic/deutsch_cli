#ifndef NOUNS_HU_H_		// include a guard
#define NOUNS_HU_H_

#include <wchar.h>

typedef struct
{
	int idx;
	char *serb;
	char *sg;
	char *pl;
	int lvl;
} HuNounData;

typedef struct _HUNOUNLISTNODE
{
	HuNounData noun;
	struct _HUNOUNLISTNODE *next;
} HuNounListNode;

typedef struct
{
	int size;
	HuNounListNode *root;
} HuNounList;

HuNounList  *load_nouns_from_preset_hu(char *filename);
HuNounData  get_noun_data_hu(HuNounList *list, int idx);
void        print_noun_list_node_hu(HuNounListNode *list_node);
void        print_noun_list_hu(HuNounList *list);

#endif					// NOUNS_HU_H_