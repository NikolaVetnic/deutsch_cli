#ifndef NOUNS_H_		// include a guard
#define NOUNS_H_

#include <wchar.h>

typedef struct
{
	int idx;
	char *serb;
	char *sg;
	char *pl;
	char *art;
} NounData;

typedef struct _NOUNLISTNODE
{
	NounData noun;
	struct _NOUNLISTNODE *next;
} NounListNode;

typedef struct
{
	int size;
	NounListNode *root;
} NounList;

NounList	*load_nouns_from_preset(char *filename);
NounData	get_noun_data(NounList *list, int idx);
void 		print_noun_list_node(NounListNode *list_node);
void		print_noun_list(NounList *list);

#endif					// NOUNS_H_
