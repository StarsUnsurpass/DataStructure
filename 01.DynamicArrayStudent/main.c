#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicArray.h"

// 定义回调函数
// 一个打印student的函数
// 此函数签名必须和函数指针的定义完全匹配
void print_student(const void* data) {
	// 接收到的data是一个void*指针，需要将其转换为真正的类型
	const Student* s_ptr = (const Student*)data;
	printf("Student: {id: %d, name: \"%s\"}", s_ptr->id, s_ptr->name);
}

int main(void) {
	printf("--- 测试 Student 动态数组 ---\n");
	DynamicArray* student_list = create_array(2);

	Student s1 = { 101, "Tom" };
	Student s2 = { 102, "Jack" };
	array_append(student_list, s1);
	array_append(student_list, s2);

	// 调用通用的 print_array，并把“如何打印学生”的函数传给它
	printf("打印学生名单：\n");
	print_array(student_list, &print_student);

	destroy_array(student_list);

	printf("\n\n--- 测试 Integer 动态数组 ---\n");

	return 0;
}