#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int n;

// Recursive DFS function
void DFS(int vertex)
{
    int i;

    printf("%d ", vertex);

    // Mark the current vertex as visited
    visited[vertex] = 1;

    // Visit all adjacent unvisited vertices
    for (i = 0; i < n; i++)
    {
        if (adj[vertex][i] == 1 && visited[i] == 0)
        {
            DFS(i);
        }
    }
}

int main()
{
    int i, j, start;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }

    // Initialize visited array
    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    printf("Enter the starting vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    printf("DFS Traversal: ");

    DFS(start);

    // Visit remaining unvisited vertices (disconnected graph)
    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            DFS(i);
        }
    }

    return 0;
}
