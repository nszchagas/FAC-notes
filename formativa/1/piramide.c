#include <stdio.h>

void print_n(int n, char c)
{
    for (int cont = 0; cont < n; cont++)
    {
        printf("%c", c);
    }
}

int main()
{

    int num_linhas;
    scanf("%d", &num_linhas);

    for (int cont = 0; cont < num_linhas; cont++)
    {
        print_n(num_linhas - cont, ' ');
        print_n(2 * cont + 1, '*');
        printf("\n");
    }

    return 0;
}
