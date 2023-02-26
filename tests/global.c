#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"

bool is_contained_in(int *arr, int arr_len, int num);

bool is_contained_in(int *arr, int arr_len, int num)
{
	for (int i = 0; i < arr_len; i++)
		if (arr[i] == num)
			return true;

	return false;
}
