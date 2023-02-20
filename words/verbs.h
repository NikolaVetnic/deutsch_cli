#ifndef VERBS_H_	// include a guard
#define VERBS_H_

typedef struct
{
	int idx;
	char *serb;
	char *inf;
	char *pres;
	char *pret;
	char *pp;
} VerbData;

typedef struct _VERBLISTNODE
{
	VerbData verb;
	struct _VERBLISTNODE *next;
} VerbListNode;

typedef struct
{
	int size;
	VerbListNode *root;
} VerbList;

VerbList    *load_verbs_from_preset(char *filename);
VerbData    get_data(VerbList *list, int idx);
void        print_verb_list(VerbList *list);

#endif				// VERBS_H_
