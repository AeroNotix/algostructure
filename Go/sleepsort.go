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
		ch := time.After(time.Duration(val) * time.Millisecond)
		<-ch
		to <- val
	}()
}

func main() {
	var randints []int

	for i := 0; i < 10; i++ {
		randints = append(randints, rand.Intn(100))
	}

	for _, item := range SleepSort(randints) {
		fmt.Println(item)
	}
}
