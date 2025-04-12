#include <stdlib.h>
#include <stdio.h>

typedef struct NODE {
    int data;
    struct NODE *next;
} Node;

typedef struct GRAF {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graf;

Node *createNode(int v) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

Graf *createGraf(int vertices) {
    Graf *graph = malloc(sizeof(Graf));
    graph->vertices = vertices;

    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graf *graph, int src, int dest) {
    Node *new_node = createNode(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = createNode(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insertEdge(int nr_vertices, int nr_edges, Graf *graph) {
    int src, dest;
    printf("Adauga %d muchii (nodurile de la 0 la %d):\n", nr_edges, nr_vertices - 1);
    for (int i = 0; i < nr_edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

int isEmpty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *new_node = createNode(data);
    if (*queue == NULL) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}

int dequeue(Node **queue) {
    if (*queue == NULL) return -1;
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipeVisited(Graf *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(Graf *graph, int vertex) {
    Node *temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(Graf *graph, int start) {
    Node *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];
        while (temp != NULL) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

void printGraf(Graf *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        Node *temp = graph->adjacency_lists[i];
        printf("Nod %d: ", i);
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int nr_vertices, nr_edges, starting_vertex;

    printf("Nr noduri: ");
    scanf("%d", &nr_vertices);

    printf("Nr muchii: ");
    scanf("%d", &nr_edges);

    Graf *graph = createGraf(nr_vertices);
    insertEdge(nr_vertices, nr_edges, graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere DFS: ");
    DFS(graph, starting_vertex);

    wipeVisited(graph);
    printf("\n");

    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere BFS: ");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
