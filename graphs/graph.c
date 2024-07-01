#include "graph.h"

static void _build_path(int start, int end, int parents[], array *res)
{
    int *val = malloc(sizeof(int));
    if (!val) {
        return;
    }

    if ((start == end) || (end == -1)) {
        *val = start;
        array_push(res, val);
    } else {
        _build_path(start, parents[end], parents, res);
        *val = end;
        array_push(res, val);
    }
}

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

void graph_add_edge(graph *_graph, int x, int y, int weight, bool directed)
{
    if (!_graph) {
        return;
    }

    edgenode *_edge_node = malloc(sizeof(edgenode));
    if (!_edge_node) {
        return;
    }

    _edge_node->weight = weight;
    _edge_node->y = y;
    _edge_node->next = _graph->edges[x];

    _graph->edges[x] = _edge_node;
    _graph->degree[x]++;

    if (!directed) {
        graph_add_edge(_graph, y, x, weight, true);
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
    edgenode *_edge_node;

    for (int i = 1; i <= _graph->nvertices; i++) {
        processed[i] = false;
        discovered[i] = false;
        parent[i] = -1;
    }

    int *begin = malloc(sizeof(int));
    *begin = start;
    queue_enqueue(_queue, begin);
    discovered[*begin] = true;

    while (queue_len(_queue) != 0) {
        int *cur_vertex = (int*)queue_dequeue(_queue);
        if (vrt_proc_cb) {
            vrt_proc_cb(*cur_vertex);
        }

        processed[*cur_vertex] = true;
        _edge_node = _graph->edges[*cur_vertex];
        while (_edge_node != NULL) {
            int *suc_vertex = malloc(sizeof(int));
            *suc_vertex = _edge_node->y;
            if ((processed[*suc_vertex] == false) || _graph->directed) {
                if (edg_proc_cb) {
                    edg_proc_cb(*cur_vertex, *suc_vertex);
                }
            }
            if (discovered[*suc_vertex] == false) {
                queue_enqueue(_queue, suc_vertex);
                discovered[*suc_vertex] = true;
                parent[*suc_vertex] = *cur_vertex;
            }
            _edge_node = _edge_node->next;
        }
        free(cur_vertex);
    }
    queue_free(_queue, NULL);
}

void graph_dfs(graph *_graph, int start, graph_vertex_proc vrt_proc_cb, graph_edge_proc edg_proc_cb)
{
    if (!_graph) {
        return;
    }

    stack *_stack = stack_new();
    if (!_stack) {
        return;
    }

    int time = 0;
    int entry_time[MAXV+1];
    int exit_time[MAXV+1];
    bool processed[MAXV+1];
    bool discovered[MAXV+1];

    for (int i = 1; i <= _graph->nvertices; i++) {
        processed[i] = false;
        discovered[i] = false;
        entry_time[i] = 0;
        exit_time[i] = 0;
    }

    edgenode *_edge_node = NULL;
    int *begin = malloc(sizeof(int));
    if (!begin) {
        return;
    }
    *begin = start;
    stack_push(_stack, begin);
    discovered[*begin] = true;
    time = time+1;
    entry_time[*begin] = time;

    while (stack_len(_stack) != 0) {
        int *cur_vertex = (int*)stack_pop(_stack);
        if (vrt_proc_cb) {
            vrt_proc_cb(*cur_vertex);
        }
        _edge_node = _graph->edges[*cur_vertex];
        while (_edge_node != NULL) {
            int *suc_vertex = malloc(sizeof(int));
            *suc_vertex = _edge_node->y;
            if (discovered[*suc_vertex] == false) {
                stack_push(_stack, suc_vertex);
                discovered[*suc_vertex] = true;
                time = time+1;
                entry_time[*suc_vertex] = time;
            }
            if ((processed[*suc_vertex] == false) || _graph->directed) {
                if (edg_proc_cb) {
                    edg_proc_cb(*cur_vertex, *suc_vertex);
                }
            }
            _edge_node = _edge_node->next;
        }
        time = time+1;
        exit_time[*cur_vertex] = time;
        processed[*cur_vertex] = true;
        free(cur_vertex);
    }
    stack_free(_stack, NULL);
}

graph *graph_mst(graph *_graph, int start)
{
    if (!_graph) {
        return NULL;
    }

    bool intree[MAXV+1];
    int distance[MAXV+1];
    int parent[MAXV+1];
    int vertices[MAXV+1];
    edgenode *_edge_node = NULL;

    for (int i = 1; i <= _graph->nvertices; i++) {
        intree[i] = false;
        distance[i] = INT_MAX;
        parent[i] = -1;
        vertices[i] = -1;
    }

    distance[start] = 0;
    int cur_vertex = start;

    while (intree[cur_vertex] == false) {
        intree[cur_vertex] = true;
        _edge_node = _graph->edges[cur_vertex];
        while (_edge_node != NULL) {
            int nxt_vertex = _edge_node->y;
            int weight = _edge_node->weight;
            if ((distance[nxt_vertex] > weight) && intree[nxt_vertex] == false) {
                distance[nxt_vertex] = weight;
                parent[nxt_vertex] = cur_vertex;
                vertices[nxt_vertex] = nxt_vertex;
            }
            _edge_node = _edge_node->next;
        }
        cur_vertex = 1;
        int dist = INT_MAX;
        for (int i = 1; i <= _graph->nvertices; i++) {
            if ((intree[i] == false) && (dist > distance[i])) {
                dist = distance[i];
                cur_vertex = i;
            }
        }
    }

    // create the mst graph
    graph *result = graph_new(_graph->nvertices, _graph->directed);
    int *cur_distance = &distance[1]; // skip the first distance, since its 0
    for (int i = 1; i <= _graph->nvertices; i++) {
        if (parent[i] > -1 && vertices[i] > -1) {
            cur_distance++;
            graph_add_edge(result, parent[i], vertices[i], *cur_distance, _graph->directed);
        }
    }
    return result;
}

array *graph_dijkstra(graph *_graph, int start, int end)
{
    if (!_graph) {
        return NULL;
    }

    bool intree[MAXV+1];
    int distance[MAXV+1];
    int parent[MAXV+1];
    edgenode *_edge_node = NULL;

    for (int i = 1; i <= _graph->nvertices; i++) {
        intree[i] = false;
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[start] = 0;
    int cur_vertex = start;

    while (intree[cur_vertex] == false) {
        intree[cur_vertex] = true;
        _edge_node = _graph->edges[cur_vertex];
        while (_edge_node != NULL) {
            int nxt_vertex = _edge_node->y;
            int weight = _edge_node->weight;
            if (distance[nxt_vertex] > (distance[cur_vertex] + weight)) {
                distance[nxt_vertex] = distance[cur_vertex] + weight;
                parent[nxt_vertex] = cur_vertex;
            }
            _edge_node = _edge_node->next;
        }
        cur_vertex = 1;
        int dist = INT_MAX;
        for (int i = 1; i <= _graph->nvertices; i++) {
            if ((intree[i] == false) && (dist > distance[i])) {
                dist = distance[i];
                cur_vertex = i;
            }
        }
    }

    // create array with shortest path
    array *res = array_new(_graph->nvertices+1, sizeof(int*));
    _build_path(start, end, parent, res);

    return res;
}

void graph_free(graph *_graph)
{
    if (!_graph) {
        return;
    }

    edgenode *edge_n = NULL;
    for (unsigned int i = 1; i <= MAXV; i++) {
        edge_n = _graph->edges[i];
        if (edge_n != NULL) {
            edgenode *cur_edge = edge_n;
            edgenode *prev_edge = NULL;
            while (cur_edge->next != NULL) {
                prev_edge = cur_edge;
                cur_edge = cur_edge->next;
                if (prev_edge) {
                    free(prev_edge);
                }
            }
            if (cur_edge) {
                free(cur_edge);
            }
        }
    }
    if (_graph) {
        free(_graph);
    }
}
