# Aula 2 - Aritmética Computacional

## Multiplicação

|||||||||||
|--|--|--|--|--|--|--|--|--|--|
|||||1 |0 |0 |0 | Multiplicando M|
||||x| 1| 0| 1| 1| Multiplicador Q|
|||||1 |0 |0 |0 ||sll $Q_0\cdot M, 1$|
||||1|0 |0 |0 | 0||sll $Q_1\cdot M, 1$|
|||0 |0 |0 |0 | ||sll $Q_2\cdot M, 1$|
||1 |0 |0 |0 | |||sll $Q_3\cdot M, 1$|
||1 |0 |1 |1 |0 |0|0|Produto P|

$ 1000_2 \times 1011_2 = 1011000_2 $

Observe que o produto possui 7 bits, que corresponde à 4 bits do multiplicando + 3 shifts (4 bits do multiplicador - 1). Portanto, precisaremos de:

- Produto: registrador de 64 bits
- Multiplicando: registrador de 64 bits
- Multiplicador: registrador de 32 bits

### Algoritmo

Passo 1: Inicializar P=0 e contador=1.
Passo 2: $P=Q_0\times M$ (Essa multiplicação será feita pela condicional, se o LSB for 1 ou 0).
Passo 3: Desloque M à esquerda.
Passo 4: Desloque Q à direita, para que o bit a ser multiplicado seja o LSB.
Passo 5: Se contador=32, pare. Senão, faça contador++ e volte ao passo 2.
