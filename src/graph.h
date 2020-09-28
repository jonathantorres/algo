#ifndef _graph_h
#define _graph_h

#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

#define MAXV 1024

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

typedef void (*graph_vertex_proc)(int vertex);
typedef void (*graph_edge_proc)(int cur_vertex, int suc_vertex);

graph *graph_new(int nvertices, bool directed);
void graph_add_edge(graph *_graph, int x, int y, bool directed);
void graph_bfs(graph *_graph, int start, graph_vertex_proc vrt_proc_cb, graph_edge_proc edg_proc_cb);
void graph_free(graph *_graph); // TODO!

#endif
