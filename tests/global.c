#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

bool is_contained_in(int *arr, int arr_len, int num);
size_t widestrlen(const char *str);
size_t compensation(const char *str);

bool is_contained_in(int *arr, int arr_len, int num)
{
	for (int i = 0; i < arr_len; i++)
		if (arr[i] == num)
			return true;

	return false;
}

size_t widestrlen(const char *str)
{
	return mbstowcs(NULL, str, strlen(str));
}

size_t compensation(const char *str)
{
	return strlen(str) - widestrlen(str);
}