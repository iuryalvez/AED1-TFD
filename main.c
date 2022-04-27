/* 
    Disciplina de Algoritmo e Estrutura de Dados
    Alunos: Filipe Brito Manganelli (202103723) e Iury Alexandre Alves Bó (202103735)
    
    Aplicação para o restaurante universitário, realiza operações
    básicas de atendimento.
*/

#include "RU.h"

int main () {

    int op, dia, mat;
    Cadastro *cadastro;
    Pessoa *aux;
    cadastro = criar_cadastro();
    
    input_usuarios(cadastro);

    clear_screen();
    printf("Bem vindo ao PCDRU!\n");

    do {
        Continue();
        clear_screen();
        printf("\tPrograma de Controle de Dados Restaurante Universitário\n\n");
        op = opcoes();
        switch (op) {
        case 1:
            atendimento(cadastro);
            break;
        case 2: 
            entrada(cadastro);
            break;
        case 3:
            verificar_cardapio();
            break;        
        default:
            if (op < 0 || op > 3) printf("Insira uma opcao valida!\n");
            break;
        }
    } while (op != 0);
    clear_screen();
    liberar_cadastro(cadastro);

    printf("\nObrigado por utilizar nosso programa! :)\n");
    printf("Desenvolvido por Filipe Manganelli e Iury Alves!!\n\n");    
    
    return 0;
}