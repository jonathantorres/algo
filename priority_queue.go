package graphs

import "container/heap"

type PQItem struct {
	Priority int
	Value    interface{}
}

type PriorityQueue struct {
	q pqueue
}

func (pq *PriorityQueue) Push(i *PQItem) {
	heap.Push(&pq.q, i)
}

func (pq *PriorityQueue) Pop() *PQItem {
	return heap.Pop(&pq.q).(*PQItem)
}

func (pq *PriorityQueue) Empty() bool {
	return pq.q.Len() == 0
}

const defaultCap = 10

func NewPriorityQueue() *PriorityQueue {
	pq := &PriorityQueue{
		q: make(pqueue, 0, defaultCap),
	}
	return pq
}

type pqueue []*PQItem

func (pq *pqueue) Push(x interface{}) {
	*pq = append(*pq, x.(*PQItem))
}

func (pq *pqueue) Pop() interface{} {
	old := *pq
	n := len(old)
	x := old[n-1]

	*pq = old[0 : n-1]

	return x
}

func (pq pqueue) Len() int {
	return len(pq)
}

func (pq pqueue) Less(i, j int) bool {
	return pq[i].Priority < pq[j].Priority
}

func (pq pqueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
}
