---
title: "Hierarquia de memória - Aula 8"
author: "Nicolas Chagas Souza"
date: 16/09/2022
geometry: left=2cm,right=2cm,top=1cm,bottom=2cm
output: pdf_document
---

## Na aula anterior

Mapeamento direto de memória

Dados

|||
|-|-|
|Memória principal|$2^t$ bytes|
|Memória cache| $2^n$ bytes|
|Blocos|$2^b$ bytes|

O endereço de memória principal é dado por

|Tag| Linha cache | Bloco |
|-|-|-|
|$t-n-b$ bits|$n$ bits| $b$ bits|

## Tamanho real da cache

|||
|-|-|-|
|bit de validade|tag|dados|

Quando dizemos o tamanho de uma memória cache, nos referimos ao total de dados que ela pode armazenar. Para calcular o tamanho real de uma cache, é necessário incluir o bit de validade e a tag, logo, para determinar esse tamanho:

1. Determinar o tamanho, em bytes:
    - Da memória principal
    - De um bloco da cache
2. Determinar o total de linhas da cache, ou seja, determinar t, n e b.
3. Determinar o tamanho da tag = $t - b - n$ bits.
4. Tamanho real da cache = $qtd_{linhas} \times \left (1+tag+dados por linha\right )$ bits, onde $qtd_{linhas}=2^n$

Obs: são dados o tamanho (dados) da cache, o tamanho de um bloco e o tamanho da memória principal.

## Conversão de unidades de medida

||
|-|
|1 byte = 8 bits
|$1KiB=2^{10}$ bytes
|$1MiB=2^{10}KiB=2^{20}B$
|$1GiB=2^{10}MiB=2^{30}B$
|$1TiB=2^{10}GiB=2^{40}B$

Quantos bits são necessários para uma memória cache diretamente mapeada com 16KiB de dados e blocos de 32B, considerando que a memória principal possui 4GiB?

Dados = $16 KiB = 2^4 \times 2^{10} B = 2^{14} B$

Blocos = $32 B = 2^5 \times  B$

Principal = $4 GiB = 2^2 \times 2^{30} B = 2^{32} B$

$2^n$ total de linhas da cache

$\frac{16KiB}{32B} = \frac{2^4\times 2^{10} B}{2^5 B} = 2^9 linhas$

n = 9
t = 32
b = 5

Tag = 32 - 9 - 5 = 18 bits

Dados = $16 KiB = 2^{4} \times 2^{10} B = 2^{14} B = 2^{17} bits$

Dados por linha = $2^{17} \div 2^{9} = 8$

Tamanho real da cache = $2^{9} \times (1+18+2^{8})$

$2^{9}\times (19+256) = 2^9 \times 275 bits$

$\frac{275\times 2^9}{2^10\times 2^3} KiB$

$\frac{256+19}{16} KiB$

$\frac{256}{16} + \frac{19}{16} KiB$

$16 + 1,18 KiB = 17,18 KiB$
