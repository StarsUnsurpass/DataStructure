#include <stdio.h>
#include "DynamicArray.h"

int main(void) {
	DynamicArray* my_array = create_array(5);

	array_append(my_array, 10);
	array_append(my_array, 20);
	array_append(my_array, 30);
	array_append(my_array, 40);
	array_append(my_array, 50);

	print_array(my_array);

	return 0;
}