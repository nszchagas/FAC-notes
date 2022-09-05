---
title: "Arquitetura de um processador - Aula 4"
author: "Nicolas Chagas Souza"
date: 26/08/2022
geometry: left=2cm,right=2cm,top=1cm,bottom=2cm
output: pdf_document
---

## MIPS Pipeline

Uma instrução pode executar as seguintes etapas:

1. Recuperação da instrução (IF - instruction fetch);
2. Decodificação e leitura no banco de registradores (ID - instruction decode);
3. Operação aritmética (EX - execution);
4. Acesso a memória de dados (MEM - memory access);
5. Escrita no banco de registradores (WB - write back).

## Melhorias no Pipeline

A melhoria deve-se a uma maior **vazão** de instruções, ou seja, a quantidade de instruções executadas ao mesmo tempo. O pipeline não altera a **latência**, que é o tempo de execução de cada instrução.

## Hazards

Situações que impede de começar próxima instrução no próximo ciclo:

- Hazards estruturais: um recurso necessário está indisponível (outra instrução usando o recurso);
- Hazard de dados: precisa aguardar uma instrução anterior para usar a sua saída;
- Hazard de controle: Decidir uma ação de controle depende de uma instrução anterior (ex: desvio).

## Hazard estruturais

Conflito ao utilizar um recurso. Esse é o motivo pelo qual no caminho de dados há duas memórias: de dados e de instrução.

