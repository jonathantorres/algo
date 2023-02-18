package graphs

import (
	"reflect"
	"testing"
)

func TestCreateUndirectedGraph(t *testing.T) {
	g := New(false)
	g.AddEdge(0, 1, 0, g.Directed)
	g.AddEdge(0, 4, 0, g.Directed)
	g.AddEdge(1, 2, 0, g.Directed)
	g.AddEdge(1, 3, 0, g.Directed)
	g.AddEdge(1, 4, 0, g.Directed)
	g.AddEdge(2, 3, 0, g.Directed)
	g.AddEdge(3, 4, 0, g.Directed)

	if g.numVertices != 5 {
		t.Errorf("expected number of vertices is %d but got %d", 5, g.numVertices)
	}

	if g.numEdges != 7 {
		t.Errorf("expected number of edges is %d but got %d", 7, g.numEdges)
	}
}

func TestCreateDirectedGraph(t *testing.T) {
	g := New(true)
	g.AddEdge(0, 1, 0, g.Directed)
	g.AddEdge(1, 2, 0, g.Directed)
	g.AddEdge(1, 3, 0, g.Directed)
	g.AddEdge(1, 4, 0, g.Directed)
	g.AddEdge(2, 4, 0, g.Directed)
	g.AddEdge(3, 4, 0, g.Directed)
	g.AddEdge(4, 5, 0, g.Directed)
	g.AddEdge(5, 6, 0, g.Directed)

	if g.numVertices != 7 {
		t.Errorf("expected number of vertices is %d but got %d", 7, g.numVertices)
	}

	if g.numEdges != 8 {
		t.Errorf("expected number of edges is %d but got %d", 8, g.numEdges)
	}
}

func TestConnectedComponents(t *testing.T) {
	g := New(false)
	g.AddEdge(0, 1, 0, g.Directed)
	g.AddEdge(0, 4, 0, g.Directed)
	g.AddEdge(1, 2, 0, g.Directed)
	g.AddEdge(1, 3, 0, g.Directed)
	g.AddEdge(1, 4, 0, g.Directed)
	g.AddEdge(2, 3, 0, g.Directed)
	g.AddEdge(3, 4, 0, g.Directed)

	components := g.ConnectedComponents()

	if components != 1 {
		t.Errorf("connected components is %d but got %d", 1, components)
	}

	comp := New(false)
	comp.AddEdge(0, 1, 0, comp.Directed)
	comp.AddEdge(0, 2, 0, comp.Directed)
	comp.AddEdge(1, 2, 0, comp.Directed)
	comp.AddEdge(3, 4, 0, comp.Directed)

	components = comp.ConnectedComponents()

	if components != 2 {
		t.Errorf("connected components is %d but got %d", 2, components)
	}
}

func TestBipartiteGraph(t *testing.T) {
	g := New(false)
	g.AddEdge(0, 1, 0, g.Directed)
	g.AddEdge(0, 4, 0, g.Directed)
	g.AddEdge(1, 2, 0, g.Directed)
	g.AddEdge(1, 3, 0, g.Directed)
	g.AddEdge(1, 4, 0, g.Directed)
	g.AddEdge(2, 3, 0, g.Directed)
	g.AddEdge(3, 4, 0, g.Directed)

	_, bipartite := g.TwoColoring()

	if bipartite {
		t.Errorf("graph g should not be bipartite")
	}

	g2 := New(false)
	g2.AddEdge(0, 1, 0, g2.Directed)
	g2.AddEdge(2, 3, 0, g2.Directed)
	g2.AddEdge(4, 5, 0, g2.Directed)

	_, bipartite = g2.TwoColoring()

	if !bipartite {
		t.Errorf("graph g2 should be bipartite")
	}
}

func TestCycle(t *testing.T) {
	g := New(false)
	g.AddEdge(0, 1, 0, g.Directed)
	g.AddEdge(0, 4, 0, g.Directed)
	g.AddEdge(1, 2, 0, g.Directed)
	g.AddEdge(1, 3, 0, g.Directed)
	g.AddEdge(1, 4, 0, g.Directed)
	g.AddEdge(2, 3, 0, g.Directed)
	g.AddEdge(3, 4, 0, g.Directed)

	if !g.HasCycle() {
		t.Errorf("graph g should have a cycle")
	}

	g2 := New(false)
	g2.AddEdge(0, 1, 0, g2.Directed)
	g2.AddEdge(2, 3, 0, g2.Directed)
	g2.AddEdge(4, 5, 0, g2.Directed)

	if g2.HasCycle() {
		t.Errorf("graph g2 should not have a cycle")
	}
}

func TestTopologicalSort(t *testing.T) {
	g := New(true)
	g.AddEdge(0, 1, 0, g.Directed)
	g.AddEdge(1, 2, 0, g.Directed)
	g.AddEdge(1, 3, 0, g.Directed)
	g.AddEdge(1, 4, 0, g.Directed)
	g.AddEdge(2, 4, 0, g.Directed)
	g.AddEdge(3, 4, 0, g.Directed)
	g.AddEdge(4, 5, 0, g.Directed)
	g.AddEdge(5, 6, 0, g.Directed)

	expected := []int{0, 1, 3, 2, 4, 5, 6}
	got := g.TopoSort()

	if !reflect.DeepEqual(got, expected) {
		t.Errorf("topological sort is incorrect, expected %v but got %v", expected, got)
	}
}

func TestPrim(t *testing.T) {
	g := New(false)
	g.AddEdge(0, 1, 5, g.Directed)
	g.AddEdge(0, 2, 12, g.Directed)
	g.AddEdge(0, 3, 7, g.Directed)
	g.AddEdge(1, 3, 9, g.Directed)
	g.AddEdge(1, 4, 7, g.Directed)
	g.AddEdge(2, 3, 4, g.Directed)
	g.AddEdge(2, 5, 7, g.Directed)
	g.AddEdge(3, 4, 4, g.Directed)
	g.AddEdge(3, 5, 3, g.Directed)
	g.AddEdge(4, 5, 2, g.Directed)
	g.AddEdge(4, 6, 5, g.Directed)
	g.AddEdge(5, 6, 2, g.Directed)

	tree := g.Prim(0)

	if tree.numVertices != 7 {
		t.Errorf("expected number of vertices is %d but got %d", 7, tree.numVertices)
	}

	if tree.numEdges != 6 {
		t.Errorf("expected number of edges is %d but got %d", 6, tree.numEdges)
	}
}

func TestKruskal(t *testing.T) {
	g := New(false)
	g.AddEdge(0, 1, 5, g.Directed)
	g.AddEdge(0, 2, 12, g.Directed)
	g.AddEdge(0, 3, 7, g.Directed)
	g.AddEdge(1, 3, 9, g.Directed)
	g.AddEdge(1, 4, 7, g.Directed)
	g.AddEdge(2, 3, 4, g.Directed)
	g.AddEdge(2, 5, 7, g.Directed)
	g.AddEdge(3, 4, 4, g.Directed)
	g.AddEdge(3, 5, 3, g.Directed)
	g.AddEdge(4, 5, 2, g.Directed)
	g.AddEdge(4, 6, 5, g.Directed)
	g.AddEdge(5, 6, 2, g.Directed)

	tree := g.Kruskal()

	if tree.numVertices != 7 {
		t.Errorf("expected number of vertices is %d but got %d", 7, tree.numVertices)
	}

	if tree.numEdges != 6 {
		t.Errorf("expected number of edges is %d but got %d", 6, tree.numEdges)
	}
}

func TestDijkstra(t *testing.T) {
	g := New(false)
	g.AddEdge(0, 1, 5, g.Directed)
	g.AddEdge(0, 2, 12, g.Directed)
	g.AddEdge(0, 3, 7, g.Directed)
	g.AddEdge(1, 3, 9, g.Directed)
	g.AddEdge(1, 4, 7, g.Directed)
	g.AddEdge(2, 3, 4, g.Directed)
	g.AddEdge(2, 5, 7, g.Directed)
	g.AddEdge(3, 4, 4, g.Directed)
	g.AddEdge(3, 5, 3, g.Directed)
	g.AddEdge(4, 5, 2, g.Directed)
	g.AddEdge(4, 6, 5, g.Directed)
	g.AddEdge(5, 6, 2, g.Directed)

	tree := g.Dijkstra(0)

	if tree.numVertices != 7 {
		t.Errorf("expected number of vertices is %d but got %d", 7, tree.numVertices)
	}

	if tree.numEdges != 6 {
		t.Errorf("expected number of edges is %d but got %d", 6, tree.numEdges)
	}
}
