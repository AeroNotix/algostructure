package main

import (
	"math/rand"
)

func quicksort(vec []int) []int {
	if len(vec) <= 1 {
		return vec
	}

	middlepos := len(vec) / 2
	middle := vec[middlepos]

	var lesser []int
	var greater []int

	newvec := append(vec[:middlepos], vec[middlepos+1:]...)

	for _, el := range newvec {
		if el <= middle {
			lesser = append(lesser, el)
			continue
		}
		greater = append(greater, el)
	}

	var out []int
	lvals := quicksort(lesser)
	gvals := quicksort(greater)
	out = append(out, lvals...)
	out = append(out, middle)
	out = append(out, gvals...)
	return out
}

func main() {
	var vec = []int{}

	for x := 0; x < 1000000; x++ {
		vec = append(vec, rand.Intn(1000000))
	}

	quicksort(vec)
}
