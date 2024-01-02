#ifndef CONNECTORS_H_		// include a guard
#define CONNECTORS_H_

#include <wchar.h>

typedef struct
{
	int idx;
	char *serb;
	char *word;
	int lvl;
} ConnectorData;

typedef struct _CONNECTORLISTNODE
{
	ConnectorData connector;
	struct _CONNECTORLISTNODE *next;
} ConnectorListNode;

typedef struct
{
	int size;
	ConnectorListNode *root;
} ConnectorList;

ConnectorList	*load_connectors_from_preset(char *filename);
ConnectorData	get_connector_data(ConnectorList *list, int idx);
void 			add_connector_list_node(ConnectorList *list, ConnectorListNode *list_node);
void 			print_connector_list_node(ConnectorListNode *list_node);
void			print_connector_list(ConnectorList *list);

#endif					// CONNECTORS_H
