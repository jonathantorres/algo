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

	// test for connected components
	fmt.Printf("connected components: %d\n", g.ConnectedComponents())

	// test for connected components
	comp := graphs.New(false)
	comp.AddEdge(0, 1, 0, comp.Directed)
	comp.AddEdge(0, 2, 0, comp.Directed)
	comp.AddEdge(1, 2, 0, comp.Directed)
	comp.AddEdge(3, 4, 0, comp.Directed)
	fmt.Printf("connected components: %d\n", comp.ConnectedComponents())

	// test for bipartite graph
	colors, bipartite := g.TwoColoring()
	fmt.Printf("%v\n", colors)
	fmt.Printf("%v\n", bipartite)

	// test for bipartite graph
	g2 := graphs.New(false)
	g2.AddEdge(0, 1, 0, g2.Directed)
	g2.AddEdge(2, 3, 0, g2.Directed)
	g2.AddEdge(4, 5, 0, g2.Directed)
	colors, bipartite = g2.TwoColoring()
	fmt.Printf("%v\n", colors)
	fmt.Printf("%v\n", bipartite)

	// test for cycle
	fmt.Printf("has cycle: %v\n", g.HasCycle())
	fmt.Printf("has cycle: %v\n", g2.HasCycle())

	// test for topological sort
	g3 := graphs.New(true)
	g3.AddEdge(0, 1, 0, g3.Directed)
	g3.AddEdge(1, 2, 0, g3.Directed)
	g3.AddEdge(1, 3, 0, g3.Directed)
	g3.AddEdge(1, 4, 0, g3.Directed)
	g3.AddEdge(2, 4, 0, g3.Directed)
	g3.AddEdge(3, 4, 0, g3.Directed)
	g3.AddEdge(4, 5, 0, g3.Directed)
	g3.AddEdge(5, 6, 0, g3.Directed)
	fmt.Printf("topo sort: %v\n", g3.TopoSort())

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
	g.InitDFS()
	g.DFS(0, processVertex, nil, processEdge)
	tree := g.DFSParent()
	for i, v := range tree {
		fmt.Printf("%d:%d ", i, v)
	}
	fmt.Println()
}
