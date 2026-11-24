#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top = -1;
int n;

// DFS function with cycle detection
int DFS(int vertex)
{
    int i;

    // Mark vertex as currently being visited
    visited[vertex] = 1;

    for (i = 0; i < n; i++)
    {
        if (adj[vertex][i] == 1)
        {
            if (visited[i] == 1)
            {
                // Cycle detected
                return 0;
            }

            if (visited[i] == 0)
            {
                if (DFS(i) == 0)
                    return 0;
            }
        }
    }

    // Mark vertex as completely visited
    visited[vertex] = 2;

    // Push vertex after visiting all neighbours
    stack[++top] = vertex;

    return 1;
}

// Topological sorting function
int topologicalSort()
{
    int i;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    top = -1;

    // Visit all unvisited vertices
    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            if (DFS(i) == 0)
                return 0;
        }
    }

    printf("\nTopological Sorting: ");

    while (top != -1)
    {
        printf("%d ", stack[top--]);
    }

    printf("\n");

    return 1;
}

int main()
{
    int i, j;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }

    if (topologicalSort() == 0)
    {
        printf("\nTopological sorting is not possible.");
        printf("\nThe graph contains a cycle.\n");
    }

    return 0;
}
