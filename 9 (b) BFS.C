#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int queue[MAX];
int front = -1, rear = -1;

// Insert an element into Queue
void enqueue(int vertex) {
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    queue[++rear] = vertex;
}

// Delete an element from Queue
int dequeue() {
    int vertex = queue[front++];
    if (front > rear)
        front = rear = -1;
    return vertex;
}

// Breadth First Search
void BFS(int start, int n) {
    int i, current;

    // Initially all vertices are unvisited
    for (i = 0; i < n; i++)
        visited[i] = 0;

    front = rear = -1;

    // Visit starting vertex
    visited[start] = 1;
    enqueue(start);

    printf("BFS Traversal: ");

    while (front != -1) {
        current = dequeue();
        printf("%d ", current);

        // Check all adjacent vertices
        for (i = 0; i < n; i++) {
            if (adj[current][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                enqueue(i);
            }
        }
    }
    printf("\n");
}

// Main function
int main() {
    int n, i, j, start;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of vertices\n");
        return 0;
    }

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("Enter starting vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid starting vertex\n");
        return 0;
    }

    BFS(start, n);

    return 0;
}
