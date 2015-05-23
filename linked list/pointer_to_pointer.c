#include <stdio.h>
#include <stdlib.h>
//clang-format-3.5 -i -style=LLVM  pointer_to_pointer.c && astyle --style=linux pointer_to_pointer.c  && clang-3.5 -Wall -Wextra pointer_to_pointer.c -o pointer && ./pointer 
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