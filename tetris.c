// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACIDADE_MAX 10   
#define TAMANHO_INICIAL 5   

// Cada peça do Tetris tem um tipo e um ID único.
typedef struct {
    char nome;   // Ex.: I, O, T, L...
    int id;
} Peca;

// Fila circular para armazenar as peças
typedef struct {
    Peca itens[CAPACIDADE_MAX];
    int inicio;
    int fim;
    int quantidade;
} FilaDePecas;

int contadorGlobalId = 0;

// Funções
Peca gerarPeca();
void inicializarFila(FilaDePecas *f);
int filaCheia(FilaDePecas *f);
int filaVazia(FilaDePecas *f);
void enfileirar(FilaDePecas *f);
void desenfileirar(FilaDePecas *f);
void exibirFila(FilaDePecas f);

int main() {
    srand(time(NULL));

    FilaDePecas fila;
    int opcao = -1;

    inicializarFila(&fila);

    while (opcao != 0) {
        printf("\n=======================================\n");
        printf("        TETRIS STACK - FILA DE PEÇAS     \n");
        printf("====================================\n");

        exibirFila(fila);

        printf("\n1 - Jogar peça(dequeue)\n");
        printf("2 - Adicionar nova peça(enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar(&fila);
                break;
            case 2:
                enfileirar(&fila);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}

Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'};

    int indice = rand() % 7;

    p.nome = tipos[indice];
    p.id = contadorGlobalId++;

    return p;
}

void inicializarFila(FilaDePecas *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;

    printf("Inicializando fila com %d peças...\n", TAMANHO_INICIAL);

    for (int i = 0; i < TAMANHO_INICIAL; i++) {
        enfileirar(f);
    }
}

int filaCheia(FilaDePecas *f) {
    return f->quantidade == CAPACIDADE_MAX;
}

int filaVazia(FilaDePecas *f) {
    return f->quantidade == 0;
}

// Enfileira uma nova peça
void enfileirar(FilaDePecas *f) {
    if (filaCheia(f)) {
        printf("\n[ERRO] Fila cheia!\n");
        return;
    }

    Peca nova = gerarPeca();

    f->itens[f->fim] = nova;
    f->fim = (f->fim + 1) % CAPACIDADE_MAX;
    f->quantidade++;

    if (f->quantidade > TAMANHO_INICIAL) {
        printf("\n >> Peça [%c %d] adicionada.\n", nova.nome, nova.id);
    }
}

// Remove a peça do início
void desenfileirar(FilaDePecas *f) {
    if (filaVazia(f)) {
        printf("\n[ERRO] Fila vazia!\n");
        return;
    }

    Peca jogada = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % CAPACIDADE_MAX;
    f->quantidade--;

    printf("\n >> Você jogou [%c %d].\n", jogada.nome, jogada.id);
}

void exibirFila(FilaDePecas f) {
    if (f.quantidade == 0) {
        printf("Fila: [ VAZIA ]\n");
        return;
    }

    printf("Fila de peças: ");

    int i = f.inicio;
    for (int count = 0; count < f.quantidade; count++) {
        printf("[%c %d] ", f.itens[i].nome, f.itens[i].id);
        i = (i + 1) % CAPACIDADE_MAX;
    }

    printf("\n");
}
