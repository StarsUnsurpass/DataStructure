#include <stdio.h>
#include "DynamicArray.h"

// 辅助输出函数
void print_header(const char* title) {
	printf("\n========================================\n");
	printf("	%s", title);
	printf("\n========================================\n");
}

int main(void) {
	// 1.初始化(initial)
	printf("1.初始化数组");
	DynamicArray* my_array = create_array(5);

	array_append(my_array, 10);
	array_append(my_array, 20);
	array_append(my_array, 30);
	array_append(my_array, 40);
	array_append(my_array, 50);

	printf("初始数组创建完毕：\n");
	print_array(my_array);
	printf("注意：当前size和capacity相等，下一次添加将触发‘扩容’。\n");

	array_append(my_array, 60);
	printf("添加60之后触发自动扩容。\n");
	print_array(my_array);


	// 2.读取（read）
	print_header("2.读取操作（O(1)）");
	size_t read_index = 2;
	Data* value_ptr = array_read(my_array, read_index);
	if (value_ptr) {
		printf("读取索引 %zu 的值……\n", read_index);
		printf("成功！值为：%d\n", *value_ptr);
		printf("C语言通过`base_address + index * sizeof(int)`计算出内存地址");
	}


	// 3.更新（update）
	print_header("3.更新操作（O(1)）");
	size_t update_index = 3;
	Data new_value = 99;
	printf("将索引 %zu 的值从 %d 更新为 %d……\n", update_index,
		*array_read(my_array, update_index), new_value);
	array_update(my_array, update_index, new_value);
	print_array(my_array);
	printf("更新同样是O(1)操作，通过地址计算直接定位并覆盖。\n");


	// 4.插入（insert）
	print_header("4.插入操作（O(n)）");
	size_t insert_index = 1;
	Data insert_value = 999;
	printf("在索引 %zu 处插入新值 %d……\n", insert_index, insert_value);
	printf("操作前：");
	print_array(my_array);
	array_insert(my_array, insert_index, insert_value);
	printf("操作后：");
	print_array(my_array);
	printf("为了插入 %d，从索引 %zu 开始的所有元素都必须向后移动一个位置。", 
		insert_value, insert_index);


	// 5.删除（delete）
	print_header("5.删除操作（O(n)）");
	size_t delete_index = 4;
	printf("删除索引 %zu 的元素（%d）……\n", delete_index,
		*array_read(my_array, delete_index));
	printf("操作前：");
	print_array(my_array);
	array_delete(my_array, delete_index);
	printf("操作后：");
	print_array(my_array);
	printf("删除元素时，其后面的所有元素都必须向前移动填补空缺。");


	// 6.销毁
	destroy_array(my_array);
	printf("\n已释放所有内存。\n");
	

	return 0;
}