package graphs

import (
	"math"
)

func (g *Graph) Dijkstra(start int) *Graph {
	inTree := make([]bool, g.numVertices)
	distance := make([]int, g.numVertices)
	weights := make([]int, g.numVertices)
	parent := make([]int, g.numVertices)

	for v, _ := range g.edges {
		inTree[v] = false
		distance[v] = math.MaxInt64
		parent[v] = -1
	}

	v := start
	distance[start] = 0
	weights[start] = 0

	for !inTree[v] {
		inTree[v] = true
		edge := g.edges[v]
		currentEdge := edge

		for currentEdge != nil {
			n := currentEdge.n
			weight := currentEdge.weight

			if distance[n] > (distance[v]+weight) && !inTree[n] {
				distance[n] = distance[v] + weight
				weights[n] = weight
				parent[n] = v
			}

			currentEdge = currentEdge.next
		}

		v = 1
		dist := math.MaxInt64

		for i := 0; i < g.numVertices; i++ {
			if !inTree[i] && dist > distance[i] {
				dist = distance[i]
				v = i
			}
		}
	}

	// build the final graph with the tree
	tree := New(g.Directed)
	for i, p := range parent {
		if p < 0 {
			// this is the root
			continue
		}

		tree.AddEdge(p, i, weights[i], g.Directed)
	}

	return tree
}
