#include <stdio.h>
#include <stdlib.h>

// Node structure for BST
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);

    return root;
}

// Function to find the height of the tree (longest path)
int findLongestPath(struct Node* root) {
    if (root == NULL)
        return 0;

    int leftDepth = findLongestPath(root->left);
    int rightDepth = findLongestPath(root->right);

    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

// Function to find the minimum value in BST
int findMinValue(struct Node* root) {
    struct Node* current = root;
    while (current && current->left != NULL)
        current = current->left;
    return current->data;
}

// Function to swap left and right pointers of each node
void mirrorTree(struct Node* root) {
    if (root == NULL)
        return;

    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Function to search for a value in BST
int search(struct Node* root, int value) {
    if (root == NULL)
        return 0;

    if (root->data == value)
        return 1;
    else if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

// In-order traversal to display the tree
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\nBinary Search Tree Operations Menu:\n");
        printf("1. Insert a node\n");
        printf("2. Display in-order traversal\n");
        printf("3. Find the number of nodes in the longest path\n");
        printf("4. Find the minimum data value\n");
        printf("5. Mirror the tree\n");
        printf("6. Search for a value\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("Value %d inserted.\n", value);
                break;
            case 2:
                printf("Inorder traversal of the BST: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Number of nodes in the longest path: %d\n", findLongestPath(root));
                break;
            case 4:
                if (root != NULL)
                    printf("Minimum data value in the tree: %d\n", findMinValue(root));
                else
                    printf("The tree is empty.\n");
                break;
            case 5:
                mirrorTree(root);
                printf("The tree has been mirrored.\n");
                break;
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value))
                    printf("Value %d found in the tree.\n", value);
                else
                    printf("Value %d not found in the tree.\n", value);
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
