#include <stdio.h>
#include <stdlib.h>

// Problem 1

int numberOfSteps(int num) {
    if (num == 0)
        return 0;

    if (num % 2 == 0)
        return 1 + numberOfSteps(num / 2);

    return 1 + numberOfSteps(num - 1);
}

void runProblem1342(void) {
    int num;

    printf("Problem 1: Number of Steps to Reduce a Number to Zero\n");
    printf("Enter a non-negative integer: ");

    if (scanf("%d", &num) != 1 || num < 0) {
        printf("Invalid input. Please enter a non-negative integer.\n");
        return;
    }

    printf("Number of steps: %d\n", numberOfSteps(num));
}

// Problem 2

void mergeSortedArray(int nums1[], int m, int nums2[], int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }

    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}

void runProblem88(void) {
    int m, n;
    int i;

    printf("Problem 2: Merge Sorted Array\n");
    printf("Enter m (number of valid elements in nums1): ");
    if (scanf("%d", &m) != 1 || m < 0) {
        printf("Invalid m.\n");
        return;
    }

    printf("Enter n (number of elements in nums2): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid n.\n");
        return;
    }

    int *nums1 = malloc((size_t)(m + n) * sizeof(int));
    int *nums2 = malloc((size_t)n * sizeof(int));

    if ((m + n > 0 && nums1 == NULL) || (n > 0 && nums2 == NULL)) {
        printf("Memory allocation failed.\n");
        free(nums1);
        free(nums2);
        return;
    }

    printf("Enter %d sorted element(s) for nums1: ", m);
    for (i = 0; i < m; i++) {
        if (scanf("%d", &nums1[i]) != 1) {
            printf("Invalid input.\n");
            free(nums1);
            free(nums2);
            return;
        }
    }

    for (i = m; i < m + n; i++)
        nums1[i] = 0;

    printf("Enter %d sorted element(s) for nums2: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &nums2[i]) != 1) {
            printf("Invalid input.\n");
            free(nums1);
            free(nums2);
            return;
        }
    }

    mergeSortedArray(nums1, m, nums2, n);

    printf("Merged array: [");
    for (i = 0; i < m + n; i++) {
        printf("%d", nums1[i]);
        if (i < m + n - 1)
            printf(", ");
    }
    printf("]\n");

    free(nums1);
    free(nums2);
}

// Problem 3

void mergeParts(int nums[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k] = nums[i];
            i++;
        } else {
            temp[k] = nums[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = nums[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = nums[j];
        j++;
        k++;
    }

    for (i = left; i <= right; i++)
        nums[i] = temp[i];
}

void mergeSort(int nums[], int temp[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(nums, temp, left, mid);
    mergeSort(nums, temp, mid + 1, right);
    mergeParts(nums, temp, left, mid, right);
}

int *sortArray(int nums[], int numsSize, int *returnSize) {
    int *result;
    int *temp;
    int i;

    *returnSize = 0;

    if (numsSize <= 0)
        return NULL;

    result = malloc((size_t)numsSize * sizeof(int));
    temp = malloc((size_t)numsSize * sizeof(int));

    if (result == NULL || temp == NULL) {
        free(result);
        free(temp);
        return NULL;
    }

    for (i = 0; i < numsSize; i++)
        result[i] = nums[i];

    mergeSort(result, temp, 0, numsSize - 1);

    free(temp);
    *returnSize = numsSize;
    return result;
}

void runProblem912(void) {
    int n;
    int i;
    int returnSize;
    int *nums;
    int *sorted;

    printf("Problem 3: Sort an Array (Merge Sort)\n");
    printf("Enter array length: ");

    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Please enter an array length of at least 1.\n");
        return;
    }

    nums = malloc((size_t)n * sizeof(int));
    if (nums == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter %d integer(s): ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &nums[i]) != 1) {
            printf("Invalid input.\n");
            free(nums);
            return;
        }
    }

    sorted = sortArray(nums, n, &returnSize);

    if (sorted == NULL) {
        printf("Sorting failed (memory allocation problem).\n");
        free(nums);
        return;
    }

    printf("Sorted array: [");
    for (i = 0; i < returnSize; i++) {
        printf("%d", sorted[i]);
        if (i < returnSize - 1)
            printf(", ");
    }
    printf("]\n");

    free(nums);
    free(sorted);
}

// Menu

int main(void) {
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("              LAB 3 MENU\n");
        printf("========================================\n");
        printf("1. Number of Steps to Reduce a Number to Zero\n");
        printf("2. Merge Sorted Array\n");
        printf("3. Sort an Array (Merge Sort)\n");
        printf("0. Exit\n");
        printf("Choose a problem: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        printf("\n--------------\n");

        switch (choice) {
            case 1:
                runProblem1342();
                break;
            case 2:
                runProblem88();
                break;
            case 3:
                runProblem912();
                break;
            case 0:
                printf("Exiting Lab 3.\n");
                return 0;
            default:
                printf("Invalid choice. Please choose 0, 1, 2, or 3.\n");
        }

        printf("--------------\n");
    }

    return 0;
}
