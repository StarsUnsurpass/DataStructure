#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

// 1.打印回调函数
void print_student(const void* data) {
	const Student* s = (const Student*)data;
	printf("{ID: %d, 姓名: %s, 年龄: %d}", s->id, s->name, s->age);
}

// 2.定义一个简单的比较回调函数（只按ID比较）
int compare_by_id(const void* a, const void* b, void* context) {
	// 这个函数不需要额外的上下文，所以将context参数忽略
	
	const Student* s_a = (const Student*)a;
	const Student* target_s = (const Student*)b;
	return s_a->id == target_s->id ? 0 : 1;
}

// 3.定义一个复杂的比较回调函数（需要使用上下文）
// 上下文结构体，用于打包额外参数
typedef struct {
	int min_age_required;
} SearchContext;

int compare_by_id_and_min_age(const void* a, const void* b, void* context) {
	const Student* s_a = (const Student*)a;
	const Student* target_s = (const Student*)b;
	SearchContext* ctx = (SearchContext*)context;

	// 复杂的比较逻辑
	if (s_a->id == target_s->id && s_a->age >= ctx->min_age_required) {
		return 0;
	}

	return 1;
}

// 4.定义释放Data内部资源的回调（本例为空，仅作演示）
void free_student_data(void* data) {
	// 如果 Student 结构体内的 name 是 chat* 类型且由 malloc 分配
	// 此处就需要 free(((Student*)data)->name);
}

int main(void) {
	Node* head = NULL;

	// 初始化数据
	printf("----1.初始化链表----\n");
	Student students[] = {
		{101, "Tom", 20},
		{102, "Jack", 21},
		{103, "Jerry", 23},
		{104, "Stark", 19}
	};
	for (int i = 0; i < 4; i++) {
		appendNode(&head, students[i]);
	}
	printList(head, print_student);

	// 简单查找与删除
	printf("\n----2.删除学号为103的学生----\n");
	Student target_103 = { 103, "", 0 };
	deleteNode(&head, &target_103, compare_by_id, NULL);
	printList(head, print_student);

	// 复杂查找与更新
	printf("\n----3.查找学号为104且年龄不小于20岁的学生----\n");
	SearchContext ctx_fail = { 20 };
	Student target_104 = { 104, "", 0 };
	Node* found = findNode(head, &target_104, compare_by_id_and_min_age, &ctx_fail);
	if (found) {
		printf("成功找到\n");
	}
	else {
		printf("未找到\n");
	}

	printf("\n----4.查找学号为101且年龄不小于20岁的学生，并更新----\n");
	SearchContext ctx_success = { 20 };
	Student target_101 = { 101, "", 0 };
	Student new_101_data = { 101, "Tony", 23 };
	updateNode(head, &target_101, new_101_data, compare_by_id_and_min_age, &ctx_success);
	printList(head, print_student);

	// 清理
	printf("\n----5.释放所有内存----\n");
	freeList(&head, free_student_data);
	printf("链表已清空\n");
	printList(head, print_student);

	return 0;
}