#include "iostream"

struct Buyer {
	char* buyer_name;
	float available_budget;
};

struct ListOfBuyers {
	Buyer* buyer;
	ListOfBuyers* pNext;
};

struct Apartament {
	int apt_code;
	int no_rooms;
	float surface_size;
	float price_per_sqm;
	ListOfBuyers* buyers;
};

struct Block {
	Apartament** apartaments;
	int noApts;
};

Block* createBlock(Apartament** apts, int nr) {
	Block* block = NULL;
	block = (Block*)malloc(sizeof(Block));
	block->apartaments = (Apartament**)malloc(nr * sizeof(Apartament));
	block->noApts = nr;
	return block;
}

Buyer* createBuyer(char* name, float budget) {
	Buyer* buyer = NULL;
	buyer = (Buyer*)malloc(sizeof(Buyer));
	buyer->buyer_name = (char*)malloc(strlen(name) + 1);
	strcpy(buyer->buyer_name, name);
	buyer->available_budget = budget;
	return buyer;
}

Apartament* buildApt(int code, int rooms, float size, float price_m2, ListOfBuyers* buyers) {
	Apartament* apt = NULL;
	apt = (Apartament*)malloc(sizeof(Apartament));
	apt->apt_code = code;
	apt->no_rooms = rooms;
	apt->surface_size = size;
	apt->price_per_sqm = price_m2;
	apt->buyers = (ListOfBuyers*)malloc(sizeof(buyers));
	apt->buyers = buyers;
	return apt;
}

void addApt(Block* block, Apartament* apt) {
	/*Apartament** temp = (Apartament**)malloc(sizeof(block->apartaments));
	temp = block->apartaments;*/
	//block->apartaments = (Apartament**)malloc(sizeof(block->apartaments) + sizeof(Apartament));
	/*for (int i = 0; i < sizeof(block->apartaments); i++) {
		block->apartaments[i] = temp[i];
	}*/
	//block->apartaments[block->noApts] = (Apartament*)malloc(sizeof(Apartament));
	block->apartaments[block->noApts]->apt_code = apt->apt_code;
	block->apartaments[block->noApts]->no_rooms = apt->no_rooms;
	block->apartaments[block->noApts]->surface_size = apt->surface_size;
	block->apartaments[block->noApts]->price_per_sqm = apt->price_per_sqm;
	block->apartaments[block->noApts]->buyers = (ListOfBuyers*)malloc(sizeof(block->apartaments[block->noApts]->buyers));
	block->apartaments[block->noApts]->buyers = apt->buyers;
	block->noApts++;
	//free(temp);
}

ListOfBuyers* createNode(Buyer* buyer)
{
	ListOfBuyers* node = (ListOfBuyers*)malloc(sizeof(ListOfBuyers));
	node->buyer = buyer;
	node->pNext = NULL;
	return node;
}

void addBuyer(Block* block, int code, Buyer* buyer) {
	ListOfBuyers* list = createNode(buyer);
	for (int i = 0; i < sizeof(block->apartaments); i++) {
		if (block->apartaments[i]->apt_code == code) {
			list->pNext = block->apartaments[i]->buyers;
			block->apartaments[i]->buyers = list;
		}
	}
}

void main() {
	Apartament** apts = (Apartament**)malloc(5*sizeof(Apartament));
	Block* block = createBlock(apts, 0);
	Apartament* apt1 = buildApt(1, 2, 45.5, 900, NULL);
	Apartament* apt2 = buildApt(2, 3, 65.7, 1000, NULL);
	Apartament* apt3 = buildApt(3, 4, 98.2, 1200, NULL);
	Apartament* apt4 = buildApt(4, 3, 68.4, 1000, NULL);
	Apartament* apt5 = buildApt(5, 1, 36.3, 800, NULL);
	addApt(block, apt1);
	addApt(block, apt2);
	addApt(block, apt3);
	addApt(block, apt4);
	addApt(block, apt5);
	Buyer* buy1 = createBuyer("Ion Popescu", 41200);
	//addBuyer(block, 1, buy1);
	printf("%d", block->apartaments[1]->apt_code);
}