package graphs

import "fmt"

func (g *Graph) TopoSort() []int {
	var sort []int
	stack := NewStack()

	processVertexLate := func(v int) {
		stack.Push(v)
	}

	processEdge := func(x, y int) {
		class := g.classifyEdge(x, y)

		if class == backEdge {
			panic(fmt.Sprintf("WARNING: found back edge (cycle) on %d->%d\n", x, y))
		}
	}

	g.InitDFS()

	for v, _ := range g.edges {
		if g.vertexStates[v] == undiscovered {
			g.DFS(v, nil, processVertexLate, processEdge)
		}
	}

	for !stack.Empty() {
		v, _ := stack.Pop()
		vertex, ok := v.(int)

		if ok {
			sort = append(sort, vertex)
		}
	}

	return sort
}
