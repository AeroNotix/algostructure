package main

import (
	"fmt"
	"math/rand"
	"time"
)

func emit(val int, to chan int) {
	go func() {
		ch := time.After(time.Duration(val) * time.Microsecond)
		<-ch
		to <- val
	}()
}

func main() {
	var randints []int

	for i := 0; i < 10; i++ {
		randints = append(randints, rand.Intn(100))
	}
	gather := make(chan int)
	for _, num := range randints {
		emit(num, gather)
	}

	for x := 0; x < 10; x++ {
		fmt.Println(<-gather)
	}
}
