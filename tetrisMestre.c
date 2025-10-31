#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define MAX_RESERVA 3

typedef struct{
    char nome; // apenas um caractere: 'I', 'O', 'T', 'L'
    int id;
} Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int qtd;
} Fila;

typedef struct {
    Peca dados[MAX];
    int topo;
} Pilha;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}
 
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int filaCheia(Fila *f) {
    return f->qtd == MAX;
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_RESERVA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
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
//Inserindo item na fila
void inserir(Fila *f, Peca p) {
    if (f->qtd < MAX) {
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % MAX;
        f->qtd++;
    }
}
//Removendo item da fila
Peca remover(Fila *f) {
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;
    return p;
}
//Inserindo item na pilha 
void push(Pilha *p, Peca pes) {
    if (p->topo < MAX - 1) {
        p->dados[++p->topo] = pes;
    }
}
//Removenod item da pilha
Peca pop(Pilha *p) {
    return p->dados[p->topo--];
}

//Mostrar os itens da fila e pilha
void mostrarEstado(Fila f,Pilha *p) {
    printf("\nFila de peças\t");
    for (int i = 0; i < f.qtd; i++) {
    int idx = (f.inicio + i) % MAX;
    printf("[%c %d] ", f.itens[idx].nome, f.itens[idx].id);
    }

    printf("\nPilha de reserva (Topo -> base): ");
    for (int i = p->topo; i >= 0; i--) {
    printf("[%c %d] ", p->dados[i].nome, p->dados[i].id);
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
        mostrarEstado(fila, &pilha);
        printf("\nTetris Stack\n");
        printf("1. Jogar peça\n");
        printf("2. Reservar peça\n");
        printf("3. Usar peça reserva\n");
        printf("4. Exibir estado atual\n");
        printf("5. Trocar peça atual\n");
        printf("6. Troca multipla (trocar as tres peças reservas)\n");
        printf("0.Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                p = remover(&fila);
                printf("Peça jogada: [%c %d]\n", p.nome, p.id);
                inserir(&fila, gerarPeca());

                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 2:
                if (!filaVazia(&fila)) {
                p = remover(&fila);
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
                removida = pop(&pilha);
                inserir(&fila, removida);
                printf("Peça usada da reserva: [%c %d]\n", removida.nome, removida.id);

                } else {
                    printf("Pilha vazia! Nenhuma peça reservada.\n");
                }
                break;

            case 4:
                mostrarEstado(fila, &pilha);
                break;

            case 5:
                if (!filaVazia(&fila) && !pilhaVazia(&pilha)) {
                //Trocando a peça da frente da fila com o topo da pilha
                int idx = fila.inicio;
                Peca temp = fila.itens[idx];
                fila.itens[idx] = pilha.dados[pilha.topo];
                pilha.dados[pilha.topo] = temp;
                printf("Troca realizada entre frente da fila e topo da pilha.\n");
                } else {
                    printf("Não foi possível realizar a troca.\n");
                }
                break;
            
            case 6:
                if (fila.qtd >= 3 && pilha.topo >= 2) {
                //Salvar os 3 primeiros da fila
                Peca tempFila[3];
                for (int i = 0; i < 3; i++) {
                int idx = (fila.inicio + i) % MAX;
                tempFila[i] = fila.itens[idx];
                }

                //Copiar os 3 da pilha para a fila (mantém ordem)
                for (int i = 0; i < 3; i++) {
                int idx = (fila.inicio + i) % MAX;
                fila.itens[idx] = pilha.dados[pilha.topo - i];
                }

                //Copiar os salvos da fila para a pilha (invertidos)
                for (int i = 0; i < 3; i++) {
                pilha.dados[pilha.topo - i] = tempFila[2 - i];
                }

                printf("Troca múltipla realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
                } else {
                    printf("Não há peças suficientes para troca múltipla.\n");
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