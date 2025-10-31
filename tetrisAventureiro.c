#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define MAX_RESERVA 3

typedef struct{
    char nome; // apenas um caractere: 'I', 'O', 'T', 'L'
    int id;
} Peca;

typedef struct{
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
}Fila;

typedef struct {
    Peca reserva[MAX_RESERVA];
    int topo;
} Pilha;
//Iniciando fila
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}
//Iniciando pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

//Gerando peças automaticamente 
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    static int contador = 0;

    p.nome = tipos[rand() % 4];
    p.id = contador++;
    return p;
}
//Funções fila
int filaCheia(Fila *f){
    return f->total == MAX;
}

int filaVazia(Fila *f){
    return f->total == 0;
}

//Inserindo item na fila
void inserir(Fila *f, Peca p){
    if (filaCheia(f)){
       printf("Fila cheia! Não é possivel inserir\n");
       return;
    }
    f->itens[f->fim] = p;
    f->fim =(f->fim +1 ) % MAX;
    f->total++;
}
//Remove item da fila
void remover(Fila *f, Peca *p){
    if (filaVazia(f)){
        printf("Fila vazia! Não é possivel remover\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio =(f->inicio +1 ) % MAX;
    f->total--;
    
}

//Funções pilha
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_RESERVA - 1;
}

//Inserindo item na pilha
void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível inserir.\n");
        return;
    }
 
    p->topo++;
    p->reserva[p->topo] = nova;
}

//Remover item da pilha
void pop(Pilha *p, Peca *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Não é possível remover.\n");
        return;
    }

    *removida = p->reserva[p->topo];
    p->topo--;
}

//Mostrar os itens da fila e pilha
void mostrarEstado(Fila *f,Pilha *p) {
    printf("\nFila:");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX){
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }

    printf("\nPilha (topo -> base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d]\n", p->reserva[i].nome, p->reserva[i].id);
    }
    printf("\n");
}
//Menu
int main() {
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    srand(time(NULL)); // inicializa aleatoriedade

    // Preenche a fila inicialmente
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca());
    }

    int opcao;
    Peca p;
    Peca removida;

    do {
        mostrarEstado(&fila, &pilha);
        printf("\nTetris Stack\n");
        printf("1.Jogar peça\n");
        printf("2.Reservar peça\n");
        printf("3. Usar peça reserva\n");
        printf("0.Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                remover(&fila, &p);
                printf("Peça jogada: [%c %d]\n", p.nome, p.id);
                inserir(&fila, gerarPeca());

                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 2:
                if (!filaVazia(&fila)) {
                remover(&fila, &p);
                if (!pilhaCheia(&pilha)) {
                    push(&pilha, p);
                    printf("Peça reservada: [%c %d]\n", p.nome, p.id);
                } else {
                    printf("Pilha cheia! Não é possível reservar.\n");
                    inserir(&fila, p); // devolve à fila
                }
                inserir(&fila, gerarPeca());
                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 3:
                if (!pilhaVazia(&pilha)) {
                pop(&pilha, &removida);
                printf("Peça usada da reserva: [%c %d]\n", removida.nome, removida.id);

                } else {
                    printf("Pilha vazia! Nenhuma peça reservada.\n");
                }
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);


    return 0;
}