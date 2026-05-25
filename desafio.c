#include <stdio.h>
#include <stdlib.h>

//struct da peca
typedef struct{
    char tipo;
    int id;
} Peca;

#define MAX 5

//struct da fila circular
typedef struct{
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
}Fila;

//inicia a fila
void iniciar(Fila *f){
    f->inicio = 0;
    f->fim = -1;
    f->total = 0; 
}

//verifica se a fila esta cheia
int filaCheia(Fila *f){
    return f->total == MAX;
}

//verifica se a fila esta vazia
int filaVazia(Fila *f){
    return f->total == 0;
}

//gera a peca 
Peca gerarPeca(int id){
    Peca p;

    char forma[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;

    p.tipo = forma[indice];
    p.id = id;

    return p;
}

//insere a peca
void inserir(Fila *f, Peca p){
    if(FilaCheia(f)){
        printf("Fila cheia. Nao é possivel inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1)% MAX;
    f->total++;
    printf("Peça inserida com sucesso\n");
}

//remove a peca
void remover(Fila *f, Peca *p){
    if(FilaVazia(f)){
        printf("Fila Vazia. Impossivel remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1)% MAX;
    f->total--;
}

//mostra o estado da fila
void mostrarFila(Fila *f){
    printf("Fila atual: ");

    int i;
    int indice = f->inicio;

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1)% MAX){
        printf("[%s, %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }
    printf("\n");
}

int main(){
    Fila fila;
    int opcao;
    int contadorID = 1;

    srand(time(NULL));

    iniciaFila(&fila);

    //inicia fila com pecas
    for(int i = 0; 0 < MAX; i++){
        inserir(&fila, gerarPeca(contadorID));
        contadorID++;
    }

    do{
        exibirFila(&fila);
    printf("Movendo pecas de tetris!\n");
    printf("1. Jogar peca\n");
    printf("2. Inserir nova peca\n");
    printf("0. Sair.\n");
    printf("Escolha a opcao que deseja: \n");
    scanf("%d", &opcao);

    switch (opcao){
    case 1:
        remover(&fila);
        break;
    
    case 2:
        inserir(&fila, gerarPeca(contadorID));
        contadorID++;
        break;
    
    case 0:
        printf("\nSaindo...\n");
        break;

    default:
        printf("\nOpcao invalida\n");
    }
} while (opcao != 3);

return 0;
}