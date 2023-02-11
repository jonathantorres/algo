package graphs

func (g *Graph) ConnectedComponents() int {
	var count int

	g.InitBFS()

	for v, _ := range g.edges {
		if g.vertexStates[v] == undiscovered {
			g.BFS(v, nil, nil)
			count++
		}
	}

	return count
}
