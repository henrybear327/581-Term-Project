#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 5;
    int *ptr = &x;
    int **ptr_to_ptr = &ptr;

    printf("x value is %d %d %d\n", x, *ptr, **ptr_to_ptr);
    printf("x addr %p %p, ptr addr %p %p, ptr_to_ptr addr%p\n", &x, ptr, &ptr,
           ptr_to_ptr, &ptr_to_ptr);
    printf("%p\n", *ptr_to_ptr); // address of x

    **ptr_to_ptr = 10;
    printf("x value is %d %d %d\n", x, *ptr, **ptr_to_ptr);
    printf("x addr %p %p, ptr addr %p %p, ptr_to_ptr addr%p\n", &x, ptr, &ptr,
           ptr_to_ptr, &ptr_to_ptr);
    printf("%p\n", *ptr_to_ptr); // address of x

    return 0;
}