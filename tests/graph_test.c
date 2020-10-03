#include "unittest.h"
#include "graph.h"

void _graph_process_vertex(int vertex)
{
    if (vertex) {}
    // printf("processed vertex: %d\n", vertex);
}

void _graph_process_edge(int a, int b)
{
    if (a) {}
    if (b) {}
    // printf("processed edge: (%d, %d)\n", a, b);
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
            if (edge_n->weight > 0) {
                printf("%d(%d) ", edge_n->y, edge_n->weight);
            } else {
                printf("%d ", edge_n->y);
            }
            edge_n = edge_n->next;
        }
        printf("\n");
    }
    printf("\n");
}

char *graph_new_test()
{
    graph *d_graph = graph_new(6, false);
    graph_add_edge(d_graph, 1, 2, 0, false);
    graph_add_edge(d_graph, 1, 4, 0, false);
    graph_add_edge(d_graph, 2, 3, 0, false);
    graph_add_edge(d_graph, 2, 6, 0, false);
    graph_add_edge(d_graph, 3, 4, 0, false);
    graph_add_edge(d_graph, 3, 6, 0, false);
    graph_add_edge(d_graph, 4, 5, 0, false);
    graph_add_edge(d_graph, 5, 6, 0, false);
    // _graph_print_stdout(d_graph);
    graph_free(d_graph);
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
    graph_add_edge(d_graph, one, two, 0, false);
    graph_add_edge(d_graph, one, six, 0, false);
    graph_add_edge(d_graph, one, five, 0, false);
    graph_add_edge(d_graph, two, three, 0, false);
    graph_add_edge(d_graph, two, five, 0, false);
    graph_add_edge(d_graph, three, four, 0, false);
    graph_add_edge(d_graph, four, five, 0, false);
    // _graph_print_stdout(d_graph);
    graph_bfs(d_graph, one, _graph_process_vertex, _graph_process_edge);
    graph_free(d_graph);

    return NULL;
}

char *graph_dfs_test()
{
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    int six = 6;
    graph *d_graph = graph_new(6, false);
    graph_add_edge(d_graph, one, two, 0, false);
    graph_add_edge(d_graph, one, six, 0, false);
    graph_add_edge(d_graph, one, five, 0, false);
    graph_add_edge(d_graph, two, three, 0, false);
    graph_add_edge(d_graph, two, five, 0, false);
    graph_add_edge(d_graph, three, four, 0, false);
    graph_add_edge(d_graph, four, five, 0, false);
    // _graph_print_stdout(d_graph);
    graph_dfs(d_graph, one, _graph_process_vertex, _graph_process_edge);
    graph_free(d_graph);
    return NULL;
}

char *graph_mst_test()
{
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    graph *d_graph = graph_new(5, false);
    graph_add_edge(d_graph, one, two, 4, false);
    graph_add_edge(d_graph, one, three, 4, false);
    graph_add_edge(d_graph, one, four, 6, false);
    graph_add_edge(d_graph, one, five, 6, false);
    graph_add_edge(d_graph, two, three, 2, false);
    graph_add_edge(d_graph, three, four, 8, false);
    graph_add_edge(d_graph, four, five, 9, false);
    // _graph_print_stdout(d_graph);

    graph *result = graph_mst(d_graph, one);
    // _graph_print_stdout(result);
    graph_free(d_graph);
    graph_free(result);

    return NULL;
}

char *graph_dijkstra_test()
{
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    graph *d_graph = graph_new(5, false);
    graph_add_edge(d_graph, one, two, 4, false);
    graph_add_edge(d_graph, one, three, 4, false);
    graph_add_edge(d_graph, one, four, 6, false);
    graph_add_edge(d_graph, one, five, 6, false);
    graph_add_edge(d_graph, two, three, 2, false);
    graph_add_edge(d_graph, three, four, 8, false);
    graph_add_edge(d_graph, four, five, 9, false);
    _graph_print_stdout(d_graph);

    graph *result = graph_dijkstra(d_graph, four);
    _graph_print_stdout(result);
    graph_free(d_graph);
    graph_free(result);

    return NULL;
}

int main()
{
    start_tests("graph tests");
    run_test(graph_new_test);
    run_test(graph_bfs_test);
    run_test(graph_dfs_test);
    run_test(graph_mst_test);
    run_test(graph_dijkstra_test);
    end_tests();
    return 0;
}
