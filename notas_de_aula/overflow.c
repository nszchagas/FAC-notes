#include <stdio.h>

int main()
{

    unsigned int a = 2147483648;
    unsigned int b = 2147483648;
    unsigned int c;
    c = a + b;
    printf("%d\n", c); // Imprime 0

    return 0;
}