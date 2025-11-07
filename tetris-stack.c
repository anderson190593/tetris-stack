#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Fila circular de peças futuras
typedef struct {
    Peca fila[TAMANHO_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Pilha linear de peças reservadas
typedef struct {
    Peca pilha[TAMANHO_PILHA];
    int topo;
} Pilha;

// Inicializa a fila
void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Inicializa a pilha
void inicializarPilha(Pilha* p) {
    p->topo = -1;
}

// Gera uma nova peça aleatória
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere uma peça na fila (enqueue)
int inserirNaFila(Fila* f, Peca nova) {
    if (f->quantidade == TAMANHO_FILA) return 0;
    f->fila[f->fim] = nova;
    f->fim = (f->fim + 1) % TAMANHO_FILA;
    f->quantidade++;
    return 1;
}

// Remove uma peça da fila (dequeue)
int removerDaFila(Fila* f, Peca* removida) {
    if (f->quantidade == 0) return 0;
    *removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAMANHO_FILA;
    f->quantidade--;
    return 1;
}

// Insere uma peça na pilha (push)
int inserirNaPilha(Pilha* p, Peca nova) {
    if (p->topo == TAMANHO_PILHA - 1) return 0;
    p->topo++;
    p->pilha[p->topo] = nova;
    return 1;
}

// Remove uma peça da pilha (pop)
int removerDaPilha(Pilha* p, Peca* removida) {
    if (p->topo == -1) return 0;
    *removida = p->pilha[p->topo];
    p->topo--;
    return 1;
}

// Exibe o estado atual da fila
void exibirFila(Fila* f) {
    printf("\n📦 Fila de peças:\n");
    int i = f->inicio;
    for (int count = 0; count < f->quantidade; count++) {
        printf("[%c %d] ", f->fila[i].nome, f->fila[i].id);
        i = (i + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// Exibe o estado atual da pilha
void exibirPilha(Pilha* p) {
    printf("🗄️ Pilha de reserva (Topo -> Base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->pilha[i].nome, p->pilha[i].id);
    }
    printf("\n");
}

// Exibe o estado completo
void exibirEstado(Fila* f, Pilha* p) {
    exibirFila(f);
    exibirPilha(p);
}

int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    int idGlobal = 0;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicial
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirNaFila(&fila, gerarPeca(idGlobal++));
    }

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        printf("\n🎮 Opções de ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        Peca manipulada;

        switch (opcao) {
            case 1:
                if (removerDaFila(&fila, &manipulada)) {
                    printf("🧩 Peça jogada: [%c %d]\n", manipulada.nome, manipulada.id);
                    inserirNaFila(&fila, gerarPeca(idGlobal++));
                } else {
                    printf("⚠️ Fila vazia!\n");
                }
                break;
            case 2:
                if (removerDaFila(&fila, &manipulada)) {
                    if (inserirNaPilha(&pilha, manipulada)) {
                        printf("📥 Peça reservada: [%c %d]\n", manipulada.nome, manipulada.id);
                        inserirNaFila(&fila, gerarPeca(idGlobal++));
                    } else {
                        printf("⚠️ Pilha cheia! Não é possível reservar.\n");
                        inserirNaFila(&fila, manipulada); // devolve à fila
                    }
                } else {
                    printf("⚠️ Fila vazia!\n");
                }
                break;
            case 3:
                if (removerDaPilha(&pilha, &manipulada)) {
                    printf("🧩 Peça usada da reserva: [%c %d]\n", manipulada.nome, manipulada.id);
                } else {
                    printf("⚠️ Pilha vazia! Nenhuma peça reservada.\n");
                }
                break;
            case 0:
                printf("👋 Encerrando o jogo. Até a próxima!\n");
                break;
            default:
                printf("❌ Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}