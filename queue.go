package graphs

import "container/list"

type Queue struct {
	list *list.List
}

func NewQueue() *Queue {
	return &Queue{list.New()}
}

func (q *Queue) Enqueue(value interface{}) {
	q.list.PushBack(value)
}

func (q *Queue) Dequeue() (interface{}, bool) {
	e := q.list.Front()

	if e == nil {
		return nil, false
	}

	q.list.Remove(e)

	return e.Value, true
}

func (q *Queue) Len() int {
	return q.list.Len()
}

func (q *Queue) Empty() bool { return q.Len() == 0 }
