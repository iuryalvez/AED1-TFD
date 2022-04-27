/* 
    Disciplina de Algoritmo e Estrutura de Dados
    Alunos: Filipe Brito Manganelli (202103723) e Iury Alexandre Alves Bó (202103735)
    
    Aplicação para o restaurante universitário, realiza operações
    básicas de atendimento.

    O trabalho precisa ter:
    
    1. TAD's; OK
    2. Mínimo de 1 struct dinâmica e 1 struct estática; OK
    3. Implementar busca sequencial e binária; OK
    4. Utilizar pelo menos dois algoritmos de ordenação; OK
    5. Obter e apresentar a complexidade computacional; OK
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define TAM 5 // tamanho da semana

/**
 * @brief estrutura contendo as informações da pessoa que será cadastrada
 * 
 */
struct pessoa {
    struct pessoa *proximo;
    int matricula;
    int creditos;
    char nome[40];
};

typedef struct pessoa Pessoa;

/**
 * @brief estrutura do cadastro que armazena a primeira e a última pessoa para acesso
 * 
 */
struct cadastro {
    Pessoa *primeiro, *ultimo;
    int tamanho;
};

typedef struct cadastro Cadastro;

/**
 * @brief estrutura de cadastro estática, utilizada para ordenação e busca binária
 * 
 */
struct cadastro_estatico {
    int matricula;
    int creditos;
    char nome[40];
};

typedef struct cadastro_estatico Cadastro_estatico;

/**
 * @brief estrutura de um dia da semana
 * 
 */
struct cardapio {
    char comida[TAM][120];
};

typedef struct cardapio Cardapio;

/**
 * @brief função que verifica se a lista está vazia
 * 
 * @param cadastro acesso ao cadastro de alunos
 * @return int, TRUE or FALSE
 */
int cadastro_vazio (Cadastro *cadastro);

/**
 * @brief função que cria um cadastro se não houver nenhum
 * 
 * @return Cadastro*, um cadastro alocado
 */
Cadastro *criar_cadastro();

void ordenacao (Cadastro *cadastro);

/**
 * @brief função que lista os alunos cadastrados no RU
 * 
 * @param cadastro acesso ao cadastro dos alunos
 */
void listar_cadastro (Cadastro *cadastro);

/**
 * @brief função que cadastra uma pessoa
 * 
 * @param cadastro acesso ao cadastro dos alunos
 */
void cadastrar_pessoa (Cadastro *cadastro);

void entrada(Cadastro* cadastro);

/**
 * @brief função que retorna uma pessoa que existe no cadastro
 * 
 * @param cadastro acesso ao cadastro de alunos
 * @param matricula matrícula da pessoa
 * @return Pessoa* 
 */
Pessoa *retornar_pessoa (Cadastro *cadastro, int matricula);

/**
 * @brief 
 * 
 * @param cadastro acesso ao cadastro de alunos
 */
void alterar_pessoa (Cadastro *cadastro);

/**
 * @brief função que descadastra uma pessoa cadastrada
 * 
 * @param cadastro acesso ao cadastro dos alunos
 * 
 * @return Pessoa *, pessoa a ser excluida
 */
Pessoa *excluir_pessoa (Cadastro *cadastro);

/**
 * @brief função que adiciona créditos para compra
 * 
 * @param cadastro acesso ao cadastro dos alunos
 */
void adicionar_creditos (Cadastro *cadastro);

/**
 * @brief função que remove créditos por terem comprado ou parar devoluções
 * 
 * @param cadastro acesso ao cadastro dos alunos
 */
void remover_creditos (Cadastro *cadastro);

/**
 * @brief função que verifica os créditos que um aluno possui
 * 
 * @param cadastro acesso ao cadastro dos alunos
 * @param mat matrícula do aluno
 * 
 * @return int, verdadeiro ou falso, possui ao menos 1 ou nao...
 */
int verifica_creditos (Cadastro *cadastro, int mat);

/**
 * @brief função que verifica o menu
 * 
 * @param dia dia da semana
 */
void verificar_cardapio ();

/**
 * @brief função que mostra as opções "ir para o atendimento", "ir comer", "mostrar cardapio", "sair" 
 * 
 * @return int, o operador do menu;
 */
int opcoes ();

/**
 * @brief função que imprime as opções possíveis
 * 
 */
void print_opcoes ();

/**
 * @brief função que entra no menu de atendimento
 * 
 */
void atendimento (Cadastro *cadastro);

/**
 * @brief função que imprime as opções possíveis do centro de atendimento
 * 
 */
void print_atendimento ();

/**
 * @brief Função auxiliar que libera memória alocada dinamicamente
 * 
 * @param cadastro Acesso ao cadastro alocado
 */
void liberar_cadastro(Cadastro *cadastro);

/**
 * @brief função que realiza busca binária
 * 
 * @param cadastro acesso ao cadastro
 * @param matricula matrícula do aluno a ser buscado
 * @return int, verdadeiro ou falso
 */
int busca_binaria (Cadastro *cadastro, int matricula);

/**
 * @brief função que busca sequencialmente
 * 
 * @param cadastro cadastro dinâmico
 * @param matricula matrícula do usuário
 * @return int, TRUE or FALSE
 */
int busca_sequencial(Cadastro *cadastro, int matricula);

/**
 * @brief função ordenação - quicksort
 * 
 * @param cadastro_E cadastro estático para ordenar
 * @param inicio primeiro elemento
 * @param fim último elemento
 */
void quick_sort_Matricula (Cadastro_estatico *cadastro_E, int inicio, int fim);

/**
 * @brief função ordenação - mergesort
 * 
 * @param cadastro_E cadastro estático para ordenar
 * @param tam tamanho
 */
void merge_sort_Matricula (Cadastro_estatico *cadastro_E, int tam);

/**
 * @brief função auxiliar do merge sort
 * 
 * @param v 
 * @param c 
 * @param i início
 * @param f fim
 */
void sort_matricula (Cadastro_estatico *v, Cadastro_estatico *c, int i, int f);

/**
 * @brief função auxiliar do merge sort
 * 
 * @param v 
 * @param c 
 * @param i início
 * @param m meio
 * @param f fim
 */
void merge_Matricula(Cadastro_estatico *v, Cadastro_estatico *c, int i, int m, int f);

/**
 * @brief função que alterna alunos do cadastro estático
 * 
 * @param i aluno que será trocado com j
 * @param j aluno que será trocado com i
 * @param cadastro_E acesso ao cadastro estático
 */
void swap_alunoE (int i, int j, Cadastro_estatico *cadastro_E);

/**
 * @brief função que copia o cadastro estático para o dinâmico 
 * 
 * @param cadastro_E cadastro estático
 * @param cadastro cadastro dinâmico
 */
void copy_cadastro (Cadastro_estatico *cadastro_E, Cadastro *cadastro);

/**
 * @brief função que limpa a tela para melhor visualização do programa
 * 
 */
void clear_screen();

/**
 * @brief função que inputa dados no cadastro
 * 
 * @param cadastro cadastro dinâmico
 */
void input_usuarios (Cadastro *cadastro);

/**
 * @brief função que imprime "Pressione qualquer tecla para continuar"
 * 
 */
void Continue();

/**
 * @brief função que pergunta se quer cadastrar um usuário não encontrado em verificações
 * 
 * @param cadastro cadastro dinâmico
 * @param mat matrícula do usuário
 */
void Not_Found(Cadastro *cadastro, int mat);

/**
 * @brief opção 2 do programa administrativo, não é o mesmo da busca seq. ou bin.
 * 
 * @param cadastro cadastro dinâmico
 */
void verificar_pessoa(Cadastro *cadastro);

void quick_sort_int (int *matriculas, int inicio, int fim);

void swap_mat(int i, int j, int *matriculas);