package main

import (
	"fmt"
)

func tail(li []int) int {
	return li[len(li)-1]
}

func head(li []int) int {
	return li[0]
}

func search(piece int, in []int) int {
	if len(in) == 3 {
		for idx, item := range in {
			if item == piece {
				return idx
			}
		}
		return -1
	}
	if len(in) == 1 {
		if in[0] == piece {
			return 0
		}
		return -1
	}
	if len(in) == 0 {
		return -1
	}
	if head(in) == piece {
		return 0
	}
	if tail(in) == piece {
		return len(in) - 1
	}
	return binsearch(piece, in, 0, len(in)-1)
}

func binsearch(piece int, in []int, ubound, lbound int) int {

	if in[ubound] == piece {
		return ubound
	}
	if in[lbound] == piece {
		return lbound
	}
	if ubound >= lbound {
		return -1
	}

	mid := ubound + lbound/2
	if in[mid] == piece {
		return mid
	}
	if in[mid] > piece {
		return binsearch(piece, in, lbound, mid-1)
	}
	return binsearch(piece, in, mid+1, ubound)

}

func main() {
	do_tests()
}

func do_tests() {
	assert_equal(-1, search(3, []int{}))
	fmt.Printf("Test %d passed\n", 1)
	assert_equal(-1, search(3, []int{1}))
	fmt.Printf("Test %d passed\n", 2)
	assert_equal(0, search(1, []int{1}))
	fmt.Printf("Test %d passed\n", 3)
	assert_equal(0, search(1, []int{1, 3, 5}))
	fmt.Printf("Test %d passed\n", 4)
	assert_equal(1, search(3, []int{1, 3, 5}))
	fmt.Printf("Test %d passed\n", 5)
	assert_equal(2, search(5, []int{1, 3, 5}))
	fmt.Printf("Test %d passed\n", 6)
	assert_equal(-1, search(0, []int{1, 3, 5}))
	fmt.Printf("Test %d passed\n", 7)
	assert_equal(-1, search(2, []int{1, 3, 5}))
	fmt.Printf("Test %d passed\n", 8)
	assert_equal(-1, search(4, []int{1, 3, 5}))
	fmt.Printf("Test %d passed\n", 9)
	assert_equal(-1, search(6, []int{1, 3, 5}))
	fmt.Printf("Test %d passed\n", 10)
	assert_equal(0, search(1, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 11)
	assert_equal(1, search(3, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 12)
	assert_equal(2, search(5, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 13)
	assert_equal(3, search(7, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 14)
	assert_equal(-1, search(0, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 15)
	assert_equal(-1, search(2, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 16)
	assert_equal(-1, search(4, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 17)
	assert_equal(-1, search(6, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 18)
	assert_equal(-1, search(8, []int{1, 3, 5, 7}))
	fmt.Printf("Test %d passed\n", 19)
}

func assert_equal(a, b int) {
	if a != b {
		panic(fmt.Sprintf("Fail test! Got %d when the answer was %d", b, a))
	}
}
