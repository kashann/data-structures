#include "iostream"

struct Student {
	char* name;
	int groupId;
};

struct ListNode {
	Student* info;
	ListNode* next;
};

struct HashTable {
	ListNode** buckets;
	int size;
};

void initHashTable(HashTable& ht, int dim) {
	ht.size = dim;
	ht.buckets = (ListNode**)malloc(sizeof(ListNode*)*dim);
	memset(ht.buckets, NULL, sizeof(ListNode*)*dim);
}

Student* createStudent(char* buffer, int group) {
	Student* student = NULL;
	student = (Student*)malloc(sizeof(Student));
	student->name = (char*)malloc(strlen(buffer) + 1);
	strcpy(student->name, buffer);
	student->groupId = group;
	return student;
}

ListNode* createNode(Student* st) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->info = st;
	node->next = NULL;
	return node;
}

ListNode* insertNode(ListNode* list, Student* st) {
	ListNode* node = createNode(st);
	if (list == NULL)
	{
		node->next = node;
	}
	else
	{
		node->next = list;
		ListNode* nRef = list;
		while (nRef->next != list)
			nRef = nRef->next;
		nRef->next = node;
	}
	return node;
}

int fhash(int key, int size) {
	return key%size;
}

void insertHT(HashTable ht, Student* st) {
	//1. to determine the position from the ht
	int position = fhash(st->groupId, ht.size);
	//2. get the list from the determined position
	ListNode* list = ht.buckets[position];
	//3. insert into the list, the st
	list = insertNode(list, st);
	//4. update the list from the ht
	ht.buckets[position] = list;
}

void printList(ListNode* list) {
	ListNode* refPoint = list;
	while (list->next != refPoint) {
		printf("Group: %d, Student: %s\n", list->info->groupId, list->info->name);
		list = list->next;
	}
	printf("Group: %d, Student: %s\n", list->info->groupId, list->info->name);
	list = list->next;
}

void printHashTable(HashTable ht) {
	if (ht.size > 0) {
		for (int i = 0; i < ht.size; i++)
			if (ht.buckets[i])
				printList(ht.buckets[i]);
	}
}

void main() {
	FILE* pFile = fopen("Text.txt", "r");
	HashTable hashTable;
	initHashTable(hashTable, 10);
	if (pFile) {
		char buffer[50];
		int groupNo;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile)) {
			fscanf(pFile, "%d", &groupNo);
			//1. create a student
			Student* stud = createStudent(buffer, groupNo);
			//2. inserting it in the hashtable
			insertHT(hashTable, stud);
			fscanf(pFile, "%s", buffer);
		}
		printHashTable(hashTable);
		fclose(pFile);
	}
}