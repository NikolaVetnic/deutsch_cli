#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdbool.h>

typedef struct ANSWER_DATA_
{
	int idx;
	float pts;
} AnswerData;

typedef struct _INPUT
{
    char content[50];
    bool is_correct;
} Input;

bool is_contained_in(int *arr, int arr_len, int num);

#endif				// GLOBAL_H_
