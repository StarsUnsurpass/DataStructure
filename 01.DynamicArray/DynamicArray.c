#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"

#define INTTIAL_CAPACITY 10

static int resize_array(DynamicArray* arr, size_t new_capacity) {
	Data* new_data = realloc(arr->data, new_capacity * sizeof(Data));

	if (!new_data) {
		return -1;
	}

	arr->data = new_data;
	arr->capacity = new_capacity;

	return 0;
}

DynamicArray* create_array(size_t initial_capacity) {
	if (initial_capacity == 0) {
		initial_capacity = INTTIAL_CAPACITY;
	}
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));

	if (!arr) {
		return NULL;
	}

	arr->data = (Data*)malloc(sizeof(Data*) * initial_capacity);

	if (!arr->data) {
		free(arr);
		return NULL;
	}

	arr->size = 0;
	arr->capacity = initial_capacity;

	return arr;
}

void destroy_array(DynamicArray* arr) {
	if (arr) {
		free(arr->data);
		free(arr);
	}
}

void array_append(DynamicArray* arr, Data value) {
	// 检查是否要扩容
	if (arr->size >= arr->capacity) {
		size_t new_capacity = arr->capacity * 2;
		resize_array(arr, new_capacity);
	}

	arr->data[arr->size] = value;
	arr->size++;
}

Data* array_read(DynamicArray* arr, size_t index) {
	if (index >= arr->size) {
		return NULL;
	}

	return &(arr->data[index]);
}

int array_update(DynamicArray* arr, size_t index, Data value) {
	if (index >= arr->size) {
		return -1;
	}

	arr->data[index] = value;
	return 0;
}

int array_insert(DynamicArray* arr, size_t index, Data value) {
	if (index > arr->size) { // 索引越界，允许在末尾插入
		return -1;
	}

	if (arr->size >= arr->capacity) {
		// 函数合约 The Function Contract
		if (resize_array(arr, arr->capacity * 2) != 0) {
			return -1;
		}
	}

	for (size_t i = arr->size; i > index; --i) {
		arr->data[i] = arr->data[i - 1];
	}

	arr->data[index] = value;

	arr->size++;

	return 0;
}

int array_delete(DynamicArray* arr, size_t index) {
	if (index >= arr->size) {
		return -1;
	}

	for (size_t i = index; i < arr->size - 1; i++) {
		arr->data[i] = arr->data[i + 1];
	}

	arr->size--;

	if (arr->size > 0 && arr->size < arr->capacity / 4 && arr->capacity > INTTIAL_CAPACITY) {
		size_t new_capacity = arr->capacity / 2;

		// 确保缩容后的容量仍然可以装下所有元素，并且不会小于初始容量
		if (new_capacity < arr->size) {
			new_capacity = arr->size;
		}

		if (new_capacity < INTTIAL_CAPACITY) {
			new_capacity = INTTIAL_CAPACITY;
		}

		printf("\n---> [缩容警告！] Size (%zu) <= Capacity / 4 (%zu). 准备缩容至 %zu.\n",
			arr->size, arr->capacity / 4, new_capacity);

		resize_array(arr, new_capacity);

		return 0;
	}
}

void print_array(DynamicArray* arr) {
	printf("Array (Size: %zu, Capacity: %zu): [ ", arr->size, arr->capacity);
	for (size_t i = 0; i < arr->size; i++) {
		printf("%d ", arr->data[i]);
	}
	printf("]\n");
}