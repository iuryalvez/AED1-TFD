/*
    MODULO COM AS FUNCOES ADMINISTRATIVAS DO PROGRAMA
*/

#include "RU.h"

void atendimento (Cadastro *cadastro) {
    int op, opc, mat;
    Pessoa *aux, *removido;

    do {
        Continue();
        clear_screen();
        print_atendimento();
        scanf("%d%*c", &op);
        clear_screen();
        switch (op) {
            case 1:
                cadastrar_pessoa(cadastro);
                break;
            case 2:
                if (cadastro_vazio(cadastro)) break;
                verificar_pessoa(cadastro);
                break;
            case 3:
                if (cadastro_vazio(cadastro)) break;
                alterar_pessoa(cadastro);
                break;
            case 4:
                if (cadastro_vazio(cadastro)) break;
                removido = excluir_pessoa(cadastro);
                if (removido) {
                    printf("Pessoa removida: %s\n", removido->nome);
                    free(removido);
                }
                else {
                    printf("Ninguem foi removido!\n");
                }
                break;
            case 5:
                if (cadastro_vazio(cadastro)) break;
                adicionar_creditos(cadastro);
                break;
            case 6:
                if (cadastro_vazio(cadastro)) break;
                remover_creditos(cadastro);
                break;
            case 7:
                if (cadastro_vazio(cadastro)) break;
                printf("| Verificando creditos |\n\n");
                printf("Insira a matricula do usuario:\n");
                scanf("%d%*c", &mat);
                if (busca_sequencial(cadastro,mat) == TRUE) {
                    aux = retornar_pessoa(cadastro, mat);
                    printf("%s possui %d credito(s)\n", aux->nome, aux->creditos);
                    break;
                } else Not_Found(cadastro, mat);
                break;
            case 8:
                if (cadastro_vazio(cadastro)) break;
                listar_cadastro(cadastro);
                break;
            case 9:
                if (cadastro_vazio(cadastro)) break; 
                ordenacao(cadastro);
                break;
            default:
                if (op < 0 || op > 9) printf("Insira uma opcao valida!\n");
                break;
        }
    } while (op != 0);
}

void cadastrar_pessoa (Cadastro *cadastro) {
    Pessoa *novo = (Pessoa *) malloc(sizeof(Pessoa)); // alocar memória para o novo elemento
    if (!novo) {
        printf("Memoria insuficente!\n");
        return;
    }
    printf("| Cadastrando novo usuario |\n\n");
    printf("Qual o nome da pessoa?\n");
    scanf("%[^\n]%*c", novo->nome);

    printf("Qual a matricula da pessoa?\n");
    scanf("%d%*c", &novo->matricula);
    if (busca_sequencial(cadastro,novo->matricula) == TRUE) { // verificando pessoa
        printf("Ja existe alguem com esta matricula cadastrado!\n");
        return;
    }
    novo->creditos = 0;
    // se for o primeiro do cadastro:
    if (cadastro->primeiro == NULL) {
        cadastro->primeiro = novo;
        cadastro->ultimo = novo;
        cadastro->ultimo->proximo = NULL;
        cadastro->tamanho++;
    } 
    else { // se não, colocar depois do último
        cadastro->ultimo->proximo = novo;
        cadastro->ultimo = novo;
        novo->proximo = NULL;
        cadastro->tamanho++;
    }
    printf("Cadastro realizado com sucesso!\n");
    
}

void verificar_pessoa(Cadastro *cadastro) { 
    int mat, opc, ver;
    Pessoa *aux;
    printf("| Verificando cadastro de usuario |\n\n");
    printf("Insira a matricula da pessoa:\n");
    scanf("%d%*c", &mat);
    
    printf("Deseja utilizar o tipo de busca:\n");
    printf("1 - Sequencial\n");
    printf("2 - Binaria\n");
    scanf("%d%*c", &opc);
    
    while (opc < 1 || opc > 2) {
        printf("Insira uma opcao valida!\n");
        scanf("%d%*c", &opc);
    }

    if (opc == 1) ver = busca_sequencial(cadastro,mat);
    else ver = busca_binaria(cadastro, mat); 
    
    if (ver == FALSE) Not_Found(cadastro,mat);
    else {
        aux = retornar_pessoa(cadastro,mat);
        printf("Usuário cadastrado como %s\nPossui %d creditos!\n", aux->nome, aux->creditos);
    }                
}

void listar_cadastro (Cadastro *cadastro) { // ver como está o cadastro
    Pessoa *aux = cadastro->primeiro;
    int i = 1;
    
    printf("| Listando cadastros |\n\n");
    if (cadastro_vazio(cadastro) == FALSE) { 
        while (aux != NULL) {
            printf("\t#%d. Nome: %s\n\tMatricula: %d\n\tCreditos: %d\n\n", i, aux->nome, aux->matricula, aux->creditos);
            aux = aux->proximo;
            i++;
        }
    
    }
}

void alterar_pessoa (Cadastro *cadastro) {
    int op, opc, mat;
    Pessoa *aux;
    
    printf("| Alterando usuario |\n\n");
    printf("Insira a matricula do usuario a ser alterado:\n");
    scanf("%d%*c", &mat);

    if (busca_sequencial(cadastro,mat)) {
        aux = retornar_pessoa(cadastro, mat);
        printf("Tem certeza que deseja alterar o usuario \"%s\"?\n", aux->nome);
        printf("1 - Sim\n2 - Nao, retorne\n");
        scanf("%d%*c", &opc);
        if (opc == 1) {
            printf("O que sera alterado no usuario \"%s\"?\n", aux->nome);
            printf("1 - Nome\n");
            printf("2 - Matricula\n");
            scanf("%d%*c", &op);
            while (op < 1 || op > 2) {
                printf("Insira uma opcao valida!\n");
                scanf("%d%*c", &op);
            }  

            if (op == 1) {
                printf("Digite o novo nome para o usuario(a) %s:\n", aux->nome);
                scanf("%[^\n]%*c", aux->nome);
                printf("Nome alterado com sucesso!\n");
                
            } else {
                printf("%s, digite sua nova matricula:\n", aux->nome);
                scanf("%d%*c", &mat);
                while (busca_sequencial(cadastro,mat) == TRUE) {
                    if (mat == aux->matricula) printf("A matricula inserida eh a mesma de antes!\n");
                    else printf("Ja existe alguem com essa matricula cadastrada!\n");
                    printf("Insira outra matricula:\n");
                    scanf("%d%*c", &mat);
                }
                aux->matricula = mat;
                printf("Matricula alterada com sucesso!\n");
                
            }
        } else printf("Nenhum usuario foi alterado!\n");
    } else Not_Found(cadastro, mat);       
}

Pessoa *excluir_pessoa (Cadastro *cadastro){
    Pessoa *aux, *remover = NULL;
    int mat, opc;

    printf("| Excluindo usuario |\n\n");
    printf("Insira a matricula da pessoa a ser removida:\n");
    scanf("%d%*c", &mat);
    if (busca_sequencial(cadastro,mat) == FALSE) {  
        printf("Esta matricula nao esta cadastrada!\n");
        return remover;
    }
    else {
        aux = retornar_pessoa(cadastro, mat);
        printf("Tem certeza que quer remover %s?\n", aux->nome);
        printf("1 - Sim, quero remover\n");
        printf("2 - Nao, retorne\n");
        scanf("%d%*c", &opc);
        while(opc < 1 || opc > 2){
            printf("Insira uma opcao valida!\n");
            scanf("%d%*c", &opc);
        } 
    }
    if (opc == 2) return remover;
    
    if (cadastro->primeiro) {
        if (cadastro->primeiro == cadastro->ultimo) {
            remover = cadastro->primeiro;
            cadastro->primeiro = NULL;
            cadastro->tamanho--;
        }
        else if (cadastro->primeiro->matricula == mat) {
            remover = cadastro->primeiro;
            cadastro->primeiro = remover->proximo;
            cadastro->tamanho--;
        }
        else {
            aux = cadastro->primeiro;
            while (aux->proximo != NULL && aux->proximo->matricula != mat) {
                aux = aux->proximo;
            }
            if (cadastro->ultimo == aux->proximo) {
                remover = aux->proximo;
                aux->proximo = NULL;
                cadastro->ultimo = aux;
            }
            else {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
            }
            cadastro->tamanho--;
        }
    }
    return remover;
}

void adicionar_creditos (Cadastro *cadastro) {
    Pessoa *aux;
    int mat, cred;
    
    printf("| Adicionando creditos |\n\n");
    printf("Insira a matricula do usuario:\n");
    scanf("%d%*c", &mat);
    if (busca_sequencial(cadastro,mat)) {
        aux = retornar_pessoa(cadastro,mat);
        printf("Quantos creditos devem ser adicionados a(o) usuario(a) %s?\n", aux->nome);
        scanf("%d%*c", &cred);
        while (cred < 1) {
            printf("Insira valores >= 1\n");
            scanf("%d%*c", &cred);
        }
        aux->creditos += cred;
        printf("Creditos adicionados com sucesso!\n");
        printf("Agora %s possui %d credito(s)!\n", aux->nome, aux->creditos);
        
    } else Not_Found(cadastro, mat);
}

void remover_creditos (Cadastro *cadastro) {
    Pessoa *aux;
    int mat, cred;

    printf("| Removendo creditos |\n\n");
    printf("Insira a matricula do usuario:\n");
    scanf("%d%*c", &mat);

    if (busca_sequencial(cadastro,mat) == TRUE) {
        aux = retornar_pessoa(cadastro,mat);
        printf("%s possui %d credito(s)\n", aux->nome, aux->creditos);
        if (aux->creditos < 1) {
            printf("Nao ha creditos para remover!\n");
            
            return;
        }
        printf("%s, quantos creditos voce deseja remover?\n", aux->nome);
        scanf("%d%*c", &cred);
        while (cred < 1 || aux->creditos-cred < 0) {
            printf("Insira valores validos\n");
            scanf("%d%*c", &cred);
        }
        aux->creditos -= cred;
        
        printf("Creditos removidos com sucesso!\n");
        printf("Agora %s possui %d credito(s)!\n", aux->nome, aux->creditos);
        
    } else Not_Found(cadastro, mat);
    
}

void ordenacao (Cadastro *cadastro) {
    Cadastro_estatico cadastro_E[cadastro->tamanho];
    Pessoa *aux;
    int i, opc;
    clock_t time, time2;
    float t;
    
    aux = cadastro->primeiro;
    cadastro_E[cadastro->tamanho]; 
    
    for (i = 0; aux != NULL; i++) {
        cadastro_E[i].matricula = aux->matricula;
        cadastro_E[i].creditos = aux->creditos;
        strcpy(cadastro_E[i].nome,aux->nome);
        aux = aux->proximo;
    }

    printf("Voce deseja ordenar por:\n");
    printf("1 - Quick Sort\n");
    printf("2 - Merge Sort\n");
    scanf("%d%*c", &opc);
    
    while (opc < 1 || opc > 2) {
        printf("Insira uma opcao valida!\n");
        scanf("%d%*c", &opc);
    }
    time = clock();
    
    if (opc == 1) {
        quick_sort_Matricula(cadastro_E,0,cadastro->tamanho-1);
        copy_cadastro (cadastro_E,cadastro);
    }
    else {
        merge_sort_Matricula(cadastro_E,cadastro->tamanho);
        copy_cadastro (cadastro_E,cadastro);
    }
    time2 = clock();
    t = time2 - time;
    printf("Ordenado com sucesso!\n");
    printf("Tempo que levou para ordenar: %f segundos\n", t/CLOCKS_PER_SEC);
    
            
}

void entrada(Cadastro* cadastro){
    int mat, op;
    Pessoa *aux;

    clear_screen();
    if (cadastro_vazio(cadastro) == TRUE) return; 
    printf("| Entrada do restaurante |\n\n");
    printf("Qual a matricula da pessoa?\n");
    scanf("%d%*c", &mat);
    if (cadastro_vazio(cadastro) == TRUE) return;

    if (busca_sequencial(cadastro, mat) == FALSE) {
        printf("O usuario nao esta cadastrado!\n");
        printf("Deseja ir na administracao fazer o cadastro?\n");
        printf("1 - Sim\n2 - Nao\n");
        scanf("%d%*c", &op);
        if (op == 1) {
            printf("\n");
            cadastrar_pessoa(cadastro);
        }
        return;
    }
    
    if (verifica_creditos(cadastro, mat) == FALSE) {
        aux = retornar_pessoa(cadastro,mat);
        printf("%s nao possui creditos!\n", aux->nome);
        return;
    }
    aux = retornar_pessoa(cadastro,mat);
    aux->creditos--;
    printf("%s entrou no RU!\n", aux->nome);
    printf("Agora %s possui %d credito(s)!\n", aux->nome, aux->creditos);
    
}


void verificar_cardapio () {
    Cardapio cardapio;
    
    strcpy(cardapio.comida[0],"Segunda: Arroz branco, feijao carioca de caldo, alface, carne de panela e suco de goiaba");
    strcpy(cardapio.comida[1],"Terca: Arroz branco, feijao carioca de caldo, almeirao, estrogonofe de frango (file), batata palha e suco de abacaxi");
    strcpy(cardapio.comida[2],"Quarta: Arroz branco, feijao carioca de caldo, tomate, lasanha de carne e suco de acerola");
    strcpy(cardapio.comida[3],"Quinta: Arroz branco, feijao carioca de caldo, cenoura, vaca atolada e suco de caju");
    strcpy(cardapio.comida[4],"Sexta: Arroz branco, feijao tropeiro, batata, coxa e sobrecoxa (frango) e suco de limao");
                            
    int op, i, dia;
    do {
        Continue();
        clear_screen();
        printf("\t| Cardapio |\n\n");
        printf("\t1 - Mostrar cardapio da semana\n");
        printf("\t2 - Mostrar cardapio de um dia especifico\n");
        printf("\t0 - Voltar\n");
        scanf("%d%*c", &op);
        clear_screen();
        switch (op) {
            case 1:
                for (i = 0; i < TAM; i++) {
                    printf("%s\n", cardapio.comida[i]);               
                    if (i != TAM-1) printf("\n");
                }
                break;
            case 2:
                printf("Escolha o dia da semana\n0 - Segunda\n1 - Terca\n2 - Quarta\n3 - Quinta\n4 - Sexta\n");
                scanf("%d%*c", &dia);
                while (dia < 0 || dia > 4) {
                    printf("Insira um dia valido!\n");
                    scanf("%d%*c", &dia);
                }
                printf("%s\n", cardapio.comida[dia]);               
                break;
            default:
                if (op < 0 || op > 2) printf("Insira uma opcao valida!\n"); 
                break;
        }
    } while (op != 0);
    return;
}