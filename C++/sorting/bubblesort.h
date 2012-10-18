#include <iostream>
#include <vector>
#include <stdlib.h>
#include "sortutils.h"

template <typename T>
T bubblesort(T& vec) {
    auto f = vec.begin();
    auto s = vec.begin();
    ++s;
    bool swapped = false;
    while (s != vec.end()) {
	if (*f > *s) {
	    swap(*f, *s);
	    swapped = true;
	}
	++f; ++s;
    }
    if (swapped) {
	bubblesort(vec);
    }
    return vec;
}
