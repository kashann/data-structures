#include <iostream>

enum Speciality {
	NEUROLOGY = 5,
	CARDIOLOGY = 10
};

struct Doctor {
	char* name;
	Speciality spec;
};

struct List {
	Doctor* info;
	List* next;
	List* prev;
};

struct Queue {
	List* head;
	List* tail;
};

Doctor* createDoctor(char* name, int spec) {
	Doctor* doc = NULL;
	doc = (Doctor*)malloc(sizeof(Doctor));
	doc->name = (char*)malloc(strlen(name) + 1);
	strcpy(doc->name, name);
	if (spec == 5)
		doc->spec = Speciality::NEUROLOGY;
	else if (spec == 10)
		doc->spec = Speciality::CARDIOLOGY;
	return doc;
}

List* createNode(Doctor* info) {
	List* node = (List*)malloc(sizeof(List));
	node->info = info;
	node->next = node->prev = NULL;
	return node;
}

void putQueue(Queue* queue, List* node) {
	if (queue->head == NULL) {
		queue->tail = queue->head = node;
	}
	else {
		node->prev = queue->tail;
		queue->tail->next = node;
		queue->tail = node;
	}
}

void printQueue(Queue queue) {
	while (queue.head) {
		printf("Name: %s || ", queue.head->info->name);
		switch (queue.head->info->spec)
		{
		case Speciality::NEUROLOGY: printf("Speciality: NEUROLOGY\n");
			break;
		case Speciality::CARDIOLOGY: printf("Speciality: CARDIOLOGY\n");
			break;
		default:
			break;
		}
		queue.head = queue.head->next;		
	}
	printf("\n");
}

Doctor* getQueue(Queue& queue) {
	Doctor* doctor = NULL;
	if (queue.head) {
		doctor = queue.head->info;
		List* tmp = queue.head;
		queue.head = queue.head->next;
		if(queue.head)
			queue.head->prev = NULL;
		free(tmp);
	}
	return doctor;
}

void main() {
	FILE* pFile = fopen("Text.txt", "r");
	Queue queue;
	queue.head = queue.head = NULL;
	if (pFile) {
		char buffer[100];
		int spec;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile)) {
			fscanf(pFile, "%d", &spec);
			//1. create the doctor element
			Doctor* doctor = createDoctor(buffer, spec);
			//2. create a list element
			List* node = createNode(doctor);
			//3. enqueue the element
			putQueue(&queue, node);

			fscanf(pFile, "%s", buffer);
		}

		fclose(pFile);
		//printQueue(queue);
		while (Doctor* doctor = getQueue(queue)) {
			printf("Name: %s || ", doctor->name);
			switch (doctor->spec)
			{
			case Speciality::NEUROLOGY: printf("Speciality: NEUROLOGY\n");
				break;
			case Speciality::CARDIOLOGY: printf("Speciality: CARDIOLOGY\n");
				break;
			default:
				break;
			}
		}
	}
}