#include <iostream>
using namespace std;

struct DLList {
	int info;
	DLList* pNext;
	DLList* pPrev;
};

struct SLList {
	int info;
	SLList* pNext;
};

DLList* createNode(int info) {
	DLList* node = (DLList*)malloc(sizeof(DLList));
	node->info = info;
	node->pNext = NULL;
	node->pPrev = NULL;
	return node;
}

SLList* createNodeSLList(int info) {
	SLList* node = (SLList*)malloc(sizeof(SLList));
	node->info = info;
	node->pNext = NULL;
	return node;
}

void printInfoDLL(DLList* list) {
	printf("\nList from head to tail:\n");
	while (list->pNext) {
		printf("%d ", list->info);
		list = list->pNext;
	}
	printf("%d ", list->info);
	printf("\nList from tail to head:\n");
	while (list) {
		printf("%d ", list->info);
		list = list->pPrev;
	}
	printf("\n");
}

void printInfoSLL(SLList* list) {
	printf("\nSimple Linked List:\n");
	while (list->pNext) {
		printf("%d ", list->info);
		list = list->pNext;
	}
	//printf("%d ", list->info);
}

void insertNode(DLList** list, DLList* node) { //10th a)
	node->pNext = *list;
	if (*list == NULL)
		*list = node;
	else
		(*list)->pPrev = node;
	*list = node;
}

void insertNodeAtHead(DLList*& list, int info) {
	DLList* node = createNode(info);
	if (!list) {
		insertNode(&list, node);
	}
	else {
		DLList* tmp = list;
		list->pPrev = node;
		node->pNext = list;
		insertNode(&list, node);
	}
}

void insertIfDoesntExist(DLList*& list, int info) { //1st a)
	int c = 0;
	DLList* node = createNode(info);
	if (!list) {
		insertNode(&list, node);
	}
	else {
		DLList* tmp = list;
		while (tmp->pNext) {
			tmp = tmp->pNext;
			if(tmp->info == info)
				c = 1;
		}
		if (c == 0) {
			list->pPrev = node;
			node->pNext = list;
			insertNode(&list, node);
		}
	}
}

int getDistanceBetweenMinAndMaxNode(DLList* list) { //1st b)
	int distance, c = 0, posMin = 0, posMax = 0;
	if (list == NULL) {
		return -1;
	}
	int max = list->info;
	int min = list->info;
	while (list != NULL) {
		if (list->info > max) {
			max = list->info;
			posMax = c;
		}
		if (list->info < min) {
			min = list->info;
			posMin = c;
		}
		c++;
		list = list->pNext;
	}
	distance = posMax - posMin;
	if (distance >= 0)
		return distance;
	else if (distance < 0)
		return -1 * distance;
}

int noEvenOddItems(DLList* list, int odd) { //2nd & 11th b)
	int c = 0;
	if (list == NULL) {
		return -1;
	}
	while (list != NULL) {
		if (list->info % 2 == odd) {
			c++;
		}
		list = list->pNext;
	}
	return c;
}

int noDivElemsInInterval(DLList* list, int x, int y, int k) { //5th b)
	int c = 0;
	if (list == NULL) {
		return -1;
	}
	while (list != NULL) {
		if (list->info % k == 0 && list->info >= x && list->info <= y && list->info != 0) {
			c++;
		}
		list = list->pNext;
	}
	return c;
}

int noDivisibleNumbers(DLList* list, int z) { //9th b)
	int c = 0;
	if (list == NULL) {
		return -1;
	}
	while (list != NULL) {
		if (list->info % z == 0 && list->info != 0) {
			c++;
		}
		list = list->pNext;
	}
	return c;
}

int noItemsBiggerThanFirst(DLList* list) { //10th b)
	int c = 0;
	if (list == NULL) {
		return -1;
	}
	int elem = list->info;
	while (list != NULL) {
		if (list->info > elem) {
			c++;
		}
		list = list->pNext;
	}
	return c;
}

int noApparitions(DLList* list, int nr) { //12th b)
	int c = 0;
	if (list == NULL) {
		return -1;
	}
	int elem = list->info;
	while (list != NULL) {
		if (list->info == nr) {
			c++;
		}
		list = list->pNext;
	}
	return c;
}

void insertAfterKey(DLList*& list, int info, int y) { //3rd a)
	DLList* node = createNode(info);
	if (!list) {
		insertNode(&list, node);
	}
	else {
		DLList* tmp = list;
		while (tmp->pNext && tmp->info != y)
			tmp = tmp->pNext;
		if (tmp->info == y) {
			node->pPrev = tmp;
			node->pNext = tmp->pNext;
			tmp->pNext->pPrev = node;
			tmp->pNext = node;
		}
		else {
			node->pPrev = list;
			list->pNext = node;
		}
	}
}

void insertOrdered(DLList*& list, int info) { //4th a)
	DLList* node = createNode(info);
	if (!list) {
		insertNode(&list, node);
	}
	else {
		DLList* tmp = list;
		while (tmp->pNext) {
			tmp = tmp->pNext;
			if (tmp->info < info && info < tmp->pNext->info) {
				node->pPrev = tmp;
				node->pNext = tmp->pNext;
				tmp->pNext->pPrev = node;
				tmp->pNext = node;
			}
		}
	}
}

int getMaxNode(DLList* list)
{
	if (list == NULL) {
		return -99999;
	}
	int max = list->info;
	while (list != NULL) {
		if (list->info > max) {
			max = list->info;
		}
		list = list->pNext;
	}
	return max;
}

void insertMaxVal(DLList*& list, int info) { //8rd a)
	int max = getMaxNode(list);
	DLList* node = createNode(info);
	if (!list) {
		insertNode(&list, node);
	}
	else {
		if (info > max) {
			list->pPrev = node;
			node->pNext = list;
			list = node;
		}
		else {
			DLList* temp = list;
			while (temp->pNext)
				temp = temp->pNext;
			temp->pNext = node;
			node->pPrev = temp;
		}
	}
}

void insertOnPosition(DLList*& list, int info, int k) { //11th a)
	DLList* node = createNode(info);
	int c = 1;
	if (!list) {
		insertNode(&list, node);
	}
	else {
		DLList* tmp = list;
		while (tmp->pNext && k != c) {
			tmp = tmp->pNext;
			c++;
		}			
		if (k == c) {
			node->pPrev = tmp;
			node->pNext = tmp->pNext;
			tmp->pNext->pPrev = node;
			tmp->pNext = node;
		}
		else {
			node->pPrev = list;
			list->pNext = node;
		}
	}
}

void main() {
	DLList* list = NULL;
	DLList* node1 = createNode(1);
	DLList* node2 = createNode(2);
	DLList* node3 = createNode(3);
	DLList* node6 = createNode(6);
	cout << "1: Simple Linked List\n2: Doubly Linked List\nYour choice: ";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: 
		cout << "Simple Linked List\n";
		break;		
	case 2:
		insertNode(&list, node6);
		insertNode(&list, node3);
		insertNode(&list, node2);
		insertNode(&list, node1);

		insertIfDoesntExist(list, 0);
		insertIfDoesntExist(list, 2);
		insertAfterKey(list, 4, 3);
		insertOrdered(list, 5);
		insertOnPosition(list, 9, 1);
		insertMaxVal(list, 8);
		insertMaxVal(list, 10);
		insertNodeAtHead(list, 6);
		printInfoDLL(list);
		cout << "Distance between min and max node: " << getDistanceBetweenMinAndMaxNode(list) << endl;
		cout << noEvenOddItems(list, 1) << " odd items, and " << noEvenOddItems(list, 0) << " even items\n";
		cout << noDivElemsInInterval(list, 5, 10, 3) << " numbers divisible with 3 in [5,10]\n";
		cout << noDivisibleNumbers(list, 2) << " numbers divisible with 4\n";
		cout << noItemsBiggerThanFirst(list) << " items bigger than the first one\n";
		cout << noApparitions(list, 6) << " apparitions of nr 6\n";
		break;
	}	
}