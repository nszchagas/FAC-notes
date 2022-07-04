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

6. Retorne ao caller (j $ra).

Para fazer o desvio do programa para um procedimento utilizamos a instrução jump and link (jal).

- `jal label`: desvia para um procedimento rotulado por label, e salva o conteúdo do PC no registrador $ra.

