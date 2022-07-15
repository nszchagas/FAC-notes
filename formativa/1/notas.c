#include <stdio.h>

int main()
{
    char conceitos[5] = {'E', 'D', 'C', 'B', 'A'};
    int fronteiras[4] = {1, 36, 61, 86};
    int nota, pos = 0;
    scanf("%d", &nota);
    while (nota >= fronteiras[pos] && pos++ < 4)
        ;

    printf("%c", conceitos[pos]);
    return 0;
}