#include "iostream"

struct Physician {
	char code[5];
	char* name;
	float salary;
};

struct BST {
	Physician* physician;
	BST* left;
	BST* right;
	int bFactor;
};

Physician* createPhysician(char* key, char* name, float salary) {
	Physician* physician = NULL;
	physician = (Physician*)malloc(sizeof(Physician));
	strcpy(physician->code, key);
	physician->name = (char*)malloc(strlen(name) + 1);
	strcpy(physician->name, name);
	physician->salary = salary;
	return physician;
}

int getBalanceFactor(BST* root);

BST* createBSTNode(Physician* info) {
	BST* node = (BST*)malloc(sizeof(BST));
	node->physician = info;
	node->left = node->right = NULL;
	node->bFactor = 0;
	return node;
}

BST* leftRotation(BST* pivot) {
	BST* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;
	desc->bFactor = getBalanceFactor(desc);
	pivot->bFactor = getBalanceFactor(pivot);
	return desc;
}

BST* rightRotation(BST* pivot) {
	BST* desc = pivot->left;
	pivot->left = desc->right;
	desc->right = pivot;
	desc->bFactor = getBalanceFactor(desc);
	pivot->bFactor = getBalanceFactor(pivot);
	return desc;
}

void rebalance(BST*& pivot) {
	BST* desc = NULL;
	pivot->bFactor = getBalanceFactor(pivot);
	if (pivot->bFactor == -2) {
		desc = pivot->left;
		if (desc->bFactor > 0)
			pivot->left = leftRotation(desc);
		pivot = rightRotation(pivot);
		//if (desc->bFactor < 0) {
		//	//simple rotation to the right
		//	pivot = rightRotation(desc);
		//}
		//else {
		//	//two simple rotations
		//	pivot->left = leftRotation(desc);
		//	pivot = rightRotation(pivot);
		//}
	}
	else
		if (pivot->bFactor == 2) {
			desc = pivot->right;
			if (desc->bFactor < 0)
				pivot->right = rightRotation(desc);
			pivot = leftRotation(pivot);
			
		}
}

void insertNode(BST*& root, BST* node) {
	if (root == NULL) {
		root = node;
	}
	else {
		if (strcmp(root->physician->code, node->physician->code) > 0)
			insertNode(root->left, node);
		else if (strcmp(root->physician->code, node->physician->code) < 0)
			insertNode(root->right, node);
		else {
			printf("Key duplicates!(insertion)\n");
		}
	}
	rebalance(root);
}

void inOrderBST(BST* root) {
	if (root) {
		inOrderBST(root->left); //L
		printf("Key: %s, BF:%d\n", root->physician->code, root->bFactor); //r
		inOrderBST(root->right); //R
	}
}

void logicalNodeDelete(BST*& root, BST*& leftS) {
	//root = MNA24 / left = DRE19
	if (leftS->right)
		logicalNodeDelete(root, leftS->right);
	else {
		//root = MNA24 / left = ERT65
		root->physician = leftS->physician;
		BST* tmp = leftS;
		leftS = leftS->left;
		free(tmp);
	}
	/*Physician* tmpPhysician = root->physician;
	root->physician = left->physician;*/
}

Physician* deleteNode(BST*& root, char* key) {
	Physician* node = NULL;
	if (root) {
		if (strcmp(root->physician->code, key) > 0)
			deleteNode(root->left, key);
		else if (strcmp(root->physician->code, key) < 0)
			deleteNode(root->right, key);
		else {
			node = root->physician;
			//3 cases for deleting an element
			//1. the root is a leaf
			if (root->left == NULL && root->right == NULL) {
				free(root->physician->name);
				free(root->physician);
				free(root);
				root = NULL;
			}
			else if (root->left == NULL) { //implicit && root->right != NULL
				BST* tmp = root;
				root = root->right;
				free(tmp->physician->name);
				free(tmp->physician);
				free(tmp);
			}
			else if (root->right == NULL) { //implicit && root->left != NULL
				BST* tmp = root;
				root = root->left;
				free(tmp->physician->name);
				free(tmp->physician);
				free(tmp);
			}
			else { //both descendants exist
				logicalNodeDelete(root, root->left);
			}
		}
	}
	return node;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int getHeight(BST* root) {
	if (root == NULL) {
		return 0;
	}
	else
		return 1 + max(getHeight(root->left), getHeight(root->right));
}

void PrintLeaves(BST* root) {
	if (root) {
		if (getHeight(root) == 1) {
			printf("Code:%s\n", root->physician->code);
		}
		PrintLeaves(root->left);
		PrintLeaves(root->right);
	}
}

int CountLeaves(BST* root) {
	int count = 0;
	if (root) {
		if (root->left == root->right)
			count++;
		count += CountLeaves(root->right) + CountLeaves(root->left);
	}
	return count;
}

void PrintTreeStructure(BST* root, int level) {
	if (root) {
		//root processing
		for (int i = 0; i < level; i++) {
			printf("\t");
		}
		printf("%s\n", root->physician->code);
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

void PrintLevel(BST* root, int level) {
	if (root == NULL)
		return;
	if (level == 1) {
		printf("%s\n", root->physician->code);
	}
	if (level > 1) {
		PrintLevel(root->left, level - 1);
		PrintLevel(root->right, level - 1);
	}
}

void PrintTreeLevels(BST* root) {
	int h = getHeight(root);
	for (int i = 1; i <= h; i++) {
		PrintLevel(root, i);
	}
}

int getBalanceFactor(BST* root) {
	int result = 0;
	if (root) {
		result = getHeight(root->right) - getHeight(root->left);
	}
	return result;
}

void main() {
	BST* root = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile) {
		char key[6], name[100];
		float salary;
		fscanf(pFile, "%s", key);
		while (!feof(pFile)) {
			fscanf(pFile, "%s", name);
			fscanf(pFile, "%f", &salary);

			Physician* physician = createPhysician(key, name, salary);
			BST* node = createBSTNode(physician);
			insertNode(root, node);

			fscanf(pFile, "%s", key);
		}
		inOrderBST(root);
		
		/*printf("----------GET HEIGHT----------\n");
		printf("Heigth:%d\n", getHeight(root));

		Physician* physician = deleteNode(root, "MNA24");
		printf("Deleted element:%s\n", physician->code);
		printf("----------AFTER DELETING A NODE----------\n");
		inOrderBST(root);*/

		printf("----------GET HEIGHT----------\n");
		printf("Heigth:%d\n", getHeight(root));

		printf("----------PRINT LEAVES----------\n");
		PrintLeaves(root);

		printf("----------PRINT NO LEAVES----------\n");
		printf("No leaves:%d\n", CountLeaves(root));

		printf("----------PRINT TREE STRUCTURE----------\n");
		PrintTreeStructure(root, 0);

		printf("----------PRINT TREE LEVELS----------\n");
		PrintTreeLevels(root);
		
		printf("----------REBALANCING----------\n");
		inOrderBST(root);

		fclose(pFile);
	}
}