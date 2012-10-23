#include <stdio.h>

void swap(int vec[], int a, int b) {
    int tmp = vec[a];
    vec[a] = vec[b];
    vec[b] = tmp;
}

void bubblesort(int vec[], int length) {
    int swapped = 0;
    while (1) {
	int idx;
	swapped = 0;
	for (idx = 0; idx < length; ++idx) {

	    if (vec[idx] > vec[idx + 1]) {
		swap(vec, idx, idx+1);
		swapped = 1;
	    }
	}
	if (swapped == 0)
	    break;
    }

    return;
}

int main() {
    int vec[15] = {123,1,0,4,41,6,11,12,421,12,1132,5,22,14,15};
    bubblesort(vec, 15);
    int x;
    for (x = 0; x < 15; ++x) {
	printf("%d ", vec[x]);
    }

}
