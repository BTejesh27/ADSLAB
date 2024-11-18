#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root, int data) {
    if (!root) return createNode(data);
    if (data < root->data) root->left = insertNode(root->left, data);
    else if (data > root->data) root->right = insertNode(root->right, data);
    return root;
}

int findLongestPath(struct Node* root) {
    if (!root) return 0;
    int leftHeight = findLongestPath(root->left);
    int rightHeight = findLongestPath(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int findMinValue(struct Node* root) {
    while (root && root->left) root = root->left;
    return root ? root->data : -1;
}

void mirrorTree(struct Node* root) {
    if (!root) return;
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirrorTree(root->left);
    mirrorTree(root->right);
}

struct Node* searchNode(struct Node* root, int key) {
    if (!root || root->data == key) return root;
    return key < root->data ? searchNode(root->left, key) : searchNode(root->right, key);
}

void inorderTraversal(struct Node* root) {
    if (!root) return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main() {
    struct Node* root = NULL;
    int values[] = {50, 30, 20, 40, 70, 60, 80};
    for (int i = 0; i < 7; i++) root = insertNode(root, values[i]);

    printf("Inorder traversal:\n");
    inorderTraversal(root);
    printf("\n");

    printf("Inorder after inserting 25:\n");
    insertNode(root, 25);
    inorderTraversal(root);
    printf("\n");

    printf("Height: %d\n", findLongestPath(root));
    printf("Min value: %d\n", findMinValue(root));

    mirrorTree(root);
    printf("Inorder after mirroring:\n");
    inorderTraversal(root);
    printf("\n");

    printf("Search 40: %s\n", searchNode(root, 40) ? "Found" : "Not found");

    return 0;
}
