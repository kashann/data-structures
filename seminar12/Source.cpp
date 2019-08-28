#include "iostream"

struct Graph {
	int** nodes = NULL;
	int size = 0;
};

void BF(Graph graph, int startVertex) {
	int* queue = (int*)malloc(sizeof(int)*graph.size);
	int* visited = (int*)malloc(sizeof(int)*graph.size);
	memset(visited, 0, sizeof(int)*graph.size);
	int pHead = 0, pTail = -1;
	visited[startVertex] = 1;
	queue[++pTail] = startVertex;
	while (pHead <= pTail) {
		for (int i = 0; i < graph.size; i++) {
			if (graph.nodes[queue[pHead]][i] == 1 && visited[i] == 0) {
				queue[++pTail] = i;
				visited[i] = 1;
			}
		}
		printf("%d ", ++queue[pHead++]);
	}
}

void main() {
	Graph graph;
	FILE* pFile = fopen("Text.txt", "r");
	if (pFile) {
		int noVertices, src, dest;
		fscanf(pFile, "%d", &noVertices);
		graph.size = noVertices;
		//allocate memory and initialize the matrix
		graph.nodes = (int**)malloc(sizeof(int*) * noVertices);
		for (int i = 0; i < noVertices; i++) {
			graph.nodes[i] = (int*)malloc(sizeof(int)*noVertices);
			memset(graph.nodes[i], 0, sizeof(int)*noVertices);
		}
		while (!feof(pFile)) {
			fscanf(pFile, "%d", &src);
			fscanf(pFile, "%d", &dest);
			graph.nodes[src-1][dest-1] = graph.nodes[dest-1][src-1] = 1;
		}
		for (int i = 0; i < noVertices; i++) {
			printf("Traversal starting from %d: ", i + 1);
			BF(graph, i); //breadth first
			printf("\n");
		}

		fclose(pFile);
	}
}