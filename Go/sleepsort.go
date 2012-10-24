package main

import (
	"fmt"
	"math/rand"
	"time"
)

func SleepSort(arr []int) []int {
	gather := make(chan int)
	for _, num := range arr {
		emit(num, gather)
	}
	out := make([]int, 0, len(arr))
	for x := 0; x < 10; x++ {
		out = append(out, <-gather)
	}
	return out
}

func emit(val int, to chan int) {
	go func() {
		ch := time.After(time.Duration(val) * time.Microsecond)
		<-ch
		to <- val
	}()
}

func isSorted(nums []int) bool {

	old := nums[0]
	for _, num := range nums {
		if num < old {
			fmt.Println(num, old)
			return false
		}
	}
	return true
}

func main() {
	var randints []int

	for i := 0; i < 100000; i++ {
		randints = append(randints, rand.Intn(10000))
	}

	fmt.Println(isSorted(SleepSort(randints)))
}
