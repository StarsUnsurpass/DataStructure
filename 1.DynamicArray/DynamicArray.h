#pragma once
#include <stddef.h>

// 这里简单用int，假设只存储int类型数据
typedef int Data;

// 定义动态数组结构体
typedef struct {
	Data* data;

	size_t size;
	size_t capacity;
} DynamicArray;

// 公共接口函数声明

// 内部辅助函数，当容量不足时，进行扩容
static int resize_array(DynamicArray* arr, size_t new_capacity);

// 创建并初始化一个动态数组
DynamicArray* create_array(size_t initial_capacity);

// 销毁数组，释放内存
void destroy_array(DynamicArray* arr);

// 在数组末尾追加元素
void array_append(DynamicArray* arr, Data value);

// 读取指定索引元素
// 返回一个指针，以便能够检查是否成功，如果索引无效，返回NULL
Data* array_read(DynamicArray* arr, size_t index);

// 更新指定索引元素
// 返回0表示成功，返回-1表示失败
int array_update(DynamicArray* arr, size_t index, Data value);

// 插入元素
int array_insert(DynamicArray* arr, size_t index, Data value);

// 删除指定索引的元素
// 返回0表示成功，返回-1表示失败
int array_delete(DynamicArray* arr, size_t index);

// 打印数组
void print_array(DynamicArray* arr);