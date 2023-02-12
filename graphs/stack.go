package graphs

import "container/list"

type Stack struct {
	list *list.List
}

func NewStack() *Stack {
	return &Stack{list.New()}
}

func (s *Stack) Push(value interface{}) {
	s.list.PushFront(value)
}

func (s *Stack) Pop() (interface{}, bool) {
	e := s.list.Front()

	if e == nil {
		return nil, false
	}

	s.list.Remove(e)

	return e.Value, true
}

func (s *Stack) Len() int {
	return s.list.Len()
}

func (s *Stack) Empty() bool { return s.Len() == 0 }
