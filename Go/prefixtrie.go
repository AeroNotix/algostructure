package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

type Node struct {
	prefix string
	Nodes  []*Node
}

// CommonPrefix finds the common prefix between two strings
//
// Example:
//
// ok, pre := CommonPrefix("Hello", "Hi")
// fmt.Println(ok, pre)
// >>> true, H
func CommonPrefix(s1, s2 string) (bool, string) {
	var use string
	if len(s1) < len(s2) {
		use = s1
	} else {
		use = s2
	}

	var x int
	for ; x < len(use); x++ {
		if s1[x] != s2[x] {
			break
		}
	}
	if x == 0 {
		return false, ""
	}
	return true, use[:x]
}

// Returns a new Node with nodes as subnodes
func New(prefix string, nodes ...*Node) *Node {
	return &Node{prefix, nodes}
}

// Inserts a string where the string is correctly supposed to go.
//
// Will rearrange the tree according to the newly inserted node.
func (n *Node) Insert(s string) {
	for idx, node := range n.Nodes {
		if ok, sub := CommonPrefix(node.prefix, s); ok {
			if sub == node.prefix {
				node.Insert(s[len(sub):])
				return
			}
			// changes N.Nodes[idx] prefix to the shorter
			// version
			n.Nodes[idx].prefix = n.Nodes[idx].prefix[len(sub):]
			// makes a new Node and puts the previous one
			// under it.
			n.Nodes[idx] = New(sub, n.Nodes[idx])
			n.Nodes[idx].Insert(s[len(sub):])
			return
		}
	}
	n.AddNode(s)
}

// Inserts a node directly to a node without trying to insert
// it according to the prefix rules.
func (n *Node) AddNode(s string) {
	n.Nodes = append(n.Nodes, &Node{s, []*Node{}})
}

// Creates a []string with all the entries which have a certain
// prefix.
func (n *Node) WithPrefix(s string) []string {
	var out []string
	for _, node := range n.Nodes {
		ok, sub := CommonPrefix(s, node.prefix)
		if ok && (sub != s) {
			subnodes := node.withPrefix(s[len(sub):])
			for idx := 0; idx < len(subnodes); idx++ {
				if len(s) == 1 {
					continue
				}
				subnodes[idx] = s[:len(s)-1] + subnodes[idx]
			}
			return subnodes
		}
		if ok && (sub == s) {
			return node.Subnodes()
		}
	}

	return out
}

func (n *Node) withPrefix(s string) []string {
	for _, node := range n.Nodes {
		ok, sub := CommonPrefix(s, node.prefix)
		if ok && (sub != s) {
			return node.withPrefix(s[len(sub):])
		}
		if ok && (sub == s) {
			subnodes := node.Subnodes()
			return subnodes
		}
	}

	return []string{}
}

func (n *Node) Subnodes() []string {
	var out []string
	out = append(out, n.prefix)
	for _, node := range n.Nodes {
		out = append(out, node.subnodes(n.prefix)...)
	}
	return out
}

func (n *Node) subnodes(pre string) []string {
	var out []string
	if len(n.Nodes) == 0 {
		out = append(out, pre+n.prefix)
	}
	for _, node := range n.Nodes {
		out = append(out, node.subnodes(pre+n.prefix)...)
	}
	return out
}

func (n Node) String() string {

	var out string
	for _, node := range n.Nodes {
		out += node.Display(0) + "\n"
	}
	return out
}

func (n Node) Display(numtabs int) string {
	var out string
	tabs := strings.Repeat("\t", numtabs)
	out += fmt.Sprintf("\n%sNode with prefix: %s\n", tabs, n.prefix)
	for _, node := range n.Nodes {
		if len(node.Nodes) > 0 {
			out += node.Display(numtabs + 1)
			continue
		}
		out += tabs + "Subnode: " + node.prefix + "\n"
	}
	return out
}

func MapWithPrefix(m map[string]bool, s string) []string {
	var out []string
	for val, _ := range m {
		if strings.HasPrefix(val, s) {
			out = append(out, val)
		}
	}
	return out
}

func main() {
	fin, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Println(err)
	}
	fdata, err := ioutil.ReadAll(fin)
	if err != nil {
		fmt.Println(err)
	}
	strs := strings.Split(string(fdata), "\n")

	root := &Node{}
	for _, str := range strs {
		root.Insert(str)
	}

}
