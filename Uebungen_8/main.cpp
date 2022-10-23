#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>
#include <time.h>

bool contains_Iter(const int *arr, const uint32_t arrSize, const int target) {
	for(uint32_t i = 0; i < arrSize; i++)
		if(arr[i] == target)
			return true;
	return false;
}

bool contains_Recursive(const int *arr, const uint32_t arrSize, const int target) {
	if(arrSize == 0) return false;
	if(arrSize == 1) return *arr == target;

	const uint32_t middleIndex = arrSize / 2;
	const uint32_t leftOfMiddle = middleIndex;
	const uint32_t rightOfMiddle = arrSize - leftOfMiddle - 1;

	if(arr[middleIndex] == target) return true;

	if(target < arr[middleIndex])
		return contains_Recursive(arr, leftOfMiddle, target);

	return contains_Recursive(arr + middleIndex + 1, rightOfMiddle, target);

	return false;
}

int main(int argc, char** argv) {
	srand(time(0));

	const uint32_t NUM_ZAHLEN = 100000;
	int *zahlen = (int*)malloc(sizeof(int) * NUM_ZAHLEN);
	// int *zahlen = new int[NUM_ZAHLEN];

	for(uint32_t i = 0; i < NUM_ZAHLEN; i++)
		zahlen[i] = rand() % 1000001;

	qsort(zahlen, NUM_ZAHLEN, sizeof(int), [](const void *l, const void *r)->int{
		if(*(int*)l > *(int*)r)
			return 1;
		if(*(int*)l < *(int*)r)
			return -1;
		return 0;
		});

	for(uint32_t i = 0; i < 100; i++)
		printf("Zahl %u: %d\n", i, zahlen[i]);

	printf("\nIterative search<%d>: %d\n", 15, contains_Iter(zahlen, NUM_ZAHLEN, 15));
	printf("Recursive search<%d>: %d\n", 15, contains_Recursive(zahlen, NUM_ZAHLEN, 15));

	// for(int target = 0; target < 10; target++) {
	// 	printf("\nIterative search<%d>: %d\n", target, contains_Iter(zahlen, NUM_ZAHLEN, target));
	// 	printf("Recursive search<%d>: %d\n", target, contains_Recursive(zahlen, NUM_ZAHLEN, target));
	// }

	free(zahlen);
	// delete[] zahlen;

	return 0;
}