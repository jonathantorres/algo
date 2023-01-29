package graphs

import (
	"bytes"
	"fmt"
)

type EdgeNode struct {
	n      int
	weight int
	next   *EdgeNode
}

type Graph struct {
	Directed    bool
	numVertices int
	numEdges    int
	edges       map[int]EdgeNode
	degree      []int

	vertexStates []int
	bfsParent    []int // tree of discovery
	dfsParent    []int // tree of discovery
	dfsEntry     []int
	dfsExit      []int
}

func New(directed bool) *Graph {
	return &Graph{
		Directed: directed,
		edges:    make(map[int]EdgeNode),
		degree:   make([]int, 10),
	}
}

func (g *Graph) AddEdge(from, to int, weight int, directed bool) {
	edgeNode := EdgeNode{
		n:      to,
		weight: weight,
	}

	edge, ok := g.edges[from]
	if ok {
		// add EdgeNode to adjacency list
		curEdge := &edge

		for {
			if curEdge.next == nil {
				break
			}
			curEdge = curEdge.next
		}
		curEdge.next = &edgeNode
		g.edges[from] = edge
	} else {
		// new entry
		g.edges[from] = edgeNode
		g.numVertices++
	}

	// update degree
	if g.numVertices == cap(g.degree) {
		newDegrees := make([]int, len(g.degree)+1, len(g.degree)*2)
		copy(newDegrees, g.degree)
		g.degree = newDegrees
	}

	g.degree[from]++

	if directed {
		g.numEdges++
	} else {
		g.AddEdge(to, from, weight, true)
	}
}

func (g *Graph) deleteEdge(n int) {
	// TODO
}

func (g *Graph) deleteVertex(n int) {
	// TODO
}

const (
	undiscovered = iota
	discovered
	processed
)

func (g *Graph) InitBFS() {
	g.vertexStates = make([]int, g.numVertices)
	g.bfsParent = make([]int, g.numVertices)

	for v, _ := range g.edges {
		g.vertexStates[v] = undiscovered
		g.bfsParent[v] = -1
	}
}

func (g *Graph) BFS(start int, processVertex func(int), processEdge func(int, int)) {
	// make sure to run InitBFS() first
	g.vertexStates[start] = discovered
	g.bfsParent[start] = -1 // root

	queue := NewQueue()
	queue.Enqueue(start)

	for !queue.Empty() {
		v, _ := queue.Dequeue()
		vertex := v.(int)

		if processVertex != nil {
			processVertex(vertex)
		}

		edge := g.edges[vertex]
		currentEdge := &edge

		for currentEdge != nil {
			n := currentEdge.n

			if processEdge != nil {
				processEdge(vertex, n)
			}

			if g.vertexStates[n] == undiscovered {
				g.vertexStates[n] = discovered
				g.bfsParent[n] = vertex
				queue.Enqueue(n)
			}
			currentEdge = currentEdge.next
		}
		g.vertexStates[vertex] = processed
	}
}

func (g *Graph) InitDFS() {
	g.dfsParent = make([]int, g.numVertices)
	g.vertexStates = make([]int, g.numVertices)
	g.dfsEntry = make([]int, g.numVertices)
	g.dfsExit = make([]int, g.numVertices)

	for v, _ := range g.edges {
		g.vertexStates[v] = undiscovered
		g.dfsEntry[v] = -1
		g.dfsExit[v] = -1
		g.dfsParent[v] = -1
	}
}

func (g *Graph) DFS(start int, processVertexEarly func(int), processVertexLate func(int), processEdge func(int, int)) {
	// make sure to run InitDFS() first
	time := 1
	var dfs func(int)
	dfs = func(v int) {
		g.vertexStates[v] = discovered

		if processVertexEarly != nil {
			processVertexEarly(v)
		}

		g.dfsEntry[v] = time
		time++
		edge := g.edges[v]
		currentEdge := &edge

		for currentEdge != nil {
			n := currentEdge.n

			if processEdge != nil {
				processEdge(v, n)
			}

			if g.vertexStates[n] == undiscovered {
				g.dfsParent[n] = v
				dfs(n)
			}
			currentEdge = currentEdge.next
		}

		if processVertexLate != nil {
			processVertexLate(v)
		}

		g.vertexStates[v] = processed
		g.dfsExit[v] = time
		time++
	}

	dfs(start)
}

func (g *Graph) DFSIter(start int, processVertex func(int), processEdge func(int, int)) {
	g.dfsParent = make([]int, g.numVertices)
	g.vertexStates = make([]int, g.numVertices)
	g.dfsEntry = make([]int, g.numVertices)
	g.dfsExit = make([]int, g.numVertices)

	for v, _ := range g.edges {
		g.vertexStates[v] = undiscovered
		g.dfsEntry[v] = -1
		g.dfsExit[v] = -1
		g.dfsParent[v] = -1
	}

	time := 1
	stack := NewStack()
	stack.Push(start)

	for !stack.Empty() {
		v, _ := stack.Pop()
		vertex := v.(int)

		if g.vertexStates[vertex] == undiscovered {
			g.vertexStates[vertex] = discovered
			g.dfsEntry[vertex] = time

			if processVertex != nil {
				processVertex(vertex)
			}

			edge := g.edges[vertex]
			currentEdge := &edge

			for currentEdge != nil {
				n := currentEdge.n

				if processEdge != nil {
					processEdge(vertex, n)
				}

				if g.vertexStates[n] == undiscovered {
					g.dfsParent[n] = vertex
				}

				stack.Push(n)
				currentEdge = currentEdge.next
			}
		} else {
			g.vertexStates[vertex] = processed
			g.dfsExit[vertex] = time
		}

		time++
	}
}

func (g *Graph) BFSParent() []int {
	return g.bfsParent
}

func (g *Graph) DFSParent() []int {
	return g.dfsParent
}

func (g *Graph) String() string {
	var buf bytes.Buffer
	for v, edge := range g.edges {
		buf.WriteString(fmt.Sprintf("%d: ", v))
		curEdge := &edge

		for {
			if curEdge == nil {
				break
			}

			buf.WriteString(fmt.Sprintf("%d(%d)->", curEdge.n, curEdge.weight))
			curEdge = curEdge.next
		}
		buf.WriteByte('\n')
	}

	buf.WriteString(fmt.Sprintf("degrees: %v\n", g.degree))

	return buf.String()
}
