#include <vector>
#include <iostream>

template <typename T>
void swap(T& a, T& b) {
    T tmp = b;
    b = a;
    a = tmp;    
}

template <typename T>
void selectionSort(T &vec) {
    auto end = vec.end();
    for (auto begin = vec.begin(); begin != end; ++begin) {
	auto current = begin;

	for (auto inner = begin; inner != end; ++inner) {
	    if (*current > *inner) {
		current = inner;
	    }
	}
	swap(*begin, *current);
    }
}
