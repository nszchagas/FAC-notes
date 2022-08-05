# Aritmética Computacional - 01/08/2022

## Algoritmo de Divisão

Uma divisão é formada por dividendo (K), divisor (D), quociente (Q) e resto (R). Para implementar o algoritmo de divisão, a seguinte ideia será utilizada:

- Subtrair o divisor do MSB do dividendo, averiguar o sinal do resultado dessa divisão. Caso o sinal seja $\geq 0$, teremos que o MSB do quociente será 1. Caso contrário, o MSB do quociente será zero.

- Repetir o passo anterior, fazendo o shift à direita do dividendo.

Divisor(D) = 64 bits
Resto(R) = 64 bits
Quociente(Q) = 32 bits

### Algoritmo

1. Passo 1: `R=K`, `contador=1`;
2. Passo 2: `R=R-D`
3. Passo 3: Desloque `Q` à esquerda.
    - Se $R\geq0$, Q[0]=1;
    - Se $R<0$, restaure o valor original de R (`R+=D`).
4. Passo 4: Desloque D à direita.
5. Passo 5: Se `contador < 33`, `contador++` e volte ao Passo 2.

Exemplo, com registradores de 4 bits: $0111\div0010$

Divisor (8 bits) $\rightarrow$ 0100 **0000**

Resto (8 bits) $\rightarrow$ **0000** 0111

## Tabela

<center>

|Iteração|Descrição|Q|D|R|
|:-:|-|-|:-:|:-:|
|0|Inicialização|0000|0010 0000|0000 0111|
|1|sll Q, R=R-D<br>srl D<br> add R, R, D|0000 <br> 0000 <br> 0000|0010 0000<br>0001 0000<br>0001 0000|$<0$ <br> $<0$ <br> 0000 0111|
|2|sll Q, R=R-D<br>srl D<br> add R, R, D|0000<br>0000 <br> 0000|0001 0000<br>0000 1000<br>0000 1000|$<0$ <br> $<0$ <br> 0000 0111|
|3|sll Q, R=R-D<br>srl D<br> add R, R, D|0000<br>0000 <br> 0000|0000 1000<br>0000 0100<br>0000 0100|$<0$ <br> $<0$ <br> 0000 0111|
|4|sll Q, R=R-D<br>srl D<br> `Q[0]=1`|0000<br>0000 <br> 0001|0000 0100<br>0000 0010<br>0000 0010|0000 0111 <br> 0000  0011 <br> 0000 0011|
|5|sll Q, R=R-D<br>srl D<br> `Q[0]=1`|0000<br>0010 <br> 0011|0000 0010<br>0000 0001<br>0000 0001|0000 0011 <br> 0000 0001 <br> 0000 0001|

</center>

## Instruções no MIPS

- div (com sinal)
- divu (sem sinal)
- div reg1, reg2
- resto: hi, quociente: lo;
- mfhi reg => reg = hi
- mflo reg => reg = lo

> Obs: O resto sempre possui o mesmo sinal do dividendo.
>
> Ex:
> $7\div(-3)=-2$, resto 1.
> $-7\div3=-2$, resto -1.
