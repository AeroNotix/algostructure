#include <iostream>
#include <vector>
#include <iterator>

template <typename T>
T quicksort(T vec) {
    if (vec.size() <= 1) {
	return vec;
    }

    auto begin = vec.begin();
    // we will advance this middle pointer
    auto middle = vec.begin();
    auto end = vec.end();

    // advance the middle pointer to be the mid-point of the whole
    // container.
    std::advance(middle,std::distance(middle,end)/2);

    // create our temp containers
    std::vector<typename T::value_type> lesser;
    std::vector<typename T::value_type> greater;

    // get the middle value and remove that from the original
    auto value = *middle;
    vec.erase(middle);

    // partition our container.
    for (auto el : vec) {
	if (el <= value)
	    lesser.push_back(el);
	else
	    greater.push_back(el);
    }

    std::vector<typename T::value_type> out;

    // recursively sort the remainders
    auto newl = quicksort(lesser);
    auto newg = quicksort(greater);
    out.insert(out.end(), newl.begin(), newl.end());
    out.push_back(value);
    out.insert(out.end(), newg.begin(), newg.end());

    return out;
}

int main() {
    std::vector<int> v {8,2,31,4,44,6,51,8,66,10,11,2};
    for (auto el : quicksort(v)) {
	std::cout << el << " ";
    }
    std::cout << std::endl;
    return 0;
}
