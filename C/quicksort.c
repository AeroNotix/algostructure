#include <stdio.h>

void swap(int vec[], int a, int b) {
	int tmp = vec[a];
	vec[a] = vec[b];
	vec[b] = tmp;
}

int partition(int vec[], int left, int right, int piv) {
	int pval = vec[piv];

	swap(vec, piv, right);

	int i;
	int store = left;
	for (i = left; i <= (right - 1); ++i) {
		if (vec[i] < pval) {
			swap(vec,i,store);
			++store;
		}
	}

	swap(vec, right, store);
	return store;
}

void quicksort(int vec[], int left, int right) {
	if (left < right) {
		int middle = (left + right) / 2;
		int newp = partition(vec, left, right, middle);
		quicksort(vec, left, newp - 1);
		quicksort(vec, newp + 1, right);
	}
}

int main() {
	int vec[15] = {123,1,0,4,41,6,11,12,421,12,1132,5,22,14,15};
	quicksort(vec, 0, 14);
	int x;
	printf("[");
	for (x = 0; x < 15; ++x) {
		printf("%d  ", vec[x]);
	}
	printf("]\n");
}
