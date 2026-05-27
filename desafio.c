#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//struct da peca
typedef struct{
    char tipo;
    int id;
} Peca;

#define MAX_FILA 5
#define MAX_PILHA 3

//struct da fila circular
typedef struct{
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
}Fila;

//struct da pilha
typedef struct{
    Peca itens[MAX_PILHA];
    int topo;
}Pilha;

//inicia a fila
void iniciar(Fila *f){
    f->inicio = 0;
    f->fim = -1;
    f->total = 0; 
}

//verifica se a fila esta cheia
int filaCheia(Fila *f){
    return f->total == MAX_FILA;
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
    if(filaCheia(f)){
        printf("Fila cheia. Nao é possivel inserir.\n");
        return;
    }
    f->fim = (f->fim + 1)% MAX_FILA;
    f->itens[f->fim] = p;
    f->total++;
    printf("Peça inserida com sucesso\n");
}

//remove a peca
Peca remover(Fila *f){
    Peca removida;

    if(filaVazia(f)){
        printf("A fila esta vazia\n");
        removida.tipo = 'x';
        removida.id = -1;

        return removida;
    }

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1)% MAX_FILA;
    f->total--;

    return removida;
}

//mostra o estado da fila
void mostrarFila(Fila *f){
    printf("Fila atual: \n");

    int i;
    int indice = f->inicio;

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1)% MAX_FILA){
        printf("[%c, %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }
    printf("\n");
}

//inicia a pilha 
void iniciarPilha(Pilha *p){
    p->topo = -1;
}

//verifica pilha cheia
int pilhaCheia(Pilha *p){
    return p->topo == MAX_PILHA - 1;
}

//verifica pilha vazia
int pilhaVazia(Pilha *p){
    return p->topo == -1;
}

//empilha
void empilhar(Pilha *p, Peca peca){
    if (pilhaCheia(p)){
        printf("Pilha cheia!\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = peca;
}

//desempilha
Peca pop(Pilha *p){
    Peca removida;

    if (pilhaVazia(p)){
        printf("Pilha vazia!\n");

        removida.tipo = 'x';
        removida.id = -1;

        return removida;
    }
    removida = p->itens[p->topo];
    p->topo--;

    return removida;
}

//mostra estado da pilha
void mostrarPilha(Pilha *p){
    printf("Pecas reservas: \n");
    
    for (int i = p->topo; i >= 0; i--){
        printf("[%c, %d]", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}

int main(){
    Fila fila;
    Pilha reserva;
    int opcao;
    int contadorID = 1;

    srand(time(NULL));

    iniciar(&fila);
    iniciarPilha(&reserva); 

    //inicia fila com pecas
    for(int i = 0; i < MAX_FILA; i++){
        inserir(&fila, gerarPeca(contadorID));
        contadorID++;
    }

    do{
        mostrarFila(&fila);
        mostrarPilha(&reserva);
    printf("Movendo pecas de tetris!\n");
    printf("1. Jogar peca\n");
    printf("2. Reservar peca\n");
    printf("3. Usar peca reservada\n");
    printf("0. Sair.\n");
    printf("Escolha a opcao que deseja: ");
    scanf("%d", &opcao);
    printf("\n\n2");

    switch (opcao){
    case 1:{
        Peca jogada = remover(&fila);

        if(jogada.id != -1){
            printf("Peca jogada: [%c, %d]\n", jogada.tipo, jogada.id);

            inserir (&fila, gerarPeca(contadorID));
            contadorID++;
        }
        break;
    }

    case 2:{
        if (pilhaCheia(&reserva)){
            printf("\nReserva Cheia\n");
            break;
        }
        Peca reservada = remover(&fila);
        if(reservada.id != -1){
            empilhar(&reserva, reservada);

            inserir(&fila, gerarPeca(contadorID));
            contadorID++;
        }
        break;
    }

    case 3: {
        Peca usada = pop(&reserva);
        if (usada.id != 1){
            printf("Peca reservada usada: [%c, %d]\n", usada.tipo, usada.id);
        }
        break;
    }
    case 0:
        printf("\nSaindo...\n");
        break;

    default:
        printf("\nOpcao invalida\n");
    }
} while (opcao != 0);

return 0;
}