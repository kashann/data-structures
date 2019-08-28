#include <iostream>
using namespace std;

struct Student {
	char* name;
	int age;
};

struct SList {
	Student* info;
	SList* pNext;
	SList* pPrev;
};

Student* createInfo(char* name, int age) {
	//1. declaring the element that you need to create and return
	Student* student = NULL;
	//2. allocate memory for the ptr
	student = (Student*)malloc(sizeof(Student));
	//3. initialize the variable
	student->age = age;
	student->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(student->name, name);
	//4. returning the pointer
	return student;
}

SList* createNode(Student* stud) {
	SList* node = (SList*)malloc(sizeof(SList));
	node->info = stud;
	node->pNext = NULL;
	node->pPrev = NULL;
	return node;
}

void insertNode(SList** list, SList* node) {
	node->pNext = *list;
	if (*list == NULL)
		*list = node;
	else
		(*list)->pPrev = node;
	*list = node;
}

void printStudents(SList* list) {
	printf("List from head to tail:\n");
	while (list->pNext) {
		printf("Student %s, age: %d\n", list->info->name, list->info->age);
		list = list->pNext;
	}
	printf("Student %s, age: %d\n", list->info->name, list->info->age);

	printf("List from tail to head:\n");
	while (list) {
		printf("Student %s, age: %d\n", list->info->name, list->info->age);
		list = list->pPrev;
	}
	printf("\n");
}

void insertBeforeKey(SList*& list, Student* stud, char* key) { //list passed by address
	SList* node = createNode(stud);
	if (!list) {
		insertNode(&list, node);
	}
	else {
		SList* tmp = list; //only when we pass the list by address
		while (tmp->pNext && strcmp(tmp->info->name, key) != 0)
			tmp = tmp->pNext;
		if (strcmp(tmp->info->name, key) == 0) {
			//insert the element before
			//1.connect the node to the structure
			node->pNext = tmp;
			node->pPrev = tmp->pPrev;
			//2.connect the structure to the node
			tmp->pPrev->pNext = node;
			tmp->pPrev = node;
		}
		else {
			//insert the element after the tail
			node->pPrev = list;
			list->pNext = node;
		}
	}
}

void main() {
	FILE* pFile = nullptr;
	pFile = fopen("Source.txt", "r");
	char buffer[100];
	int age;
	SList* list = NULL;
	if (pFile) {
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile)) {
			fscanf(pFile, "%d", &age);
			//1. create usefull info
			Student* student = createInfo(buffer, age);
			//2. create the list element
			SList* node = createNode(student);
			//3. insert the element in the list
			insertNode(&list, node);

			fscanf(pFile, "%s", buffer);
		}
		printStudents(list);
		Student* student = createInfo("Student7", 22);
		insertBeforeKey(list, student, "Student3"); 
		//hw make it work for stud4 using online ase ro resource and send hw by email with subj DS1052LH 23:55
		printStudents(list);
	}
}