#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode *newNode(int value) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    node->val = value;
    node->next = NULL;
    return node;
}

static void freeList(struct ListNode *head) {
    while (head != NULL) {
        struct ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static struct ListNode *appendNode(struct ListNode **head,
                                   struct ListNode **tail, int value) {
    struct ListNode *node = newNode(value);
    if (*head == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }
    *tail = node;
    return node;
}

static int isValid(const char *s) {
    size_t len = strlen(s);
    char *stack = malloc((len + 1) * sizeof(char));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    size_t top = 0;
    for (size_t i = 0; i < len; i++) {
        char c = s[i];

        if (c == '(' || c == '[' || c == '{') {
            stack[top++] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == 0) {
                free(stack);
                return 0;
            }

            char open = stack[--top];
            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{')) {
                free(stack);
                return 0;
            }
        } else {
            free(stack);
            return 0;
        }
    }

    int valid = (top == 0);
    free(stack);
    return valid;
}

static struct ListNode *getIntersectionNode(struct ListNode *headA,
                                            struct ListNode *headB) {
    struct ListNode *a = headA;
    struct ListNode *b = headB;

    while (a != b) {
        a = (a == NULL) ? headB : a->next;
        b = (b == NULL) ? headA : b->next;
    }
    return a;
}

static struct ListNode *reverseList(struct ListNode *head) {
    struct ListNode *previous = NULL;
    struct ListNode *current = head;

    while (current != NULL) {
        struct ListNode *next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

static int parseInts(const char *text, int *values, int maxValues) {
    int count = 0;
    const char *p = text;

    while (*p != '\0') {
        char *end;
        while (*p == ' ' || *p == '\t' || *p == ',') p++;
        if (*p == '\0') break;

        long value = strtol(p, &end, 10);
        if (end == p) return -1;
        if (count >= maxValues) return -1;
        values[count++] = (int)value;
        p = end;
        while (*p == ' ' || *p == '\t' || *p == ',') p++;
        if (*p != '\0' && *p != '-' && (*p < '0' || *p > '9')) return -1;
    }
    return count;
}

static int readLine(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) return 0;
    buffer[strcspn(buffer, "\r\n")] = '\0';
    return 1;
}

static void printList(const struct ListNode *head) {
    if (head == NULL) {
        printf("empty");
        return;
    }
    while (head != NULL) {
        printf("%d", head->val);
        if (head->next != NULL) printf(" -> ");
        head = head->next;
    }
}

int main(void) {
    char line[4096];
    char bracketInput[2048];
    int valuesA[1000], valuesB[1000], sharedValues[1000], reverseValues[1000];

    printf("Problem 20 - Valid Parentheses\n");
    printf("Enter brackets (example: {[]()}): ");
    if (!readLine(bracketInput, sizeof(bracketInput))) return 1;
    printf("Result: %s\n", isValid(bracketInput) ? "true" : "false");

    printf("\n--------------\n");
    printf("Problem 160 - Intersection of Two Linked Lists\n");
    printf("Enter: A-prefix | B-prefix | shared-tail (integers; use none if empty)\n");
    printf("Example: 4 1 | 5 6 1 | 8 4 5\n> ");
    if (!readLine(line, sizeof(line))) return 1;

    char *partA = line;
    char *partB = strchr(partA, '|');
    char *partShared = NULL;
    if (partB != NULL) {
        *partB++ = '\0';
        partShared = strchr(partB, '|');
    }
    if (partB == NULL || partShared == NULL) {
        fprintf(stderr, "Please enter three sections separated by '|'.\n");
        return 1;
    }
    *partShared++ = '\0';

    int countA = (strcmp(partA, "none") == 0) ? 0 :
                 parseInts(partA, valuesA, 1000);
    int countB = (strcmp(partB, "none") == 0) ? 0 :
                 parseInts(partB, valuesB, 1000);
    int countShared = (strcmp(partShared, "none") == 0) ? 0 :
                      parseInts(partShared, sharedValues, 1000);
    if (countA < 0 || countB < 0 || countShared < 0) {
        fprintf(stderr, "Invalid integer list.\n");
        return 1;
    }

    struct ListNode *headA = NULL, *tailA = NULL;
    struct ListNode *headB = NULL, *tailB = NULL;
    for (int i = 0; i < countA; i++) appendNode(&headA, &tailA, valuesA[i]);
    for (int i = 0; i < countB; i++) appendNode(&headB, &tailB, valuesB[i]);

    struct ListNode *sharedHead = NULL, *sharedTail = NULL;
    for (int i = 0; i < countShared; i++)
        appendNode(&sharedHead, &sharedTail, sharedValues[i]);

    if (tailA != NULL) tailA->next = sharedHead;
    else headA = sharedHead;
    if (tailB != NULL) tailB->next = sharedHead;
    else headB = sharedHead;

    struct ListNode *intersection = getIntersectionNode(headA, headB);
    if (intersection == NULL) {
        printf("Intersection: none\n");
    } else {
        printf("Intersection node value: %d\n", intersection->val);
    }

    /* Free shared tail exactly once, then free the two independent prefixes. */
    if (tailA != NULL) tailA->next = NULL;
    if (tailB != NULL) tailB->next = NULL;
    freeList(headA);
    freeList(headB);
    freeList(sharedHead);

    printf("\n--------------\n");
    printf("Problem 206 - Reverse Linked List\n");
    printf("Enter list values separated by spaces (example: 1 2 3 4 5; use none for empty)\n> ");
    if (!readLine(line, sizeof(line))) return 1;

    int countReverse = (strcmp(line, "none") == 0) ? 0 :
                       parseInts(line, reverseValues, 1000);
    if (countReverse < 0) {
        fprintf(stderr, "Invalid integer list.\n");
        return 1;
    }

    struct ListNode *reverseHead = NULL, *reverseTail = NULL;
    for (int i = 0; i < countReverse; i++)
        appendNode(&reverseHead, &reverseTail, reverseValues[i]);

    reverseHead = reverseList(reverseHead);
    printf("Reversed list: ");
    printList(reverseHead);
    printf("\n");
    freeList(reverseHead);

    return 0;
}
