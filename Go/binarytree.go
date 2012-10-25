package main

import (
	"math/rand"
)

type compare func(interface{}, interface{}) bool

type Tree struct {
	Left   *Tree
	Value  interface{}
	Right  *Tree
	comp   compare
	Levels int
}

func NewTree(f compare) *Tree {
	return &Tree{comp: f}
}

func (t *Tree) Add(v interface{}) bool {
	t.Levels++

	var node *Tree = t
	for node.Value != nil {
		if node.comp(node.Value, v) {
			node = node.Left
		} else {
			node = node.Right
		}
	}

	node.Value = v
	node.Left = NewTree(t.comp)
	node.Right = NewTree(t.comp)
	return true
}

func (t *Tree) walk() {
	if t.Left.Value != nil {
		t.Left.walk()
	}
	if t.Right.Value != nil {
		t.Right.walk()
	}
}

func (t *Tree) Walk() {
	t.walk()
}

func main() {
	t := NewTree(func(current, newval interface{}) bool {
		if current.(int) < newval.(int) {
			return false
		}
		return true
	})

	for x := 0; x < 1000000; x++ {
		t.Add(rand.Intn(x + 1))
	}
}
