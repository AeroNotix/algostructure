package main

import (
	"time"
	"fmt"
	"math/rand"
	"sort"
)

type compare func(interface{}, interface{}) bool

type Tree struct {
	Left *Tree
	Value interface{}
	Right *Tree
	comp compare
	Levels int
}

func NewTree(f compare) *Tree {
	return &Tree{comp:f}
}

func (t *Tree) Add(v interface{}) bool {
	t.Levels++
	if t.Value == nil {
		t.Value = v
		return true
	}

	if t.comp(t.Value, v) {
		if t.Left == nil {
			t.Left = NewTree(t.comp)
		}
		return t.Left.Add(v)
	}

	if !t.comp(t.Value, v) {
		if t.Right == nil {
			t.Right = NewTree(t.comp)
		}
		return t.Right.Add(v)
	}
	panic("Shouldn't get here")
}

func (t *Tree) walk(ch chan<- interface{})  {
	if t.Left != nil {
		t.Left.walk(ch)
	}
	ch <- t.Value
	if t.Right != nil {
		t.Right.walk(ch)
	}
}

func (t *Tree) Walk() []interface{} {
	ch := make(chan interface{}, t.Levels)

	t.walk(ch)
	close(ch)

	var ar []interface{}
	for item := range ch {
		ar = append(ar, item)
	}
	return ar
}

func main() {
	t := NewTree(func (current, newval interface{}) bool {
		if current.(int) < newval.(int) {
			return false
		}
		return true
	})

	t2 := NewTree(func (current, newval interface{}) bool {
		if current.(int) < newval.(int) {
			return false
		}
		return true
	})

	t3 := NewTree(func (current, newval interface{}) bool {
		if current.(int) < newval.(int) {
			return false
		}
		return true
	})

	intslice := make([]int, 0, 100000)
	for x := 0; x < 100000; x++ {
		intslice = append(intslice, x)
	}
	intslice2 := make([]int, 0, 100000)
	for x := 0; x < 100000; x++ {
		intslice2 = append(intslice2, x)
	}
	intslice3 := make([]int, 0, 100000)
	for x := 0; x < 100000; x++ {
		intslice3 = append(intslice3, x)
	}

	r := RandomSlice{intslice}
	r2 := RandomSlice{intslice2}
	sort.Sort(r)
	sort.Sort(r2)

	ti := time.Now()
	for _, num := range r.Slice {
		t.Add(num)
	}
	fmt.Println(time.Now().Sub(ti))

	ti = time.Now()
	for _, num := range r2.Slice {
		t2.Add(num)
	}
	fmt.Println(time.Now().Sub(ti))

	ti = time.Now()
	for _, num := range intslice3 {
		t3.Add(num)
	}
	fmt.Println(time.Now().Sub(ti))

	ti = time.Now()
	t.Walk()
	fmt.Println(time.Now().Sub(ti))
	ti = time.Now()
	t2.Walk()
	fmt.Println(time.Now().Sub(ti))
	ti = time.Now()
	t3.Walk()
	fmt.Println(time.Now().Sub(ti))
}

type RandomSlice struct {
	Slice []int
}

func (r RandomSlice) Len() int {
	return len(r.Slice)
}

func (RandomSlice) Less(i, j int) bool {
	d := rand.Intn(2)
	if d == 1 { return true }
	return false
}

func (r RandomSlice) Swap(i, j int) {
	r.Slice[i], r.Slice[j] = r.Slice[j], r.Slice[i]
}