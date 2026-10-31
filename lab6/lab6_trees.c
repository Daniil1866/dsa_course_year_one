#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *createNode(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* 701 */
struct TreeNode *insertIntoBST(struct TreeNode *root, int val) {
    if (root == NULL)
        return createNode(val);

    if (val < root->val)
        root->left = insertIntoBST(root->left, val);
    else if (val > root->val)
        root->right = insertIntoBST(root->right, val);

    return root;
}

/* 94 helpers */
void countNodes(struct TreeNode *root, int *count) {
    if (root == NULL) return;
    (*count)++;
    countNodes(root->left, count);
    countNodes(root->right, count);
}

void inorderFill(struct TreeNode *root, int *result, int *index) {
    if (root == NULL) return;
    inorderFill(root->left, result, index);
    result[(*index)++] = root->val;
    inorderFill(root->right, result, index);
}

int *inorderTraversal(struct TreeNode *root, int *returnSize) {
    int count = 0;
    countNodes(root, &count);
    *returnSize = count;

    if (count == 0) return NULL;

    int *result = malloc(count * sizeof(int));
    int index = 0;
    inorderFill(root, result, &index);
    return result;
}

/* 102 */
int **levelOrder(struct TreeNode *root, int *returnSize,
                 int **returnColumnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int nodeCount = 0;
    countNodes(root, &nodeCount);

    struct TreeNode **queue = malloc(nodeCount * sizeof(struct TreeNode *));
    int **result = malloc(nodeCount * sizeof(int *));
    int *columnSizes = malloc(nodeCount * sizeof(int));

    int front = 0, back = 0, levels = 0;
    queue[back++] = root;

    while (front < back) {
        int size = back - front;
        result[levels] = malloc(size * sizeof(int));
        columnSizes[levels] = size;

        for (int i = 0; i < size; i++) {
            struct TreeNode *current = queue[front++];
            result[levels][i] = current->val;

            if (current->left != NULL)
                queue[back++] = current->left;
            if (current->right != NULL)
                queue[back++] = current->right;
        }

        levels++;
    }

    free(queue);
    *returnSize = levels;
    *returnColumnSizes = columnSizes;
    return result;
}

/* Local testing helpers */
void printArray(int *values, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", values[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]");
}

void freeTree(struct TreeNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

struct TreeNode *buildLectureTree(void) {
    int values[] = {4, 2, 7, 1, 3, 6, 9};
    struct TreeNode *root = NULL;

    for (int i = 0; i < 7; i++)
        root = insertIntoBST(root, values[i]);

    return root;
}

void task1(void) {
    struct TreeNode *root = buildLectureTree();
    int size;
    int *result = inorderTraversal(root, &size);

    printf("BST built from [4, 2, 7, 1, 3, 6, 9]\n");
    printf("Inorder check: ");
    printArray(result, size);
    printf("\n");

    free(result);
    freeTree(root);
}

void task2(void) {
    struct TreeNode *root = buildLectureTree();
    int size;
    int *result = inorderTraversal(root, &size);

    printf("Inorder result: ");
    printArray(result, size);
    printf("\nExpected: [1, 2, 3, 4, 6, 7, 9]\n");

    free(result);
    freeTree(root);
}

void task3(void) {
    struct TreeNode *root = buildLectureTree();
    int returnSize;
    int *columnSizes;
    int **result = levelOrder(root, &returnSize, &columnSizes);

    printf("Level order result: [");
    for (int i = 0; i < returnSize; i++) {
        printArray(result[i], columnSizes[i]);
        if (i < returnSize - 1) printf(", ");
        free(result[i]);
    }
    printf("]\nExpected: [[4], [2, 7], [1, 3, 6, 9]]\n");

    free(result);
    free(columnSizes);
    freeTree(root);
}

int main(void) {
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("               LAB 6 MENU\n");
        printf("========================================\n");
        printf("1. Build BST (701)\n");
        printf("2. Inorder DFS (94)\n");
        printf("3. Level Order BFS (102)\n");
        printf("0. Exit\nChoose: ");

        if (scanf("%d", &choice) != 1) break;

        printf("\n--------------\n");

        if (choice == 1) task1();
        else if (choice == 2) task2();
        else if (choice == 3) task3();
        else if (choice == 0) return 0;
        else printf("Invalid choice.\n");

        printf("--------------\n");
    }

    return 0;
}
