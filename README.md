![Screenshot](Figures/Capturar.JPG)

Projeto de uma linguagem denominada GOL e de seu respectivo compilador (fase de síntese) com geração de código de três endereços.

Autor: Michelangelo da Rocha Machado.

# Andamento do projeto
- [x] Análise Léxica
- [x] Análise sintática
- [x] Análise semântica
- [x] Geração de código intermediário

# Linguagem
## Documentação:
[GOL Language Documentation](https://github.com/michelangelo246/Compilador/blob/master/Doc/14_0156089_tradutor.pdf)

## Efeito de algumas operações:

As operações a seguir foram derivadas de algumas das operações
básicas encontradas na biblioteca Ngraph para lidar com grafos em C++.

```c
graph G1; //Declaração de variável do tipo graph
graph G2;
graph G3;
int a = 13;

G1 << a; //Inserção de vértice 13 no grafo G1
G1 << (a,14); //Inserção de aresta (13,14) no grafo G1
G2 << 15; //Inserção de vértice 15 no grafo G2
a = G3@(13)#; //a recebe o grau de entrada do nó 13
a = G3#(13)@; //a recebe o grau de saída do nó 13
G3 = G1&(13)&; //G3 recebe grafo composto pelos vizinhos do nó 13 no grafo G1
```
Operações removidas:
* ~~G3 = G1 + G2; //G3 recebe união dos grafos G1 e G2~~
* ~~G2 = G3[(G1)]; //G2 recebe subgrafo de G3 composto por vértices de G1~~

## Notas:

Os únicos tipos numéricos são: ‘int’ e ‘float’; Não existe sobrecarga de nomes de funções; Em um ‘if’, o ‘else' estará associado com o ‘if’ mais recente; Expressões matemáticas são avaliadas em ordem consistente com aquelas da matemática; O tipo grafo armazena grafos direcionados com repetição de arestas; O tamanho máximo de um identificador é 31 caracteres; As declarações de variáveis devem constar antes dos statements e somente no escopo global ou de uma função; Grafos não podem ser declarados globalmente;

# Codigo:

O programa pode gerar a árvore sintática abstrata (AST) nas seguintes formas:
1. Texto puro **
2. Codigo .dot que pode ser copiado para algum site (e.g. [webgraphviz](http://www.webgraphviz.com/)) 
3. Arquivo .dot que pode ser usado para gerar uma imagem com comando graphviz: ```dot -Tpng Arvore.dot -o Arvore.png ```*

\* Para utilizar o graphviz, instale-o na sua máquina através do comando: ```sudo apt install graphviz```

\*\* Descontinuado

## AST:
AST gerada a partir de código exemplo:

| Codigo        | AST           |
| ------------- |:-------------:|
| <img src="https://github.com/michelangelo246/Compilador/blob/master/Figures/Codigo.PNG" width="250">      | <img src="https://github.com/michelangelo246/Compilador/blob/master/Figures/Arvore.png" width="500">

## Geração de código:
O programa gera como saída um arquivo de extensão '.tac' o qual pode ser interpretado através da extração do interpretador TAC, contido no diretório de mesmo nome. O interpretador também pode ser baixado através do repositório do autor: https://github.com/lhsantos/tac.

| Código GOL    | Código gerado (fragmento) |
| ------------- |:-------------:|
| <img src="https://github.com/michelangelo246/Compilador/blob/master/Figures/CodigoGOL.PNG" width="250">      | <img src="https://github.com/michelangelo246/Compilador/blob/master/Figures/CodigoTAC.PNG" width="250">
