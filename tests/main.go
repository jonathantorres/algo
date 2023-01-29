package main

import (
	"fmt"

	"github.com/jonathantorres/graphs"
)

// TODO: create unit tests for these
func main() {
	g := graphs.New(false)
	g.AddEdge(0, 1, 0, g.Directed)
	g.AddEdge(0, 4, 0, g.Directed)
	g.AddEdge(1, 2, 0, g.Directed)
	g.AddEdge(1, 3, 0, g.Directed)
	g.AddEdge(1, 4, 0, g.Directed)
	g.AddEdge(2, 3, 0, g.Directed)
	g.AddEdge(3, 4, 0, g.Directed)
	fmt.Printf("%s\n", g)

	runBfs(g)
	fmt.Println()
	runDfs(g)

	// tests for the queue
	// q := graphs.NewQueue()
	// q.Enqueue(1)
	// q.Enqueue(2)
	// fmt.Printf("%v\n", q.Empty())
	// fmt.Printf("%d\n", q.Len())
	// v, _ := q.Dequeue()
	// fmt.Printf("%v\n", q.Empty())
	// fmt.Printf("%d\n", q.Len())
	// fmt.Printf("%d\n", v)

	// tests for the stack
	// s := graphs.NewStack()
	// s.Push(1)
	// s.Push(2)
	// fmt.Printf("%v\n", s.Empty())
	// fmt.Printf("%d\n", s.Len())
	// v, _ := s.Pop()
	// fmt.Printf("%d\n", v)
	// fmt.Printf("%v\n", s.Empty())
	// fmt.Printf("%d\n", s.Len())
}

func processVertex(v int) {
	fmt.Printf("process vertex: %d\n", v)
}

func processEdge(u, v int) {
	fmt.Printf("process edge: %d->%d\n", u, v)
}

func runBfs(g *graphs.Graph) {
	g.InitBFS()
	g.BFS(0, processVertex, processEdge)
	tree := g.BFSParent()
	for i, v := range tree {
		fmt.Printf("%d:%d ", i, v)
	}
	fmt.Println()
}

func runDfs(g *graphs.Graph) {
	g.DFS(0, processVertex, processEdge)
	tree := g.DFSParent()
	for i, v := range tree {
		fmt.Printf("%d:%d ", i, v)
	}
	fmt.Println()
}
