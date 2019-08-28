//#include <stdio.h>
#include <iostream>
#include <memory.h>

struct Letter
{
	int : 5;
	int sign : 1;
	int : 2;
};

void main()
{
	int a = 5;
	int b = 7;
	//the initialization is mandatory

	int* const ptr1 = &a;
	//prt1 = &b;
	*ptr1 = 8;
	//is optional
	int const * ptr2;
	//const int * ptr2;

	a = 3;
	ptr2 = &a;
	//*ptr2 = &b;
	ptr2 = &b;
	int const * const ptr3 = &a;
	int * pArray1 = new int(3);
	int * pArray2 = new int[3];
	memset(pArray2, NULL, sizeof(int*) * 3);
	int* pArray3[10];
	memset(pArray3, NULL, sizeof(pArray3));

	char letter = 'A';
	printf("letter=%c\n", letter);
	letter = letter | 32;
	printf("letter=%c\n", letter);
	letter = letter & 223;
	printf("letter=%c\n", letter);

	Letter* pLetter;
	pLetter = (Letter*)&letter;
	pLetter->sign = !pLetter->sign;
	printf("letter=%c\n", letter);
	int** matrix;
	matrix = new int*[3];
	for (int i = 0; i < 3; i++) {
		matrix[i] = new int[3];
	}
}