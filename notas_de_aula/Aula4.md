# Aula 4

## Relembrando

Expressões aritméticas operam sobre dois registradores e salvam o resultado em um registrador.

## Instruções Imediatas

Operam entre um registrador e uma constante e são instruções presentes na arquitetura. A constante deve ser sempre o terceiro argumento da instrução.

> Princípio de Design 3:
>
> Torne o caso comum mais rápido.

**_Observação:_** Evite utilizar a constante zero, já que há o registrador $zero disponível.

Exemplo: inicializar um registrador com zero:

`add $s0, $zero, $zero`
`move $s0, $zero # Lembrando que move é uma pseudo instrução que não existe na arquitetura.`

## Representação de inteiros em base 2

Um registrador contém um binário de 32 bits. Como tratar esse valor como um inteiro?

- A representação binária é _posicional_:

Numa base b qualquer, um número:

<img src="https://latex.codecogs.com/svg.image?{\color{Emerald}&space;xyzw=x\cdot&space;b^3&space;&plus;&space;y\cdot&space;b^2&plus;&space;&plus;&space;z&space;\cdot&space;b^1&space;&plus;&space;w\cdot&space;b^0}" title="https://latex.codecogs.com/svg.image?{\color{Emerald} xyzw=x\cdot b^3 + y\cdot b^2+ + z \cdot b^1 + w\cdot b^0}" />
