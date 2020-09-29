#include "unittest.h"
#include "graph.h"

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
    graph_add_edge(d_graph, one, two, false);
    graph_add_edge(d_graph, one, six, false);
    graph_add_edge(d_graph, one, five, false);
    graph_add_edge(d_graph, two, three, false);
    graph_add_edge(d_graph, two, five, false);
    graph_add_edge(d_graph, three, four, false);
    graph_add_edge(d_graph, four, five, false);
    _graph_print_stdout(d_graph);
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
    graph_add_edge(d_graph, one, two, false);
    graph_add_edge(d_graph, one, six, false);
    graph_add_edge(d_graph, one, five, false);
    graph_add_edge(d_graph, two, three, false);
    graph_add_edge(d_graph, two, five, false);
    graph_add_edge(d_graph, three, four, false);
    graph_add_edge(d_graph, four, five, false);
    _graph_print_stdout(d_graph);
    graph_dfs(d_graph, one, _graph_process_vertex, _graph_process_edge);
    graph_free(d_graph);
    return NULL;
}

int main()
{
    start_tests("graph tests");
    run_test(graph_new_test);
    run_test(graph_bfs_test);
    run_test(graph_dfs_test);
    end_tests();
    return 0;
}
