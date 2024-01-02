#ifndef EXPRESSIONS_H_		// include a guard
#define EXPRESSIONS_H_

#include <wchar.h>

typedef struct
{
	int idx;
	char *serb;
	char *word;
	int lvl;
} ExpressionData;

typedef struct _EXPRESSIONLISTNODE
{
	ExpressionData expression;
	struct _EXPRESSIONLISTNODE *next;
} ExpressionListNode;

typedef struct
{
	int size;
	ExpressionListNode *root;
} ExpressionList;

ExpressionList	*load_expressions_from_preset(char *filename);
ExpressionData	get_expression_data(ExpressionList *list, int idx);
void 			add_expression_list_node(ExpressionList *list, ExpressionListNode *list_node);
void 			print_expression_list_node(ExpressionListNode *list_node);
void			print_expression_list(ExpressionList *list);

#endif					// EXPRESSIONS_H
