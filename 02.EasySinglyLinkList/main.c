#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// 定义节点结构
// 1.data int
// 2.指向下一个节点的指针
typedef struct Node {
	int data;
	struct Node* next;
} Node;

Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (newNode == NULL) {
		printf("分配失败!\n");
		return NULL;
	}

	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

void list_append(Node** headRef, int data) {
	Node* newNode = createNode(data);
	if (newNode == NULL) return;

	if (*headRef == NULL) {
		*headRef = newNode;
		return;
	}

	Node* last = *headRef;
	while (last->next != NULL) {
		last = last->next;
	}

	last->next = newNode;
}

void prependNode(Node** headRef, int data) {
	Node* newNode = createNode(data);

	newNode->next = *headRef;
	*headRef = newNode;
}

void printList(Node* head) {
	Node* current = head;

	printf("当前列表：");
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}

	printf("NULL\n");
}

Node* findNode(Node* head, int data) {
	Node* current = head;

	while (current != NULL) {
		if (current->data == data) {
			return current;
		}

		current = current->next;
	}

	return NULL;
}

void updateNode(Node* head, int oldData, int newData) {
	Node* nodeToUpdate = findNode(head, oldData);
	if (nodeToUpdate != NULL) {
		nodeToUpdate->data = newData;
		printf("数据 %d 已经成功更新至 %d .\n", oldData, newData);
	}
	else {
		printf("未找到！\n");
	}
}

void deleteNode(Node** headRef, int data) {
	Node* tmp = *headRef;
	Node* prev = NULL;

	// 如果删除的是头节点
	if (tmp != NULL && tmp->data == data) {
		*headRef = tmp->next;
		free(tmp);
		return;
	}

	// 如果在尾部或中部
	while (tmp != NULL && tmp->data != data) {
		prev = tmp;
		tmp = tmp->next;
	}

	if (tmp == NULL) {
		return;
	}

	prev->next = tmp->next;
	free(tmp);
}

void list_free(Node** headRef) {
	if (headRef == NULL) return;
	Node* current = *headRef;

	Node* nextNode;

	while (current != NULL) {
		nextNode = current->next;
		free(current);
		current = nextNode;
	}

	*headRef = NULL;
}

int main(void) {
	Node* head = NULL;

	list_append(&head, 10);
	list_append(&head, 20);
	list_append(&head, 30);
	printList(head);

	list_append(&head, 40);
	printList(head);

	prependNode(&head, 0);
	printList(head);

	deleteNode(&head, 30);
	printList(head);

	list_free(&head);
	printList(head);

	return 0;
}