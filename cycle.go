package graphs

func (g *Graph) HasCycle() bool {
	var cycle bool
	var processEdge func(int, int)

	processEdge = func(x int, y int) {
		if g.vertexStates[y] == discovered && g.dfsParent[x] != y {
			cycle = true
		}
	}

	g.InitDFS()
	g.DFS(0, nil, processEdge)

	return cycle
}
