#include "iostream"

struct SplayTree { //self balancing binary search tree
	int info;
	SplayTree* left;
	SplayTree* right;
	int balancingFactor;
};

int getBalanceFactor(SplayTree* root);

SplayTree* createSplayTreeNode(int info) {
	SplayTree* node = (SplayTree*)malloc(sizeof(SplayTree));
	node->info = info;
	node->left = node->right = NULL;
	node->balancingFactor = 0;
	return node;
}

SplayTree* leftRotation(SplayTree* pivot) {
	SplayTree* descendant = pivot->right;
	pivot->right = descendant->left;
	descendant->left = pivot;
	descendant->balancingFactor = getBalanceFactor(descendant);
	pivot->balancingFactor = getBalanceFactor(pivot);
	return descendant;
}

SplayTree* rightRotation(SplayTree* pivot) {
	SplayTree* descendant = pivot->left;
	pivot->left = descendant->right;
	descendant->right = pivot;
	descendant->balancingFactor = getBalanceFactor(descendant);
	pivot->balancingFactor = getBalanceFactor(pivot);
	return descendant;
}

void rebalance(SplayTree*& pivot) {
	SplayTree* descendant = NULL;
	pivot->balancingFactor = getBalanceFactor(pivot);
	if (pivot->balancingFactor == -2) {
		descendant = pivot->left;
		if (descendant->balancingFactor > 0)
			pivot->left = leftRotation(descendant);
		pivot = rightRotation(pivot);
	}
	else if (pivot->balancingFactor == 2) {
			descendant = pivot->right;
			if (descendant->balancingFactor < 0)
				pivot->right = rightRotation(descendant);
			pivot = leftRotation(pivot);
	}
}

void insertNode(SplayTree*& root, SplayTree* node) {
	if (root == NULL) {
		root = node;
	}
	else {
		if (root->info > node->info)
			insertNode(root->left, node);
		else if (root->info < node->info)
			insertNode(root->right, node);
		else {
			printf("Duplicates at insertion!\n");
		}
	}
	rebalance(root);
}

void inOrderSplayTree(SplayTree* root) {
	if (root) {
		inOrderSplayTree(root->left);
		printf("Key: %d, Balance Factor:%d\n", root->info, root->balancingFactor);
		inOrderSplayTree(root->right);
	}
}

void logicalNodeDelete(SplayTree*& root, SplayTree*& leftS) {
	if (leftS->right)
		logicalNodeDelete(root, leftS->right);
	else {		
		root->info = leftS->info;
		SplayTree* temp = leftS;
		leftS = leftS->left;
		free(temp);
	}
}

int deleteNode(SplayTree*& root, int key) {
	int node = key;
	if (root) {
		if (root->info > key)
			deleteNode(root->left, key);
		else if (root->info < key)
			deleteNode(root->right, key);
		else {
			node = root->info;
			if (root->left == NULL && root->right == NULL) {
				free(root);
				root = NULL;
			}
			else if (root->left == NULL) {
				SplayTree* temp = root;
				root = root->right;
				free(temp);
			}
			else if (root->right == NULL) {
				SplayTree* temp = root;
				root = root->left;
				free(temp);
			}
			else {
				logicalNodeDelete(root, root->left);
			}
		}
	}
	return node;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int getHeight(SplayTree* root) {
	if (root == NULL) {
		return 0;
	}
	else
		return 1 + max(getHeight(root->left), getHeight(root->right));
}

void PrintLeaves(SplayTree* root) {
	if (root) {
		if (getHeight(root) == 1) {
			printf("Info:%d\n", root->info);
		}
		PrintLeaves(root->left);
		PrintLeaves(root->right);
	}
}

int CountLeaves(SplayTree* root) {
	int count = 0;
	if (root) {
		if (root->left == root->right)
			count++;
		count += CountLeaves(root->right) + CountLeaves(root->left);
	}
	return count;
}

void PrintTreeStructure(SplayTree* root, int level) {
	if (root) {
		for (int i = 0; i < level; i++) {
			printf("\t");
		}
		printf("%d\n", root->info);
		level++;
		PrintTreeStructure(root->left, level);
		PrintTreeStructure(root->right, level);
	}
	else {
		for (int i = 0; i < level; i++) {
			printf("\t");
		}
		printf("NULL\n");
	}
}

void PrintLevel(SplayTree* root, int level) {
	if (root == NULL)
		return;
	if (level == 1) {
		printf("%d\n", root->info);
	}
	if (level > 1) {
		PrintLevel(root->left, level - 1);
		PrintLevel(root->right, level - 1);
	}
}

int getBalanceFactor(SplayTree* root) {
	int result = 0;
	if (root) {
		result = getHeight(root->right) - getHeight(root->left);
	}
	return result;
}

void main() {
	SplayTree* root = NULL;
	for (int i = 1; i <= 10; i++) {
		SplayTree* node = createSplayTreeNode(i);
		insertNode(root, node);
	}
	inOrderSplayTree(root);

	printf("----------TREE HEIGHT----------\n");
	printf("Heigth:%d\n", getHeight(root));

	printf("----------NODE DELETION----------\n");
	int del = 0;
	printf("Choose the node to be deleted: ");
	scanf("%d", &del);
	while (del < 1 || del > 10) {
		printf("Choose the node (BETWEEN 1 TO 10) to be deleted: ");
		scanf("%d", &del);
	}		
	int deletedInfo = deleteNode(root, del);
	inOrderSplayTree(root);	
	printf("Deleted element:%d\n", deletedInfo);

	printf("----------LEAVES----------\n");
	printf("No leaves:%d\n", CountLeaves(root));
	PrintLeaves(root);

	printf("----------TREE STRUCTURE----------\n");
	PrintTreeStructure(root, 0);
}