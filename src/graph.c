#include "graph.h"

graph *graph_new(int nvertices, bool directed)
{
    graph *new_graph = malloc(sizeof(graph));
    if (!new_graph) {
        return NULL;
    }

    new_graph->nvertices = nvertices;
    new_graph->nedges = 0;
    new_graph->directed = directed;

    for (unsigned int i = 1; i <= MAXV; i++) {
        new_graph->degree[i] = 0;
    }

    for (unsigned int i = 1; i <= MAXV; i++) {
        new_graph->edges[i] = NULL;
    }

    return new_graph;
}

void graph_add_edge(graph *_graph, int x, int y, bool directed)
{
    if (!_graph) {
        return;
    }

    edgenode *_edge_node = malloc(sizeof(edgenode));
    if (!_edge_node) {
        return;
    }

    _edge_node->weight = 0;
    _edge_node->y = y;
    _edge_node->next = _graph->edges[x];

    _graph->edges[x] = _edge_node;
    _graph->degree[x]++;

    if (!directed) {
        graph_add_edge(_graph, y, x, true);
    } else {
        _graph->nedges++;
    }
}

void graph_bfs(graph *_graph, int start, graph_vertex_proc vrt_proc_cb, graph_edge_proc edg_proc_cb)
{
    if (!_graph) {
        return;
    }

    queue *_queue = queue_new();
    if (!_queue) {
        return;
    }

    bool processed[MAXV+1];
    bool discovered[MAXV+1];
    int parent[MAXV+1];
    int cur_vertex;
    int suc_vertex;
    edgenode *_edge_node;

    for (int i = 1; i <= _graph->nvertices; i++) {
        processed[i] = false;
        discovered[i] = false;
        parent[i] = -1;
    }

    queue_enqueue(_queue, &start);
    discovered[start] = true;

    while (queue_len(_queue) != 0) {
        cur_vertex = *(int*)queue_dequeue(_queue);
        if (vrt_proc_cb) {
            vrt_proc_cb(cur_vertex);
        }

        processed[cur_vertex] = true;
        _edge_node = _graph->edges[cur_vertex];
        while (_edge_node != NULL) {
            suc_vertex = _edge_node->y;
            if ((processed[suc_vertex] == false) || _graph->directed) {
                if (edg_proc_cb) {
                    edg_proc_cb(cur_vertex, suc_vertex);
                }
            }
            if (discovered[suc_vertex] == false) {
                queue_enqueue(_queue, &suc_vertex);
                discovered[suc_vertex] = true;
                parent[suc_vertex] = cur_vertex;
            }
            _edge_node = _edge_node->next;
        }
    }
    queue_free(_queue, NULL);
}
