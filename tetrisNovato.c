#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
//Estruta das peças
typedef struct{
    char nome; // apenas um caractere: 'I', 'O', 'T', 'L'
    int id;
} Peca;
//Estruta da fila
typedef struct{
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
}Fila;
//Inicializar a fila
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}
//Verifica se a fila esta cheia
int filaCheia(Fila *f){
    return f->total == MAX;
}
//Verifica se a fila esta vazia
int filaVazia(Fila *f){
    return f->total == 0;
}
//Gerando peças de forma aleatoria sem precisar inserir manualmente 
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    static int contador = 0;

    p.nome = tipos[rand() % 4];
    p.id = contador++;
    return p;
}
//Inserir a peça na fila
void inserir(Fila *f, Peca p){
    if (filaCheia(f)){
       printf("\nFila cheia! Não é possivel inserir\n");
       return;
    }
    f->itens[f->fim] = p;
    f->fim =(f->fim +1 ) % MAX;
    f->total++;
}
//Remover a peça na fila
void remover(Fila *f, Peca *p){
    if (filaVazia(f)){
        printf("Fila vazia! Não é possivel remover\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio =(f->inicio +1 ) % MAX;
    f->total--;
    
}
//Visualizar a lista 
void mostraFila(Fila *f){
    printf("\nFila:");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX){
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL)); // inicializa aleatoriedade

    int opcao;
    Peca p;
    //Menu
    do {
        mostraFila(&fila);//Conforme for adicionando ou removendo aqui iria mostrar as peças
        printf("\nTetris Stack\n");
        printf("1.Jogar peça\n");
        printf("2.Inserir nova peça\n");
        printf("0.Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                remover(&fila, &p);
                printf("Peça jogada: [%c %d]\n", p.nome, p.id);
                break;
            case 2:
                p = gerarPeca();
                inserir(&fila, p);
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