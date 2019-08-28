#include <iostream>
using namespace std;

struct Student {
	char* name;
	int age;
};

struct SList {
	Student* info;
	SList* pNext;
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
	return node;
}

void insertNode(SList** list, SList* node) {
	node->pNext = *list;
	*list = node;
}

void printStudents(SList* list) {
	while (list) {
		printf("Student %s, age: %d\n", list->info->name, list->info->age);
		list = list->pNext;
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
	}
}