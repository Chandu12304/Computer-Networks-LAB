#include <stdio.h>
#define INF 9999
#define V 3  // Number of vertices

// Find the vertex with the minimum distance value
int minDistance(int dist[], int visited[]) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Dijkstra's algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // Output array
    int visited[V];   // To track visited vertices

    // Initialize all distances as INF and visited as 0
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;  // Distance from source to itself is 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited); // Pick the min distance vertex
        visited[u] = 1;

        // Update distance of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the result
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

int main() {
    // Example graph (Adjacency Matrix)
    int graph[V][V] = {
        {0, 1, 6},
        {3, 0, 0},
        {6, 3, 0}
    };

    int source = 2;
    dijkstra(graph, source);

    return 0;
}
