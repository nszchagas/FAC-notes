#include <stdio.h>

int main()
{
    int dividendo, divisor;
    int quociente = 0, resto;
    scanf("%d", &dividendo);
    scanf("%d", &divisor);

    while (dividendo - divisor >= 0)
    {
        quociente++;
        dividendo -= divisor;
    }
    if (dividendo < 0)
        resto = dividendo + divisor;
    else
        resto = dividendo;

    printf("Quociente: %d | resto: %d\n", quociente, resto);
    return 0;
}
