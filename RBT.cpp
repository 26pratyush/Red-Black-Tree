#include <stdio.h>
#include <stdlib.h>

// Define the Red and Black node colors
#define RED 0
#define BLACK 1

// Node structure with additional features
struct Node {
    int key;
    int color;
    struct Node *left, *right, *parent;
};

// Create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = RED;  // New nodes are initially RED
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Left rotation to maintain tree balance
void rotateLeft(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right rotation to maintain tree balance
void rotateRight(struct Node **root, struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Fix violations of Red-Black Tree properties after insertion
void fixViolation(struct Node **root, struct Node *z) {
    struct Node *parent_z = NULL;
    struct Node *grand_parent_z = NULL;

    while ((z != *root) && (z->color == RED) && (z->parent->color == RED)) {
        parent_z = z->parent;
        grand_parent_z = z->parent->parent;

        if (parent_z == grand_parent_z->left) {
            struct Node *uncle_z = grand_parent_z->right;
            if (uncle_z != NULL && uncle_z->color == RED) {
                grand_parent_z->color = RED;
                parent_z->color = BLACK;
                uncle_z->color = BLACK;
                z = grand_parent_z;
            } else {
                if (z == parent_z->right) {
                    rotateLeft(root, parent_z);
                    z = parent_z;
                    parent_z = z->parent;
                }
                rotateRight(root, grand_parent_z);
                int temp = parent_z->color;
                parent_z->color = grand_parent_z->color;
                grand_parent_z->color = temp;
                z = parent_z;
            }
        } else {
            struct Node *uncle_z = grand_parent_z->left;
            if ((uncle_z != NULL) && (uncle_z->color == RED)) {
                grand_parent_z->color = RED;
                parent_z->color = BLACK;
                uncle_z->color = BLACK;
                z = grand_parent_z;
            } else {
                if (z == parent_z->left) {
                    rotateRight(root, parent_z);
                    z = parent_z;
                    parent_z = z->parent;
                }
                rotateLeft(root, grand_parent_z);
                int temp = parent_z->color;
                parent_z->color = grand_parent_z->color;
                grand_parent_z->color = temp;
                z = parent_z;
            }
        }
    }

    (*root)->color = BLACK;
}

// Insert a new node into the Red-Black Tree
void insert(struct Node **root, int key) {
    struct Node *z = createNode(key);
    struct Node *y = NULL;
    struct Node *x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == NULL) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    fixViolation(root, z);
}

// Search for a node with a given key
struct Node* search(struct Node *root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Inorder traversal to print tree elements in sorted order
void inorderTraversal(struct Node *root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d(%s) ", root->key, root->color == RED ? "RED" : "BLACK");
    inorderTraversal(root->right);
}

// Helper function to check if the Red-Black Tree is balanced
int checkRedBlackProperties(struct Node *root, int blackHeight, int *pathBlackHeight) {
    if (root == NULL) {
        // If leaf node, return the black height from this path
        if (*pathBlackHeight == -1) {
            *pathBlackHeight = blackHeight;
        } else if (*pathBlackHeight != blackHeight) {
            return 0; // Black height mismatch
        }
        return 1;
    }

    // If the current node is red, check if its parent is also red (violates Red-Black property)
    if (root->color == RED && (root->parent != NULL && root->parent->color == RED)) {
        return 0; // Violation of consecutive red nodes
    }

    // Count the black height of the current path
    int newBlackHeight = blackHeight + (root->color == BLACK ? 1 : 0);

    // Recursively check the left and right subtrees
    return checkRedBlackProperties(root->left, newBlackHeight, pathBlackHeight) &&
           checkRedBlackProperties(root->right, newBlackHeight, pathBlackHeight);
}

// Function to check if the tree is balanced and follows Red-Black properties
int checkBalance(struct Node *root) {
    int pathBlackHeight = -1;
    return checkRedBlackProperties(root, 0, &pathBlackHeight);
}

// Get the height of the tree
int getHeight(struct Node *node) {
    if (node == NULL) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Main function for testing
int main() {
    struct Node *root = NULL;

    // Insert nodes
    insert(&root, 3);
    insert(&root, 21);
    insert(&root, 32);
    insert(&root, 15);

    // Inorder traversal
    printf("Inorder traversal of the Red-Black tree:\n");
    inorderTraversal(root);
    printf("\n");

    // Search operation
    struct Node *found = search(root, 21);
    if (found != NULL)
        printf("Found node with key: %d\n", found->key);
    else
        printf("Node not found\n");

    // Check tree balance
    if (checkBalance(root))
        printf("The tree is balanced.\n");
    else
        printf("The tree is not balanced.\n");

    // Print tree height
    printf("Tree height: %d\n", getHeight(root));

    return 0;
}
