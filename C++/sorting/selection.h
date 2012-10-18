#include <vector>
#include <iostream>
#include "sortutils.h"

template <typename T>
T selectionsort(T &vec) {
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
    return vec;
}
