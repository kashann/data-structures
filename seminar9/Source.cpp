#include "iostream"

struct Pacient {
	char* name;
	int age;
};

struct HeapItem {
	int priority;
	Pacient* pacient;
};

struct Heap {
	HeapItem** items;
	int size;
	int noEl;
};

void initHeap(Heap& heap, int size) {
	heap.noEl = 0;
	heap.size = size;
	heap.items = (HeapItem**)malloc(sizeof(HeapItem*)*size);
	memset(heap.items, NULL, sizeof(HeapItem*)*size);
}

HeapItem* createItem(int key, char* buffer, int age) {
	HeapItem* item = NULL;
	item = (HeapItem*)malloc(sizeof(HeapItem));
	item->pacient = (Pacient*)malloc(sizeof(Pacient));
	item->pacient->age = age;
	item->pacient->name = (char*)malloc(strlen(buffer) + 1);
	strcpy(item->pacient->name, buffer);
	item->priority = key;
	return item;
}

void HeapUp(Heap& heap, int current) {
	if (current > 0) {
		int parent = (current - 1) / 2;
		if (heap.items[current]->priority > heap.items[parent]->priority) {
			HeapItem* tmp = heap.items[current];
			heap.items[current] = heap.items[parent];
			heap.items[parent] = tmp;
			HeapUp(heap, parent);
		}
	}
}

void EnqueueHeap(Heap& heap, HeapItem* item) {
	if (heap.noEl < heap.size) {
		heap.items[heap.noEl] = item;
		heap.noEl++;
		HeapUp(heap, heap.noEl - 1);
	}
}

void HeapDown(Heap& heap, int current) {
	int left = 2 * current + 1;
	int right = 2 * current + 2;
	int max;
	if (left < heap.noEl) {
		if (left == heap.noEl)//equiv with if(right < heap.noEl)
			max = left;
		if (heap.items[left]->priority > heap.items[right]->priority)
			max = left;
		else
			max = right;
		if (heap.items[current]->priority < heap.items[max]->priority) {
			HeapItem* item = heap.items[current];
			heap.items[current] = heap.items[max];
			heap.items[max] = item;
			HeapDown(heap, max);
		}
	}
	if (current > 0) {
		int parent = (current - 1) / 2;
		if (heap.items[current]->priority > heap.items[parent]->priority) {
			heap.items[current];
			HeapDown(heap, parent);
		}
	}
}

HeapItem* DequeueHeap(Heap& heap) {
	HeapItem* item = NULL;
	if (heap.noEl > 0) {
		item = heap.items[0];
		heap.items[0] = heap.items[heap.noEl - 1];
		heap.noEl--;
		HeapDown(heap, 0);
	}
	return item;
}

void printHeap(Heap& heap) {
	for (int i = 0; i < heap.size; i++) {
		printf("Key: %d, name: %s\n", heap.items[i]->priority, heap.items[i]->pacient->name);
	}
}

void main() {
	Heap heap;
	initHeap(heap, 7);
	FILE* pFile = fopen("Text.txt", "r");
	if (pFile) {
		int key, age;
		char buffer[50];
		fscanf(pFile, "%d", &key);
		while (!feof(pFile)) {
			fscanf(pFile, "%s", buffer);
			fscanf(pFile, "%d", &age);
			HeapItem* item = createItem(key, buffer, age);
			EnqueueHeap(heap, item);
			fscanf(pFile, "%d", &key);
		}
		//HeapItem* item = DequeueHeap(heap);
		fclose(pFile);
		printHeap(heap);
		printf("%d\n", DequeueHeap(heap)->priority);
		printf("%d\n", DequeueHeap(heap)->priority);
		printf("%d\n", DequeueHeap(heap)->priority);
		printf("%d\n", DequeueHeap(heap)->priority);
		printf("%d\n", DequeueHeap(heap)->priority);
		printf("%d\n", DequeueHeap(heap)->priority);
		printf("%d\n", DequeueHeap(heap)->priority);
	}
}