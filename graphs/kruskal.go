package graphs

type edgePair struct {
	x, y int
}

func (g *Graph) Kruskal() *Graph {
	union := newSetUnion(g.numVertices)
	pq := NewPriorityQueue()

	for v, edge := range g.edges {
		currentEdge := edge

		for currentEdge != nil {
			n := currentEdge.n
			item := &PQItem{
				Priority: currentEdge.weight,
				Value: &edgePair{
					x: v,
					y: n,
				},
			}

			pq.Push(item)

			currentEdge = currentEdge.next
		}
	}

	// build the final graph with the tree
	mst := New(g.Directed)

	for !pq.Empty() {
		item := pq.Pop()
		edge := item.Value.(*edgePair)

		if !union.sameComponent(edge.x, edge.y) {
			mst.AddEdge(edge.x, edge.y, item.Priority, g.Directed)
			union.union(edge.x, edge.y)
		}
	}

	return mst
}

type setUnion struct {
	parent []int
	size   []int
	n      int
}

func (s *setUnion) find(x int) int {
	if s.parent[x] == x {
		return x
	} else {
		return s.find(s.parent[x])
	}
}

func (s *setUnion) union(s1, s2 int) {
	r1 := s.find(s1)
	r2 := s.find(s2)

	if r1 == r2 {
		return
	}

	if s.size[r1] >= s.size[r2] {
		s.size[r1] = s.size[r1] + s.size[r2]
		s.parent[r2] = r1
	} else {
		s.size[r2] = s.size[r1] + s.size[r2]
		s.parent[r1] = r2
	}
}

func (s *setUnion) sameComponent(s1, s2 int) bool {
	return s.find(s1) == s.find(s2)
}

func newSetUnion(n int) *setUnion {
	union := &setUnion{
		parent: make([]int, n),
		size:   make([]int, n),
		n:      n,
	}

	for i := 0; i < n; i++ {
		union.parent[i] = i
		union.size[i] = 1
	}

	return union
}
