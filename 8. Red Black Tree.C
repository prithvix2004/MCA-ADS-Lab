#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct Node {
    int data;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

typedef struct Node Node;

Node *root;
Node *NIL;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->color = RED;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NIL;
    return newNode;
}

void initialize() {
    NIL = (Node*)malloc(sizeof(Node));
    if (!NIL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    root = NIL;
}

void leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void insertFix(Node *z) {
    Node *y;

    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;

            // Case 1: Uncle is RED
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2: Triangle
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3: Line
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;

            // Case 1: Uncle is RED
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2: Triangle
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3: Line
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void insert(int data) {
    Node *z = createNode(data);
    Node *y = NIL;
    Node *x = root;

    while (x != NIL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else if (z->data > x->data)
            x = x->right;
        else {
            printf("Duplicate values not allowed.\n");
            free(z);
            return;
        }
    }

    z->parent = y;
    if (y == NIL)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFix(z);
    printf("Node %d inserted successfully.\n", data);
}

Node* search(Node *x, int data) {
    if (x == NIL || x->data == data)
        return x;

    if (data < x->data)
        return search(x->left, data);

    return search(x->right, data);
}

Node* minimum(Node *x) {
    while (x->left != NIL)
        x = x->left;
    return x;
}

void transplant(Node *u, Node *v) {
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

void deleteFix(Node *x) {
    Node *w;

    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;

            // Case 1: Sibling is RED
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            // Case 2: Both sibling children are BLACK
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                // Case 3: Far child is BLACK
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // Case 4: Far child is RED
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            w = x->parent->left;

            // Case 1: Sibling is RED
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            // Case 2: Both sibling children are BLACK
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                // Case 3: Far child is BLACK
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // Case 4: Far child is RED
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;

    // Ensure sentinel NIL integrity is preserved
    NIL->color = BLACK;
    NIL->parent = NIL;
}

void deleteNode(int data) {
    Node *z = search(root, data);
    if (z == NIL) {
        printf("Element %d not found!\n", data);
        return;
    }

    Node *y = z;
    Node *x;
    int originalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (originalColor == BLACK)
        deleteFix(x);

    printf("Node %d deleted successfully.\n", data);
}

void inorder(Node *node) {
    if (node != NIL) {
        inorder(node->left);
        printf("%d(%s) ", node->data, node->color == RED ? "R" : "B");
        inorder(node->right);
    }
}

void preorder(Node *node) {
    if (node != NIL) {
        printf("%d(%s) ", node->data, node->color == RED ? "R" : "B");
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(Node *node) {
    if (node != NIL) {
        postorder(node->left);
        postorder(node->right);
        printf("%d(%s) ", node->data, node->color == RED ? "R" : "B");
    }
}

void display(Node *node, int space) {
    if (node == NIL)
        return;

    space += 5;
    display(node->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d(%s)\n", node->data, node->color == RED ? "R" : "B");

    display(node->left, space);
}

// Free all allocated nodes recursively
void freeTree(Node *node) {
    if (node != NIL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

// Helper to flush invalid characters from input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice, data;
    initialize();

    do {
        printf("\n----- RED BLACK TREE -----\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Display Tree\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &data) == 1)
                    insert(data);
                else {
                    printf("Invalid number!\n");
                    clearInputBuffer();
                }
                break;

            case 2:
                printf("Enter value to delete: ");
                if (scanf("%d", &data) == 1)
                    deleteNode(data);
                else {
                    printf("Invalid number!\n");
                    clearInputBuffer();
                }
                break;

            case 3:
                printf("Enter value to search: ");
                if (scanf("%d", &data) == 1) {
                    if (search(root, data) != NIL)
			                printf("Element %d found!\n", data);
			              else
			                printf("Element %d not found!\n", data);
                }
			          else {
				          printf("Invalid number!\n");
			            clearInputBuffer();
                }
                break;

          	case 4:
          		if (root == NIL) printf("Tree is empty.\n");
          		else {
          			printf("Inorder Traversal: ");
          			inorder(root);
          			printf("\n");
          			}
            break;

            case 5:
            if (root == NIL) printf("Tree is empty.\n");
            else {
            printf("Preorder Traversal: ");
            preorder(root);
            printf("\n");
            }
            break;

            case 6:
            if (root == NIL) printf("Tree is empty.\n");
            else {
            printf("Postorder Traversal: ");
            postorder(root);
            printf("\n");
            }
            break;

            case 7:
            if (root == NIL) printf("Tree is empty.\n");
            else {
            printf("\nRed-Black Tree (rotated 90 degrees left):\n");
            display(root, 0);
            }
            break;

            case 8:
            printf("Freeing memory and exiting...\n");
            freeTree(root);
            free(NIL);
            break;

            default:
            printf("Invalid choice! Please select 1-8.\n");
            }
            }
            
            while (choice != 8);
  return 0;
}
