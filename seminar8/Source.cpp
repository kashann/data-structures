#include "iostream"

struct HashTable {
	int** ht;
	int size;
	int noEl;
};

void initHashTable(HashTable& ht, int dim) {
	ht.noEl = 0;
	ht.size = dim;
	ht.ht = (int**)malloc(sizeof(int*)*dim);
	memset(ht.ht, NULL, sizeof(int*)*dim);
}

int fhash(int val, int dim) {
	return val%dim;
}

void resizeHT(HashTable& ht) {
	//1. declare the doubled hash table
	//2. allocate memory
	int newSize = ht.size * 2;
	int** newHt = (int**)malloc(sizeof(int*)*newSize);
	memset(newHt, NULL, sizeof(int*)*newSize);
	//3. copy the elements from the original array
	for (int i = 0; i < ht.size; i++) {
		if (ht.ht[i] != NULL) {
			int index = fhash(*ht.ht[i], newSize);
			newHt[index] = (int*)malloc(sizeof(int));
			*newHt[index] = *ht.ht[i];
			free(ht.ht[i]);
		}
	}
	//4. free memory for the initial array
	free(ht.ht);
	//5. replacing the hashtables
	ht.ht = newHt;
	ht.size = newSize;
}

void printHT(HashTable ht) {
	if (ht.size > 0) {
		for (int i = 0; i < ht.size; i++)
			if (ht.ht[i] != NULL)
				printf("%d: %d\n", i, *ht.ht[i]);
	}
}

void insertHT(HashTable& ht, int value) {
	int index = fhash(value, ht.size);
	ht.noEl++;
	double loadingFactor = ((double)ht.noEl / ht.size);
	if (ht.ht[index] != NULL) {
		//probing operation
		while (ht.ht[index] != NULL && index < ht.size)
			index++;
		if (index == ht.size || loadingFactor > 0.5) {
			//1. we use a circular array implementation
			//2. we resize the entire hashtable
			resizeHT(ht);
		}
	}
	ht.ht[index] = (int*)malloc(sizeof(int));
	*ht.ht[index] = value;
}

void main() {
	HashTable hashTable;
	initHashTable(hashTable, 7);
	insertHT(hashTable, 3);
	insertHT(hashTable, 1);
	insertHT(hashTable, 54);
	insertHT(hashTable, 23);
	insertHT(hashTable, 27);
	insertHT(hashTable, 29);
	insertHT(hashTable, 30);
	insertHT(hashTable, 31);
	printHT(hashTable);
}