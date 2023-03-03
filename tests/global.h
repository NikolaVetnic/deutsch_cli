#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdbool.h>
#include <string.h>
#include <locale.h>

typedef struct ANSWER_DATA_
{
	int idx;
	float pts;
    bool should_break;
} AnswerData;

typedef struct _INPUT
{
    char content[50];
    bool is_correct;
} Input;

bool is_contained_in(int *arr, int arr_len, int num);
size_t widestrlen(const char *str);
size_t compensation(const char *str);

#endif				// GLOBAL_H_
