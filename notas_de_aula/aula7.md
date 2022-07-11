<<<<<<< HEAD
# Aula 7 - Linguagem de montagem

## Dica para o exercício de paridade

Fazer um and com uma máscara para contar os bits 1:

```assembly
    li $t0, 1
loop: 
    and $t1, $t0, $a0
    beq $t0, $t1, soma
    slt $t0, $t0, 1
    j loop
soma: 
    addi $t3, $t3, 1
    j loop
```

## Caracteres

- Conjunto especial tabelado
  - Tabela ASCII: mapeia um caractere para um número de 8 bits (1 byte).

  - Tabela Unicode

### Instruções para trabalhar com caracteres

Temos as instruções load byte e load byte unsigned:

- lb/lbu reg, offset(base)

Carregam apenas um byte no registrador de 4 bytes. Carregam o número e em seguida fazem a extensão de sinal. O lbu apenas completa com 0 os bits mais significativos.

> Para trabalhar com os caracteres utilizamos o lbu, já que os caracteres não possuem sinal.

Para armazenar um byte, utilizamos a instrução:

- sb reg, offset(base)

Exemplo:

```c
    void strcpy(char *x, char *y){
        int i = 0;
        do { // Observação: '\0' é o 0 na tabela ASCII.
            x[i] = y[i];
            i++;
        } while (y[i] != '\0');
    }
```

```assembly
    strcpy:                     # $a0 = *x e $a1 = *y
        add $t0, $zero, $zero   # i = 0
    loop:
        add $a1, $a1, $t0       # y = y + i
        lbu $t1, 0($a1)         # t1 = y[i]
        add $a0, $a0, $t0       # x = x + i
        sb $t1, 0($a0)          # x[i] = t1 (= y[i]). 
        addi $t0, $zero, 1      # i++; Incremento de 1 pois cada caractere utiliza apenas 1 byte na memória.
        bne $t1, $zero, loop    # if y[i] != 0 goto loop
        jr $ra
```

## Constantes de 32 bits

- Instruções do formato tipo I:

| op | rs | rt | const |
| --- | --- | --- | --- |
| 6 bits | 5 bits | 5 bits | 16 bits |

- O tamanho do registrador é 5 bits pois há 32 registradores (2⁵) diferentes.

Como armazenar números maiores do que 16 bits em um registrador? 

Exemplo: armazenando 4 milhões em um registrador.
| 0000000000111101 | 0000100100000000 |
| --- | --- |
| 16 bits | 16 bits |
| 61 | 2304 |

```assembly
    addi $s0, $zero, 61
    sll $s0, $s0, 16
    addi $s0, $s0, 2304
```

- Instrução load upper immediate: armazena 16 bits nos bits mais significativos de um registrador. 

```assembly
    lui $s0, 61     # lui é uma pseudoinstrução.
    addi $s0, $s0, 2304
```
=======
# Aula 7 - Linguagem de montagem - 04/07/22

## Procedimentos

> Função é um tipo de procedimento que possui retorno. Procedimentos não possuem retorno.

Para compilar procedimentos em Assembly é necessário entender alguns conceitos:

- caller: procedimento que faz a chamada
- callee: procedimento que é chamado

> Em procedimentos recursivos, o próprio procedimento será caller e callee, diferenciando-se as instâncias em execução.

- Program Counter (PC)

  - O programa é um vetor de instruções na memória, ou seja, cada instrução possui um endereço de memória. O PC é um registrador que armazena o endereço de memória da próxima instrução a ser executada pelo programa.

Obs: As instruções de desvio (beq, bne e j) operam sobre o PC.

- Procedimento folha: é um procedimento que não faz chamada a nenhum outro procedimento. O nome folha faz referência à estrutura de árvore, estes procedimentos estão nas extremidades, ou seja, não fazem chamadas à nenhum outro procedimento.

Exemplo:

```C
main() { // Nesse instante o caller é o S.O. e o callee é a main
    // ...
    media(x, y); // Nesse instante o caller é a main e o callee é a função média.
}

media(int x, int y){ # Procedimento folha, pois não faz chamada à nenhum outro procedimento.
    return (x+y)/2; 
}
```

- No Assembly MIPS as variáveis (registradores) possuem "escopo" global, então cabe ao programador salvar os valores utilizados nos registradores salvos (ex: $s0) ao iniciar um procedimento, para não sobrescrever informações utilizadas em outros procedimentos.

### Etapas para a chamada de um procedimento

1. Armazenar os parâmetros nos registradores ($a0-$a3), se couber, e caso não caiba a passagem de argumentos deve ser feita pela memória (utilizando as instruções sw e lw).

2. Desviar o fluxo do programa para o procedimento (jal label).

3. Ajustar o armazenamento no procedimento:

    - Há argumentos na memória que precisam ser carregados?

    - É necessário fazer backup de registradores salvos $s?

4. Executar as instruções do procedimento.

5. Salve o retorno do procedimento ($v0-$v1).

6. Restaure os backups.

7. Retorne ao caller (jr $ra).

Para fazer o desvio do programa para um procedimento utilizamos a instrução jump and link (jal).

- `jal label`: desvia para um procedimento rotulado por label, e salva o conteúdo do PC no registrador $ra.

Para retornar ao caller utilizamos a instrução jump register (jr).

- `jr $ra`: desvia para a instrução cujo endereço está em $ra.

Como fazer e restaurar os backups?

Por convenção, é necessário salvar o conteúdos dos registradores $s. Para isso, utilizamos a pilha.

A memória do computador é segmentada em 4 partes, do endereço 0 ao endereço máximo, temos:

- Os endereços mais baixos são reservados para o sistema operacional

- Acima dele vem o segmento de texto, que é a parte da memória reservada para armazenar as instruções de programa. O PC sempre contém um endereço desse segmento da memória.

- Dados estáticos: dado cujo o endereço de memória permanece alocado para o programa mesmo que o escopo da variável já tenha acabado.

- Dados dinâmicos:

  - heap: parte da memória reservada para as alocações dinâmicas, cresce de baixo para cima.

  - pilha: cresce de cima para baixo.

O registrador global stack pointer ($sp) aponta para a última posição de memória com dados na pilha, ou seja, o topo da pilha. Para armazenar dados na pilha é necessário seguir o seguinte passo a passo:

1. Abrir espaço na pilha: decrementar a quantidade necessária de bytes de $sp.

2. Armazenar os dados utilizando a expressão sw a partir de $sp.

Para restaurar os dados da pilha:

1. Restaurar os dados usando lw. 

2. Restaurar o espaço da pilha: incrementar a quantidade de bytes que foram utilizadas em $sp novamente. 

Exemplo: armazenar e restaurar o conteúdo dos registradores $s0 e $s1 na pilha.

    ```
    subi $sp, $sp, 8 # Abrindo 2 espaços de memória
    sw $s0, 0($sp) # Armazena $s0 no primeiro espaço, apontado por $sp
    sw $s1, 4($sp) # Armazena $s1 no segundo espaço, apontado por $sp + 4
    # ...

    lw $s1, 4($sp)
    lw $s0, 0($sp)
    addi $sp, $sp, 8 
    ```

Exemplo 2: fatorial

```C
int fat(int n){
    if (n<1)
        return 1;
    else 
        return n*fat(n-1);
    
}
```

```
    fat: # Argumento em $a0  
    
    addi $sp, $sp, -8 # Abre espaço para salvar $ra e $a0
    sw $a0, 0($sp) # Salva a0 na pilha
    sw $ra, 4($sp) # Salva $ra na pilha

    addi $t1, $zero, 1
    slt $t0, $a0, $t1 # t0 = n < 1
    beq $t0, $zero, L1 # if (n<1) goto L1

    addi $v0, $zero, 1
    jr $ra
    
    
L1: addi $a0, $a0, -1 #n--
    jal fat

    lw $a0, 0($sp)
    lw $ra, 4($sp)
    addi $sp, $sp, 8

    mul $v0, $a0, $v0 
    jr $ra

```
>>>>>>> ef5b7b188152ffcb8a415b53cb8f12f708c94185
