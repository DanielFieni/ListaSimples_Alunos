#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//|=============== STRUCT ===============|
typedef struct tipoNo {
    char nome[20];
    int matricula;
    float nota;
    struct tipoNo *prox;
}TNo;

typedef struct tipoLista {
    int total;
    TNo *inicio;
    TNo *fim;
}TLista;
//|======================================|

int menu();
void inicializar(TLista *L);
void inserir(TLista *L);
void remover(TLista *L);
void listarNome(TLista *L);
void exibe(TNo *atual);
void listar(TLista *L);
void listarNota(TLista *L);

TLista lista;

void main(){
   int op;
   inicializar(&lista);
    do{
        op = menu();
        switch (op)
        {
        case 0:
            //Sair
            break;
        case 1:
            //inserir
            inserir(&lista);
            break;
        case 2:
            //remover
            remover(&lista);
            break;
        case 3:
            //Listar por nome
            listarNome(&lista);
            listar(&lista);
            system("PAUSE");
            break;
        case 4:
            //Lista por nota
            listarNota(&lista);
            listar(&lista);
            system("PAUSE");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente\n\n");
            system("PAUSE");
            break;
        }
    }while (op != 0);
}

//|=============== FUNCOES ===============|
int menu(){
    int opcao;
    system("@cls||clear");
    printf("\n\n");
    printf("\t|============== MENU ==============|\n");
    printf("\t0 - SAIR (Sair da aplicacao)\n");
    printf("\t1 - INSERIR\n");
    printf("\t2 - REMOVER\n");
    printf("\t3 - LISTAR POR NOME\n");
    printf("\t4 - LISTAR POR NOTA\n");
    printf("Escolha uma opcao: ");
    scanf("%d" ,&opcao);
    return opcao;
}

//|======================================|
void inicializar(TLista *L){
    L->inicio = NULL;
    L->fim = NULL;
    L->total = 0;
}
//|======================================|
void inserir(TLista *L){
    TNo *novo = (TNo *)malloc(sizeof(TNo));
    printf("\n\t|========= INSERIR ALUNO =========|\n");
    printf("Insira o NOME: ");
    scanf(" %20[^\n]s" ,&novo->nome);
    printf("Insira a MATRICULA: ");
    scanf("%d" ,&novo->matricula);
    printf("Insira a NOTA: ");
    scanf("%f" ,&novo->nota);

    novo->prox = NULL;

    if(L->inicio == NULL){
        L->inicio = novo;
        L->fim = novo;
    } else {
        TNo *atual = L->inicio;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    L->total++;
}
//|======================================|
void remover(TLista *L){
    if(L->inicio == NULL){
        printf("\n\nSEM ELEMENTOS PARA EXCLUIR\n");
        system("PAUSE");
    } else {
        TNo *atual = L->inicio, *anterior = NULL, *proximo = NULL;
        int matricula, encontrado = 0;

        printf("\n\t|========= EXCLUIR ALUNO =========|\n");
        printf("Insira a MATRICULA: ");~
        scanf("%d" ,&matricula);
        
        while(atual != NULL){
            if(atual->matricula == matricula){
                encontrado = 1;
                proximo = atual->prox;
                if(anterior == NULL){
                    //Excluir a matricula da primeira posicao da fila
                    L->inicio = proximo;
                    if(L->inicio == NULL) L->fim = NULL;
                } else {
                    //Exclui a matricula de qualquer lugar da fila
                    anterior->prox = proximo;
                }
                L->total--;
                free(atual); //Devolver o espaço para a memoria
                break;
            }
            anterior = atual;
            atual = atual->prox;
        }
        if(!encontrado){
            //Se a matricula nao for encontrada
            printf("\n\n\tERROR! Matricula inexistente\n");
            printf("\tTente novamente\n\n");
            system("PAUSE");
        }
    }
}

//|======================================|
void troca(TNo *novo, TNo *proximo){
	TNo *aux = (TNo *)malloc(sizeof(TNo));
	
	strcpy(aux->nome, proximo->nome); // aux = novo
	aux->matricula = proximo->matricula;
    aux->nota = proximo->nota;
	
	strcpy(proximo->nome, novo->nome); // proximo = novo
	proximo->matricula = novo->matricula;
    proximo->nota = novo->nota;
	
	strcpy(novo->nome, aux->nome); // novo = aux
	novo->matricula = aux->matricula;
	novo->nota = aux->nota;
}

void listarNome(TLista *L){
    int contadorTroca = 0;
    if(L->inicio == NULL){
        printf("\n\nSEM ELEMENTOS PARA LISTAR\n");
    } else {
        TNo *novo = L->inicio;
        TNo *proximo = novo->prox;
        
        while (proximo != NULL){
            if(strcmp(novo->nome,proximo->nome) > 0){
                troca(novo , proximo);
                contadorTroca++;
            }//if
            novo = novo->prox;
            proximo = proximo->prox; 
        }//while
    }//if ... else
    if(contadorTroca != 0){
        listarNome(L);
    }
}
//|======================================|
void listarNota(TLista *L){
    int contadorTroca = 0;
    if(L->inicio == NULL){
        printf("\n\nSEM ELEMENTOS PARA LISTAR\n");
    } else {
        TNo *novo = L->inicio, *proximo = novo->prox;
        while(proximo != NULL){
            if(novo->nota > proximo->nota){
                troca(novo, proximo);
                contadorTroca++;
            }//if
            novo = novo->prox;
            proximo = proximo->prox;
        }//while
    }//if...else
    if(contadorTroca != 0){
        listarNota(L);
    }
}

//|======================================|
void exibe(TNo *atual){
	printf("\n+-------NOME--------+\t+-------NOTA--------+\t+-------MATRICULA-----+");
	printf("\n        %s\t\t        %.2f\t\t        %d\n",atual->nome, atual->nota, atual->matricula);
	printf("_____________________________________________________________________\n");
}

void listar(TLista *L){
	TNo *atual = L->inicio;
	printf("\n");
	while(atual != NULL){
		exibe(atual);
		atual = atual->prox;
	}//while
	printf("\n\n");
}


