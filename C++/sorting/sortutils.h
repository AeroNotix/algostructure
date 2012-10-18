#ifndef SORTUTILS
template <typename T>
void swap(T& a, T& b) {
    T tmp = b;
    b = a;
    a = tmp;    
}
#define SORTUTILS
#endif
