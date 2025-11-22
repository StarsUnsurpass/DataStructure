#pragma once
#include <stddef.h>

typedef struct {
	int id;
	char name[50];
	int age;
} Student;

typedef Student Data;

typedef struct{
	Data data;
	struct Node* next;
} Node;

Node* createNode(Data data);

void appendNode(Node** headRef, Data data);

void perpendNode(Node** headRef, Data data);

void printList(Node* head, void(*print_func)(const void* data));

// 泛型
// 第三个参数意味着传递过来的是一个函数的地址
// 这个函数必须满足：
// 1.返回int类型；
// 2.接收两个const void*类型的参数；
// 可变参数：printf(%d)；
// 格式化输出
// 调用契约，findNode调用：
// 1.正在遍历的是当前节点的数据
// 2.一开始传递给它的目标数据
// context pointer上下文指针
Node* findNode(
	Node* headRef, 
	const void* target_data, 
	int(*compare_func)(const void* a, const void* b, void* context), 
	void* context);

void deleteNode(
	Node** headRef, 
	const void* target_data,
	int(*compare_func)(const void* a, const void* b, void* context),
	void* context);

void updateNode(
	Node* headRef,
	const void* target_data,
	Data newData,
	int(*compare_func)(const void* a, const void* b, void* context),
	void* context);

void freeList(Node** headRef, void(*free_data_func)(void* data));