#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv)
{
	int a = 10;
	int b = 5;

	printf("Code is at %p \n", (void *)main);
	printf("Heap is at %p \n", malloc(4));
	printf("Stack is at %p \n", (void *)&a);

	int m[3];

	printf("\n");
	printf("Address of a: %p\n",    (void *)m);
	printf("Address of a[1]: %p\n", (void *)&m[1]);
	printf("Address of a[2]: %p\n", (void *)&m[2]);
	printf("Address of q: %p\n",    (void *)&a);
	printf("Address of s: %p\n",    (void *)&b);
	printf("\n");
	printf("printf is at %p \n", (void *)printf);
	printf("\n");

    if((&b - &a) > 0){
    	printf("The stack is growing up\n");
    }else{
    	printf("The stack is growing down\n");
    }

    return 0;
}
