#include "iostream"

struct Neighbor {
	int vertex;
	Neighbor* next;
};

Neighbor* createNeighbor(int value) {
	Neighbor* node = (Neighbor*)malloc(sizeof(Neighbor));
	node->next = NULL;
	node->vertex = value;
	return node;
}

struct Graph {
	int vertex;
	Graph* next = NULL;
	Neighbor* adjacentNodes = NULL;
};

void insertSL(Graph* graph, int value) {
	Neighbor* node = createNeighbor(value);
	if (graph->adjacentNodes == NULL)
		graph->adjacentNodes = node;
	else {
		Neighbor* temp = graph->adjacentNodes;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

Graph* createPL(int value) {
	Graph* node = (Graph*)malloc(sizeof(Graph));
	node->adjacentNodes = NULL;
	node->next = NULL;
	node->vertex = value;
	return node;
}

Graph* insertPL(Graph*& graph, int value) {
	Graph* node = createPL(value);
	/*if (graph == NULL)
		graph = node;
	else {
		Graph* temp = graph;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}*/
	node->next = graph;
	graph = node;
	return node;
}

void printGraph(Graph* graph) {
	while (graph) {
		printf("Node %d:", graph->vertex);
		Neighbor* list = graph->adjacentNodes;
		while (list) {
			printf(" -> %d", list->vertex);
			list = list->next;
		}
		graph = graph->next;
		printf("\n");
	}
}

void main() {
	Graph* graph = NULL;
	FILE* pFile = fopen("Text.txt", "r");
	if (pFile) {
		int vertex, noEdges;
		fscanf(pFile, "%d", &vertex);
		while (!feof(pFile)) {
			//insert the vertex into the priamry list
			Graph* parent = insertPL(graph, vertex);
			fscanf(pFile, "%d", &noEdges);
			for (int i = 0; i < noEdges; i++) {
				fscanf(pFile, "%d", &vertex);
				//insert each adjacent node into the secondary list
				insertSL(parent, vertex);
			}			
			fscanf(pFile, "%d", &vertex);
		}
		//read the number of edges (no. adjacent vertices)

		//insert each one into the secondary list
		fclose(pFile);
		printGraph(graph);
	}
}