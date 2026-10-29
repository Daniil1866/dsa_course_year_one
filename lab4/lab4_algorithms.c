#include <stdio.h>
#include <stdlib.h>

// quicksort

int partition(int values[], int lo, int hi) {
    int pivot = values[lo];
    int boundary = lo;

    for (int scan = lo + 1; scan < hi; scan++) {
        if (values[scan] < pivot) {
            boundary++;
            int temp = values[boundary];
            values[boundary] = values[scan];
            values[scan] = temp;
        }
    }

    values[lo] = values[boundary];
    values[boundary] = pivot;
    return boundary;
}

void quickSort(int values[], int lo, int hi) {
    if (hi - lo <= 1)
        return;

    int p = partition(values, lo, hi);
    quickSort(values, lo, p);
    quickSort(values, p + 1, hi);
}

// Merge sort from lab3

void mergeParts(int values[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (values[i] <= values[j])
            temp[k++] = values[i++];
        else
            temp[k++] = values[j++];
    }
    while (i <= mid)
        temp[k++] = values[i++];
    while (j <= right)
        temp[k++] = values[j++];

    for (i = left; i <= right; i++)
        values[i] = temp[i];
}

void mergeSort(int values[], int temp[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(values, temp, left, mid);
    mergeSort(values, temp, mid + 1, right);
    mergeParts(values, temp, left, mid, right);
}

// Helpers

void printArray(const int values[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", values[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("]\n");
}

int readArray(int values[], int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &values[i]) != 1)
            return 0;
    }
    return 1;
}

void runQuickSort(void) {
    int n;
    printf("Local task: Quicksort\nEnter array length (0 or more): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid array length.\n");
        return;
    }

    int *quickValues = NULL, *mergeValues = NULL, *temp = NULL;
    if (n > 0) {
        quickValues = malloc((size_t)n * sizeof(int));
        mergeValues = malloc((size_t)n * sizeof(int));
        temp = malloc((size_t)n * sizeof(int));
        if (quickValues == NULL || mergeValues == NULL || temp == NULL) {
            printf("Memory allocation failed.\n");
            free(quickValues);
            free(mergeValues);
            free(temp);
            return;
        }
    }

    printf("Enter %d integer(s): ", n);
    if (!readArray(quickValues, n)) {
        printf("Invalid input.\n");
        free(quickValues);
        free(mergeValues);
        free(temp);
        return;
    }

    for (int i = 0; i < n; i++)
        mergeValues[i] = quickValues[i];

    quickSort(quickValues, 0, n);
    if (n > 0)
        mergeSort(mergeValues, temp, 0, n - 1);

    printf("Quicksort result: ");
    printArray(quickValues, n);
    printf("Merge sort result: ");
    printArray(mergeValues, n);

    int same = 1;
    for (int i = 0; i < n; i++) {
        if (quickValues[i] != mergeValues[i]) {
            same = 0;
            break;
        }
    }
    printf("Results match: %s\n", same ? "yes" : "no");

    free(quickValues);
    free(mergeValues);
    free(temp);
}

// LeetCode 704: Binary Search

int search(int nums[], int numsSize, int target) {
    int lo = 0, hi = numsSize;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] == target)
            return mid;
        if (nums[mid] < target)
            lo = mid + 1;
        else
            hi = mid;
    }
    return -1;
}

void runBinarySearch(void) {
    int n, target;
    printf("LeetCode 704: Binary Search\nEnter array length (0 or more): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid array length.\n");
        return;
    }

    int *nums = NULL;
    if (n > 0) {
        nums = malloc((size_t)n * sizeof(int));
        if (nums == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
    }

    printf("Enter %d sorted integer(s): ", n);
    if (!readArray(nums, n)) {
        printf("Invalid input.\n");
        free(nums);
        return;
    }
    printf("Enter target: ");
    if (scanf("%d", &target) != 1) {
        printf("Invalid target.\n");
        free(nums);
        return;
    }

    printf("Result index: %d\n", search(nums, n, target));
    free(nums);
}

// LeetCode 35: Search Insert Position

int searchInsert(int nums[], int numsSize, int target) {
    int lo = 0, hi = numsSize;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] < target)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

void runSearchInsert(void) {
    int n, target;
    printf("LeetCode 35: Search Insert Position\nEnter array length (0 or more): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid array length.\n");
        return;
    }

    int *nums = NULL;
    if (n > 0) {
        nums = malloc((size_t)n * sizeof(int));
        if (nums == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
    }

    printf("Enter %d sorted integer(s): ", n);
    if (!readArray(nums, n)) {
        printf("Invalid input.\n");
        free(nums);
        return;
    }
    printf("Enter target: ");
    if (scanf("%d", &target) != 1) {
        printf("Invalid target.\n");
        free(nums);
        return;
    }

    printf("Insertion position: %d\n", searchInsert(nums, n, target));
    free(nums);
}


// menu

int main(void) {
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("              LAB 4 MENU\n");
        printf("========================================\n");
        printf("1. Local task: Quicksort\n");
        printf("2. LeetCode 704: Binary Search\n");
        printf("3. LeetCode 35: Search Insert Position\n");
        printf("0. Exit\nChoose a task: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        printf("\n--------------\n");
        switch (choice) {
            case 1: runQuickSort(); break;
            case 2: runBinarySearch(); break;
            case 3: runSearchInsert(); break;
            case 0:
                printf("Exiting Lab 4.\n");
                return 0;
            default:
                printf("Invalid choice. Choose 0, 1, 2, or 3.\n");
        }
        printf("--------------\n");
    }
    return 0;
}
