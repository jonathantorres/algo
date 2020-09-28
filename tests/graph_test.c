#include "unittest.h"
#include "graph.h"

// for dfs
int time;
int entry_time[MAXV+1];
int exit_time[MAXV+1];
bool finished;

void _graph_process_vertex(int vertex)
{
    printf("processed vertex: %d\n", vertex);
}

void _graph_process_edge(int a, int b)
{
    printf("processed edge: (%d, %d)\n", a, b);
}

void _graph_print_stdout(graph *graph)
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

// void graph_init_search(graph *graph)
// {
//     if (!graph) {
//         return;
//     }
//     time = 0;
//     finished = false;

//     for (int i = 1; i <= graph->nvertices; i++) {
//         processed[i] = false;
//         discovered[i] = false;
//         parent[i] = -1;
//         entry_time[i] = 0;
//         exit_time[i] = 0;
//     }
// }

// void dfs_find_path(int start, int end, int parents[])
// {
//     if ((start == end) || (end == -1)) {
//         printf("\n%d", start);
//     } else {
//         dfs_find_path(start, parents[end], parents);
//         printf(" %d", end);
//     }
// }

// void graph_dfs_process_edge(int a, int b)
// {
//     printf("processed edge: (%d, %d)\n", a, b);
//     if (parent[a] != b) {
//         printf("Cycle from %d to %d:", a, b);
//         dfs_find_path(b, a, parent);
//         printf("\n\n");
//         finished = true;
//     }
// }

// void graph_dfs(graph *graph, int v)
// {
//     if (!graph) {
//         return;
//     }
//     edgenode *_edge_node;
//     int y;

//     if (finished) {
//         return;
//     }
//     discovered[v] = true;
//     time = time+1;
//     entry_time[v] = time;

//     graph_process_vertex_early(v);

//     _edge_node = graph->edges[v];
//     while (_edge_node != NULL) {
//         y = _edge_node->y;
//         if (discovered[y] == false) {
//             parent[y] = v;
//             graph_dfs_process_edge(v, y);
//             graph_dfs(graph, y);
//         } else if ((!processed[y]) || (graph->directed)) {
//             graph_dfs_process_edge(v, y);
//             if (finished) {
//                 return;
//             }
//             _edge_node = _edge_node->next;
//         }
//         graph_process_vertex_late(v);
//         time = time+1;
//         exit_time[v] = time;
//         processed[v] = true;
//     }
// }

char *graph_new_test()
{
    graph *d_graph = graph_new(6, false);
    graph_add_edge(d_graph, 1, 2, false);
    graph_add_edge(d_graph, 1, 4, false);
    graph_add_edge(d_graph, 2, 3, false);
    graph_add_edge(d_graph, 2, 6, false);
    graph_add_edge(d_graph, 3, 4, false);
    graph_add_edge(d_graph, 3, 6, false);
    graph_add_edge(d_graph, 4, 5, false);
    graph_add_edge(d_graph, 5, 6, false);
    _graph_print_stdout(d_graph);
    return NULL;
}

char *graph_bfs_test()
{
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    int six = 6;
    graph *d_graph = graph_new(6, false);
    graph_add_edge(d_graph, one, two, false);
    graph_add_edge(d_graph, one, six, false);
    graph_add_edge(d_graph, one, five, false);
    graph_add_edge(d_graph, two, three, false);
    graph_add_edge(d_graph, two, five, false);
    graph_add_edge(d_graph, three, four, false);
    graph_add_edge(d_graph, four, five, false);
    _graph_print_stdout(d_graph);
    graph_bfs(d_graph, one, _graph_process_vertex, _graph_process_edge);

    return NULL;
}

// char *graph_dfs_test()
// {
//     graph *d_graph = graph_new(6, false);
//     graph_add_edge(d_graph, 1, 2, false);
//     graph_add_edge(d_graph, 1, 4, false);
//     graph_add_edge(d_graph, 2, 3, false);
//     graph_add_edge(d_graph, 2, 6, false);
//     graph_add_edge(d_graph, 3, 4, false);
//     graph_add_edge(d_graph, 3, 6, false);
//     graph_add_edge(d_graph, 4, 5, false);
//     graph_add_edge(d_graph, 5, 6, false);
//     _graph_print_stdout(d_graph);

//     graph_init_search(d_graph);
//     graph_dfs(d_graph, 1);

//     return NULL;
// }

int main()
{
    start_tests("graph tests");
    run_test(graph_new_test);
    run_test(graph_bfs_test);
    // run_test(graph_dfs_test);
    end_tests();
    return 0;
}
