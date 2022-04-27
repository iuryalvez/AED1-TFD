/*
    MODULO COM AS FUNCOES AUXILIARES DO PROGRAMA
*/

#include "RU.h"

// Primeiras opções

void print_opcoes () {
    printf("\t| Menu |\n\n");
    printf("\t1 - Administrativo\n");
    printf("\t2 - Entrada de usuario no restaurante\n");
    printf("\t3 - Cardapio\n");
    printf("\t0 - Sair\n");
}

int opcoes () {
    int op;
    do {
        print_opcoes();
        scanf("%d%*c", &op);
        if (op < 0 || op > 3) printf("Insira uma opcao valida!\n");
    } while (op < 0 || op > 3);
    return op;
}

// ATENDIMENTO

void print_atendimento () {
    printf("\t| Administrativo |\n\n");
    printf("\t1 - Cadastrar um usuario\n");
    printf("\t2 - Verificar cadastro de um usuario\n");
    printf("\t3 - Alterar informacoes de um usuario\n");
    printf("\t4 - Excluir um usuario\n");
    printf("\t5 - Adicionar creditos a um usuario\n");
    printf("\t6 - Remover creditos de um usuario\n");
    printf("\t7 - Verificar creditos de um usuario\n");
    printf("\t8 - Listar todos os usuarios\n");
    printf("\t9 - Ordenar todos os usuarios\n");
    printf("\t0 - Voltar\n");
}

void input_usuarios (Cadastro *cadastro) {
    Cadastro_estatico cad[15];
    strcpy(cad[0].nome,"Filipe Manganelli");
    cad[0].creditos = 6;
    cad[0].matricula = 202103723;
    strcpy(cad[1].nome,"Iury Alves");
    cad[1].creditos = 4;
    cad[1].matricula = 202103735;
    strcpy(cad[2].nome,"Charles do Bronx");
    cad[2].creditos = 200;
    cad[2].matricula = 10;
    strcpy(cad[3].nome,"Barry Allen");
    cad[3].creditos = 0;
    cad[3].matricula = 300000000;
    strcpy(cad[4].nome,"Cristiano Ronaldo");
    cad[4].creditos = 7;
    cad[4].matricula = 7;
    strcpy(cad[5].nome,"Goku");
    cad[5].creditos = 10;
    cad[5].matricula = 8001;
    strcpy(cad[6].nome,"Peter Parker");
    cad[6].creditos = 0;
    cad[6].matricula = 200200616;
    strcpy(cad[7].nome,"Leonardo da Vinci");
    cad[7].creditos = 20;
    cad[7].matricula = 20;
    strcpy(cad[8].nome,"Neymar hexacampeao");
    cad[8].creditos = 6;
    cad[8].matricula = 6;
    strcpy(cad[9].nome,"Kevin Durant");
    cad[9].creditos = 35;
    cad[9].matricula = 35;
    strcpy(cad[10].nome,"Leonardo Fibonacci");
    cad[10].creditos = 1;
    cad[10].matricula = 11235813;
    strcpy(cad[11].nome,"Lightning McQueen");
    cad[11].creditos = 4;
    cad[11].matricula = 95;
    strcpy(cad[12].nome,"Alan Turing");
    cad[12].creditos = 5;
    cad[12].matricula = 69;
    strcpy(cad[13].nome,"Luis Ignacio");
    cad[13].creditos = 13;
    cad[13].matricula = 13;
    strcpy(cad[14].nome,"Jair Bolsonaro");
    cad[14].creditos = 3;
    cad[14].matricula = 17;

    int tam = 15;
    int i;
    Pessoa *novo = (Pessoa *) malloc(sizeof(Pessoa)); // alocar memória para o novo elemento
    if (!novo) {
        printf("Memoria insuficente!\n");
        return;
    }
    novo->matricula = cad[0].matricula;
    novo->creditos = cad[0].creditos;
    strcpy(novo->nome,cad[0].nome);
    cadastro->primeiro = novo;
    cadastro->ultimo = novo;
    for (i = 1; i < tam; i++) {
        novo->proximo = (Pessoa *) malloc(sizeof(Pessoa)); // alocar memória para o novo elemento
        if (!novo) {
            printf("Memoria insuficente!\n");
            return;
        }
        novo = novo->proximo;
        novo->matricula = cad[i].matricula;
        novo->creditos = cad[i].creditos;
        strcpy(novo->nome,cad[i].nome);
    }
    cadastro->ultimo = novo;
    novo->proximo = NULL;
    cadastro->tamanho = tam;
}

int cadastro_vazio (Cadastro *cadastro) {
    if (cadastro->primeiro == NULL) { // verificação, se for NULL, o início não possui elementos, então está vazio
        printf("Ainda nao ha pessoas cadastradas!\n");
        return TRUE;
    }
    return FALSE; // se não, o cadastro não está vazio
}

Cadastro *criar_cadastro() {
    // declarar o cadastro alocando dinamicamente
    Cadastro *cadastro = (Cadastro *) malloc(sizeof(Cadastro));
    if (!cadastro) {
        printf("Memoria insuficiente!\n");
        return NULL;
    }
    cadastro->tamanho = 0; // cadastro vazio
    return cadastro;
}

int busca_sequencial (Cadastro *cadastro, int matricula) {
    Pessoa *aux = cadastro->primeiro;
    while (aux != NULL) {
        if (aux->matricula == matricula) {
            return TRUE;
        }
        aux = aux->proximo;
    }
    return FALSE;
}

Pessoa *retornar_pessoa (Cadastro *cadastro, int matricula) {
    Pessoa *aux = cadastro->primeiro;
    while (aux != NULL) {
        if (aux->matricula == matricula) return aux;
        aux = aux->proximo;
    }
    return NULL;
}

void Not_Found(Cadastro *cadastro, int mat){
    int op;

    printf("O usuario nao esta cadastrado\n");
    printf("Deseja cadastra-lo?\n");
    printf("1 - Sim\n2 - Nao\n");
    scanf("%d%*c", &op);
    while(op < 1 || op > 2) {
        printf("Insira uma opcao valida!\n");
        scanf("%d%*c", &op);
    }
    if (op == 1) {
        cadastrar_pessoa(cadastro);
    }
}

int verifica_creditos (Cadastro *cadastro, int mat) {
    Pessoa *aux;
    if (busca_sequencial(cadastro,mat) == FALSE) return FALSE;    
    aux = retornar_pessoa(cadastro, mat);
    if (aux->creditos == 0) {
        return FALSE;
    }
    else return TRUE;
}

void liberar_cadastro (Cadastro *cadastro) {
    Pessoa *head = cadastro->primeiro;
    if (head == NULL) {
        return;
    }
    else {
        while (head != cadastro->ultimo) {
            Pessoa *aux = head;
            head = head->proximo;
            free(aux);
        }
        Pessoa *aux = head;
        head = NULL;
        free(aux);
    }
}

int busca_binaria (Cadastro *cadastro, int matricula) {
    int i, esq, dir;
    
    if (cadastro->tamanho == 1 || cadastro->tamanho == 2) {
        if (matricula == cadastro->primeiro->matricula) return TRUE;
        if (matricula == cadastro->ultimo->matricula) return TRUE;
        else return FALSE;
    }

    int *matriculas = (int *) malloc(sizeof(int) * cadastro->tamanho);
    Pessoa *aux = cadastro->primeiro;

    for (i = 0; aux != NULL; i++) {
        matriculas[i] = aux->matricula;
        aux = aux->proximo;
    }

    quick_sort_int(matriculas, 0, cadastro->tamanho);

    esq = 0;
    dir = cadastro->tamanho-1;
    while (esq <= dir) {  /* Condição de parada */
        // printf("Debug 2\n");
        i = (int)(esq + dir) / 2;  /* Calcula o meio do sub-vetor */

        if (matriculas[i] == matricula) {  /* Item encontrado */
            free(matriculas);
            return TRUE;
        }
        if (matriculas[i] < matricula) {  /* Item está no sub-vetor à direita */
            esq = i + 1;
        } else {  /* cadastro_B[i].matricula > mat. Item está no sub-vetor à esquerda */
            dir = i - 1;
        }
    }
    free(matriculas);
    return FALSE;
}

void quick_sort_int (int *matriculas, int inicio, int fim) {
    int i, j;
    int x;
    int temp;

    i = inicio;
    j = fim;
    x = matriculas[(inicio+fim)/2];

    do {
        while (matriculas[i] < x && i < fim) {
            i++;
        } 
        while (matriculas[j] > x && j > inicio) {
            j--;
        }
        if (i <= j) {
            swap_mat(i, j, matriculas);
            i++;
            j--;
        }
    } while (i <= j);

    if (inicio < j) {
        quick_sort_int(matriculas, inicio, j);
    }
    if (i < fim) {
        quick_sort_int(matriculas, i, fim);
    }
}

void swap_mat(int i, int j, int *matriculas) {
    int temp = matriculas[i];
    matriculas[i] = matriculas[j];
    matriculas[j] = temp;
}

void quick_sort_Matricula (Cadastro_estatico *cadastro_E, int inicio, int fim) {
    int i, j;
    int x;
    int temp;

    i = inicio;
    j = fim;
    x = cadastro_E[(inicio+fim)/2].matricula;

    do {
        while (cadastro_E[i].matricula < x && i < fim) {
            i++;
        } 
        while (cadastro_E[j].matricula > x && j > inicio) {
            j--;
        }
        if (i <= j) {
            swap_alunoE(i, j, cadastro_E);
            i++;
            j--;
        }
    } while (i <= j);

    if (inicio < j) {
        quick_sort_Matricula(cadastro_E, inicio, j);
    }
    if (i < fim) {
        quick_sort_Matricula(cadastro_E, i, fim);
    }
}

void swap_alunoE (int i, int j, Cadastro_estatico *cadastro_E) {
    Cadastro_estatico temp = cadastro_E[i];
    cadastro_E[i] = cadastro_E[j];
    cadastro_E[j] = temp;
}

void merge_sort_Matricula (Cadastro_estatico *cadastro_E, int tam) {
    Cadastro_estatico *c = malloc(sizeof(Cadastro_estatico)*tam);
    sort_matricula(cadastro_E, c, 0, tam-1);
    free(c);
}

void sort_matricula (Cadastro_estatico *v, Cadastro_estatico *c, int i, int f) {
    if (i >= f) return;

    int m = (i+f)/2;
    sort_matricula(v,c,i,m);
    sort_matricula(v,c,m+1,f);
    
    if (v[m].matricula <= v[m+1].matricula) return;
    
    merge_Matricula(v,c,i,m,f);
}

void merge_Matricula(Cadastro_estatico *v, Cadastro_estatico *c, int i, int m, int f) {
    int z, iv = i, ic = m+1;
    
    for (z = i; z <= f; z++) c[z] = v[z];
    z = i;

    while (iv <= m && ic <= f) {
        if (c[iv].matricula <= c[ic].matricula) v[z++] = c[iv++];
        else v[z++] = c[ic++];
    }

    while (iv <= m) v[z++] = c[iv++];
    while (ic <= f) v[z++] = c[ic++];
}

void copy_cadastro (Cadastro_estatico *cadastro_E, Cadastro *cadastro) {
    int i;
    Pessoa *aux;
    for (i = 0, aux = cadastro->primeiro; aux != NULL; i++, aux = aux->proximo) {
        aux->matricula = cadastro_E[i].matricula;
        aux->creditos = cadastro_E[i].creditos;
        strcpy(aux->nome,cadastro_E[i].nome);
    }
}

void clear_screen () {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}

void Continue(){
    printf("\nPressione qualquer tecla para continuar\n");
    getchar();
}
