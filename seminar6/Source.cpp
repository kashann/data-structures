#include "iostream"
using namespace std;
struct Student
{
	char* name;
	int age;
};
struct SList
{
	Student* info;
	SList* pNext;
	SList* pPrev; //added
};

Student* createInfo(char* name, int age)
{
	//1.declaring the element that 
	//you need to create and return
	Student* student = NULL;
	//2.allocate memory for the ptr
	student = (Student*)malloc(sizeof(Student));
	//3.init the variable
	student->age = age;
	student->name = (char*)malloc(sizeof(char)*
		(strlen(name) + 1));
	strcpy(student->name, name);
	//4.returning the pointer
	return student;
}
SList* createNode(Student* stud)
{
	SList* node = (SList*)malloc(sizeof(SList));
	node->info = stud;
	node->pNext = NULL;
	node->pPrev = NULL; //added for circular
	return node;
}

void insertNode(SList** list, SList* node)
{
	/*node->pNext = *list; //this is for simple linked list
	*list = node;*/
	if (*list == NULL)
	{
		node->pNext = node->pPrev = node;
	}
	else
	{
		node->pNext = *list;
		node->pPrev = (*list)->pPrev;
		(*list)->pPrev->pNext = node;
		//(*list)->pNext = node;
	}
	*list = node;
}

void printStudents(SList* list)
{
	SList* temp = list;
	do
	{		
		printf("Student %s, age: %d \n",
			list->info->name,
			list->info->age);
		list = list->pNext;		
	} while (list != temp);
}

void interchange(SList*& p, SList*& q) 
{
	SList* aux = q;
	SList* tmp1 = p->pNext->pNext;
	p->pNext->pNext = q->pNext->pNext;//1.
	aux->pNext->pNext = aux;//2.
	SList* tmp = aux->pNext;
	aux->pNext = p->pNext;//3.
	p->pNext = tmp;//4.
}

void main()
{
	//interchanging two items
	FILE* pFile = nullptr;
	pFile = fopen("Text.txt", "r");
	char buffer[100]; int age;
	SList* list = NULL;
	if (pFile)
	{
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile))
		{
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
		interchange(list, list->pNext->pNext);
		printf("\n--------INTERCHANGE--------\n");
		printStudents(list);
		SList* head = list;
		while (head)
		{
			SList* next = head->pNext;
			while (next)
			{
				if (head->info->age > next->info->age)
					interchange(head, next); //make it work, we need some ifs in the interchange function
				next = next->pNext;
			}
			head = head->pNext;
		}
	}//chain probing and rehashing FOR hashtables
}