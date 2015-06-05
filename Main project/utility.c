#include <stdio.h>
void clear_screen()
{
    printf("%c[2J", 27);
}