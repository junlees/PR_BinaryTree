#include <stdio.h>

typedef struct _element{
	int key;
	/* data fields */
}element;


typedef struct _node {
	element data;
	struct node *left_child, *right_child;
}node;

typedef node* treePointer;

element* search(treePointer nodePtr, int k);
element* iterSearch(treePointer nodePtr, int k);
treePointer createNode(int key);
treePointer insert(treePointer nodePtr, int key);
treePointer deleteNode(treePointer currentNode, int key);
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);
treePointer findMinimum(treePointer currentNode);

int main() {
	treePointer nodePtr = NULL;
	nodePtr = insert(nodePtr, 3);
	nodePtr = insert(nodePtr, 2);
	nodePtr = insert(nodePtr, 4);
	nodePtr = insert(nodePtr, 5);
	nodePtr = insert(nodePtr, 1);
	printf("inorder : ");
	inorder(nodePtr);
	printf("\n");

	insert(nodePtr, 8);

	printf("inorder : ");
	inorder(nodePtr);
	printf("\n");
	
	deleteNode(nodePtr, 4);

	printf("inorder : ");
	inorder(nodePtr);
	printf("\n");

	printf("%d", search(nodePtr, 3)->key);
	printf("\n");

	if(iterSearch(nodePtr, 10) != NULL)
		printf("%d", iterSearch(nodePtr, 3)->key);
	else
		printf("NULL");

	printf("\n");

	if(iterSearch(nodePtr, 3) != NULL)
		printf("%d", iterSearch(nodePtr, 10)->key);
	else
		printf("NULL");
		
	printf("\n");
	return 0;
}

element* search(treePointer nodePtr, int k) {
	/* return a pointer to the node that contains key.
	If there is no such node, return NULL */
	//재귀

	if (!nodePtr) return NULL;
	if (k == nodePtr->data.key)
		return &(nodePtr->data);
	if (k < nodePtr->data.key)
		return search(nodePtr->left_child, k);
	return search(nodePtr->right_child, k);
}

element* iterSearch(treePointer nodePtr, int k) {
	/* return a pointer to the element whose key is k,
	if there’s no such element, return NULL, */
	//루프

	while (nodePtr) {
		if (k == nodePtr->data.key)
			return &(nodePtr->data);
		if (k < nodePtr->data.key)
			nodePtr = nodePtr->left_child;
		else nodePtr = nodePtr->right_child;
	}
	return NULL;
}

treePointer createNode(int key) {

	//treePointer newNode = (node*)malloc(sizeof(node));
	treePointer newNode = (treePointer)malloc(sizeof(node));

	newNode->data.key = key;
	newNode->left_child = NULL;
	newNode->right_child = NULL;

	return newNode;
}

treePointer insert(treePointer nodePtr, int key) {
	if (nodePtr == NULL)
		return createNode(key);

	if (key < nodePtr->data.key)
		nodePtr->left_child = insert(nodePtr->left_child, key);
	else if (key > nodePtr->data.key)
		nodePtr->right_child = insert(nodePtr->right_child, key);

	return nodePtr;
}

treePointer deleteNode(treePointer currentNode, int key) {
		if (currentNode == NULL) {
		return NULL;
	}
	else if (key < currentNode->data.key) {
		currentNode->left_child = deleteNode(currentNode->left_child, key);
	}
	else if (key > currentNode->data.key) {
		currentNode->right_child = deleteNode(currentNode->right_child, key);
	}
	else {
		if (currentNode->left_child == NULL && currentNode->right_child == NULL)
			currentNode = NULL;
		else if (currentNode->left_child == NULL)
			currentNode = currentNode->right_child;
		else if (currentNode->right_child == NULL)
			currentNode = currentNode->left_child;
		else {
			treePointer tempNode = findMinimum(currentNode->right_child);
			currentNode->data.key = tempNode->data.key;
			currentNode->right_child = deleteNode(currentNode->right_child, tempNode->data.key);
		}
	}
	return currentNode;
}

treePointer findMinimum(treePointer currentNode) {

	if (currentNode->left_child == NULL)
		return currentNode;

	return findMinimum(currentNode->left_child);
}


void inorder(treePointer ptr)
/* inorder tree traversal */
{
	if (ptr) {
		inorder(ptr->left_child);
		printf("%d ", ptr->data.key);
		inorder(ptr->right_child);
	}
}

void preorder(treePointer ptr)
/* preorder tree traversal */
{
	if (ptr) {
		printf("%d", ptr->data.key);
		preorder(ptr->left_child);
		preorder(ptr->right_child);
	}
}

void postorder(treePointer ptr)
/* postorder tree traversal */
{
	if (ptr) {
		postorder(ptr->left_child);
		postorder(ptr->right_child);
		printf("%d", ptr->data.key);
	}
}
