#ifndef ADS_H_		// include a guard
#define ADS_H_

#include <wchar.h>

typedef struct
{
	int idx;
	char *serb;
	char *word;
	int lvl;
} AdData;

typedef struct _ADLISTNODE
{
	AdData ad;
	struct _ADLISTNODE *next;
} AdListNode;

typedef struct
{
	int size;
	AdListNode *root;
} AdList;

AdList		*load_ads_from_preset(char *filename);
AdData		get_ad_data(AdList *list, int idx);
void 		add_ad_list_node(AdList *list, AdListNode *list_node);
void 		print_ad_list_node(AdListNode *list_node);
void		print_ad_list(AdList *list);

#endif					// ADS_H
