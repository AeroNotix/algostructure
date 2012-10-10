#include <iostream>
#include <vector>
#include <stdlib.h>

template <typename T>
void swap(T& a, T& b) {
    T tmp = b;
    b = a;
    a = tmp;    
}

template <typename T>
void bubblesort(T& vec) {
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
}
