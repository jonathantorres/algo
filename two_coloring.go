package graphs

const (
	uncolored = iota
	black
	white
)

func (g *Graph) TwoColoring() ([]int, bool) {
	colors := make([]int, g.numVertices)
	var isBipartite = true

	for v, _ := range g.edges {
		colors[v] = uncolored
	}

	g.InitBFS()

	processEdge := func(x int, y int) {
		if colors[x] == colors[y] {
			isBipartite = false
		}

		colors[y] = complement(colors[x])
	}

	for v, _ := range g.edges {
		if g.vertexStates[v] == undiscovered {
			colors[v] = white
			g.BFS(v, nil, processEdge)
		}
	}

	return colors, isBipartite
}

func (g *Graph) IsBipartite() bool {
	_, isBipartite := g.TwoColoring()

	return isBipartite
}

func complement(color int) int {
	if color == white {
		return black
	}
	if color == black {
		return white
	}
	return uncolored
}
