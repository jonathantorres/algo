#include <stdbool.h>
#include <stdlib.h>
#include "unittest.h"
#include "queue.h"

#define MAXV 1000

typedef struct edgenode {
    int y;
    int weight;
    struct edgenode *next;
} edgenode;

typedef struct graph {
    edgenode *edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    bool directed;
} graph;

// for bfs
bool processed[MAXV+1];
bool discovered[MAXV+1];
int parent[MAXV+1];

// for dfs
int time;
int entry_time[MAXV+1];
int exit_time[MAXV+1];
bool finished;

graph *graph_create(int nvertices, bool directed)
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

void graph_insert_edge(graph *graph, int x, int y, bool directed)
{
    if (!graph) {
        return;
    }

    edgenode *_edge_node = malloc(sizeof(edgenode));
    if (!_edge_node) {
        return;
    }

    _edge_node->weight = 0;
    _edge_node->y = y;
    _edge_node->next = graph->edges[x];

    graph->edges[x] = _edge_node;
    graph->degree[x]++;

    if (!directed) {
        graph_insert_edge(graph, y, x, true);
    } else {
        graph->nedges++;
    }
}

void graph_print_stdout(graph *graph)
{
    if (!graph) {
        return;
    }
    printf("\n");
    edgenode *edge_n;

    for (int i = 1; i <= graph->nvertices; i++) {
        printf("%d: ", i);
        edge_n = graph->edges[i];
        while (edge_n != NULL) {
            printf("%d ", edge_n->y);
            edge_n = edge_n->next;
        }
        printf("\n");
    }
    printf("\n");
}

void graph_init_search(graph *graph)
{
    if (!graph) {
        return;
    }
    time = 0;
    finished = false;

    for (int i = 1; i <= graph->nvertices; i++) {
        processed[i] = false;
        discovered[i] = false;
        parent[i] = -1;
        entry_time[i] = 0;
        exit_time[i] = 0;
    }
}

void dfs_find_path(int start, int end, int parents[])
{
    if ((start == end) || (end == -1)) {
        printf("\n%d", start);
    } else {
        dfs_find_path(start, parents[end], parents);
        printf(" %d", end);
    }
}

void graph_process_vertex_early(int vertex)
{
    printf("processed vertex: %d\n", vertex);
}

void graph_process_vertex_late(int vertex)
{
    printf("processed vertex late: %d\n", vertex);
}

void graph_bfs_process_edge(int a, int b)
{
    printf("processed edge: (%d, %d)\n", a, b);
}

void graph_dfs_process_edge(int a, int b)
{
    printf("processed edge: (%d, %d)\n", a, b);
    if (parent[a] != b) {
        printf("Cycle from %d to %d:", a, b);
        dfs_find_path(b, a, parent);
        printf("\n\n");
        finished = true;
    }
}

void graph_bfs(graph *graph, int start)
{
    if (!graph) {
        return;
    }

    queue *_queue = queue_new();
    if (!_queue) {
        return;
    }

    int cur_vertex;
    int suc_vertex;
    edgenode *_edge_node;

    queue_enqueue(_queue, &start);
    discovered[start] = true;

    while (queue_length(_queue) != 0) {
        cur_vertex = *(int*)queue_dequeue(_queue);
        graph_process_vertex_early(cur_vertex);
        processed[cur_vertex] = true;
        _edge_node = graph->edges[cur_vertex];
        while (_edge_node != NULL) {
            suc_vertex = _edge_node->y;
            if ((processed[suc_vertex] == false) || graph->directed) {
                graph_bfs_process_edge(cur_vertex, suc_vertex);
            }
            if (discovered[suc_vertex] == false) {
                queue_enqueue(_queue, &suc_vertex);
                discovered[suc_vertex] = true;
                parent[suc_vertex] = cur_vertex;
            }
            _edge_node = _edge_node->next;
        }
        graph_process_vertex_late(cur_vertex);
    }
    queue_destroy(_queue);
}

void graph_dfs(graph *graph, int v)
{
    if (!graph) {
        return;
    }
    edgenode *_edge_node;
    int y;

    if (finished) {
        return;
    }
    discovered[v] = true;
    time = time+1;
    entry_time[v] = time;

    graph_process_vertex_early(v);

    _edge_node = graph->edges[v];
    while (_edge_node != NULL) {
        y = _edge_node->y;
        if (discovered[y] == false) {
            parent[y] = v;
            graph_dfs_process_edge(v, y);
            graph_dfs(graph, y);
        } else if ((!processed[y]) || (graph->directed)) {
            graph_dfs_process_edge(v, y);
            if (finished) {
                return;
            }
            _edge_node = _edge_node->next;
        }
        graph_process_vertex_late(v);
        time = time+1;
        exit_time[v] = time;
        processed[v] = true;
    }
}

char *graph_create_test()
{
    graph *d_graph = graph_create(6, false);
    graph_insert_edge(d_graph, 1, 2, false);
    graph_insert_edge(d_graph, 1, 4, false);
    graph_insert_edge(d_graph, 2, 3, false);
    graph_insert_edge(d_graph, 2, 6, false);
    graph_insert_edge(d_graph, 3, 4, false);
    graph_insert_edge(d_graph, 3, 6, false);
    graph_insert_edge(d_graph, 4, 5, false);
    graph_insert_edge(d_graph, 5, 6, false);
    graph_print_stdout(d_graph);
    return NULL;
}

char *graph_bfs_test()
{
    graph *d_graph = graph_create(6, false);
    graph_insert_edge(d_graph, 1, 2, false);
    graph_insert_edge(d_graph, 1, 4, false);
    graph_insert_edge(d_graph, 2, 3, false);
    graph_insert_edge(d_graph, 2, 6, false);
    graph_insert_edge(d_graph, 3, 4, false);
    graph_insert_edge(d_graph, 3, 6, false);
    graph_insert_edge(d_graph, 4, 5, false);
    graph_insert_edge(d_graph, 5, 6, false);
    graph_print_stdout(d_graph);

    graph_init_search(d_graph);
    graph_bfs(d_graph, 1);

    return NULL;
}

char *graph_dfs_test()
{
    graph *d_graph = graph_create(6, false);
    graph_insert_edge(d_graph, 1, 2, false);
    graph_insert_edge(d_graph, 1, 4, false);
    graph_insert_edge(d_graph, 2, 3, false);
    graph_insert_edge(d_graph, 2, 6, false);
    graph_insert_edge(d_graph, 3, 4, false);
    graph_insert_edge(d_graph, 3, 6, false);
    graph_insert_edge(d_graph, 4, 5, false);
    graph_insert_edge(d_graph, 5, 6, false);
    graph_print_stdout(d_graph);

    graph_init_search(d_graph);
    graph_dfs(d_graph, 1);

    return NULL;
}

int main()
{
    start_tests("graph tests");
    run_test(graph_create_test);
    run_test(graph_bfs_test);
    run_test(graph_dfs_test);
    end_tests();

    return 0;
}
