#ifndef VERBS_HU_H_	// include a guard
#define VERBS_HU_H_

typedef struct
{
	int idx;
	char *serb;
	char *pres;
	int lvl;
} HuVerbData;

typedef struct _HUVERBLISTNODE
{
	HuVerbData verb;
	struct _HUVERBLISTNODE *next;
} HuVerbListNode;

typedef struct
{
	int size;
	HuVerbListNode *root;
} HuVerbList;

HuVerbList  *load_verbs_from_preset_hu(char *filename);
HuVerbData  get_verb_data_hu(HuVerbList *list, int idx);
void 		print_verb_list_node_hu(HuVerbListNode *list_node);
void        print_verb_list_hu(HuVerbList *list);

#endif				// VERBS_HU_H_
