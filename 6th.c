#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} MinHeap;

void initHeap(MinHeap* heap) {
    heap->size = 0;
}

int parent(int index) {
    return (index - 1) / 2;
}

int leftChild(int index) {
    return (2 * index) + 1;
}

int rightChild(int index) {
    return (2 * index) + 2;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(MinHeap* heap, int value) {
    if (heap->size == MAX_SIZE) return;
    heap->data[heap->size] = value;
    int current = heap->size++;
    while (current > 0 && heap->data[current] < heap->data[parent(current)]) {
        swap(&heap->data[current], &heap->data[parent(current)]);
        current = parent(current);
    }
}

void heapify(MinHeap* heap, int index) {
    int smallest = index, left = leftChild(index), right = rightChild(index);
    if (left < heap->size && heap->data[left] < heap->data[smallest]) smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest]) smallest = right;
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

int deleteMin(MinHeap* heap) {
    if (heap->size == 0) return -1;
    int min = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify(heap, 0);
    return min;
}

void display(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) printf("%d ", heap->data[i]);
    printf("\n");
}

int main() {
    MinHeap heap;
    initHeap(&heap);
    int choice, value;
    while (1) {
        printf("\n1. Insert\n2. Delete Min\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter value: ");
            scanf("%d", &value);
            insert(&heap, value);
        } else if (choice == 2) {
            value = deleteMin(&heap);
            if (value != -1) printf("Deleted: %d\n", value);
        } else if (choice == 3) display(&heap);
        else if (choice == 4) break;
    }
    return 0;
}
