# Trabalho Final de Algoritmo e Estrutura de Dados I
    
Trabalho desenvolvido por:
  
  - [Filipe Manganelli](https://github.com/fbmanganelli) e
  - [Iury Alves](https://github.com/iuryalvez) 

Nossa aplicação é um programa que faz o controle do banco de dados do Restaurante 
Universitário (RU) da UFG, em código (Linguagem C), é uma lista encadeada que 
será responsável por armazenar a matrícula, nome e créditos de diferentes alunos.

### Requisitos funcionais: A aplicação conta com 5 arquivos:
- “RU.h” = header com declaração das funções e estruturas
- “RU.c” = responsável por implementar as funções auxiliares do programa
- ”ADM.c” = responsável por implementar as funções administrativas do programa
- “main.c” = o script principal.

Para compilar e executar:        
 
        gcc -c RU.c -o RU.o 
 
        gcc -c ADM.c -o ADM.o
    
        gcc RU.o ADM.o main.c -o main.exe 
    
        ./main.exe

### A aplicação conta com as seguintes funcionalidades:
  ##### 1. Administrativo:
  - a. Voltar ao menu principal;
  - b. Cadastrar novo usuário;
  - c. Verificar cadastro de usuário (busca sequencial e binária);
  - d. Alterar informações do usuário;
  - e. Excluir um usuário;
  - f. Adicionar créditos a um usuário;
  - g. Remover créditos de um usuário;
  - h. Verificar créditos do usuário;
  - i. Listar todos os usuários;
  - j. Ordenar os usuário em função de suas matrículas (quicksort e merge
    sort)
  ##### 2. Entrada de usuário no RU:
  - a. Verificar se o usuário está cadastrado;
  - b. Verificar se o usuário possui créditos;
  - c. Remover créditos ao entrar;
  ##### 3. Mostrar cardápio:
   - a. Verificar cada dia da semana;
   - b. Listar o cardápio dos dias da semana;

O programa possui algumas estruturas de dados que são criadas, alteradas e excluídas
de acordo com os processos. Temos o Cadastro dinâmico, o Cadastro estático, e o Cardápio
também estático. Utilizamos funções de busca sequencial e busca binária conforme foi
pedido e para os dois algoritmos de ordenação escolhemos o quicksort e o merge sort, ambos
estudados em classe.

O programa é bem intuitivo para ser usado, já vem com dados de 15 pessoas 
cadastradas para melhor manipulação e visualização do programa, não achamos
que possa ter problemas na execução.

  - filipemanganelli@discente.ufg.br
  - iury.alves@discente.ufg.br
