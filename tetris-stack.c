#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Estrutura da peça
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Fila circular
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Pilha linear
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo;
} Pilha;

// Inicializa fila
void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Inicializa pilha
void inicializarPilha(Pilha* p) {
    p->topo = -1;
}

// Gera peça aleatória
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Enfileira peça
int inserirNaFila(Fila* f, Peca nova) {
    if (f->quantidade == TAM_FILA) return 0;
    f->fila[f->fim] = nova;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
    return 1;
}

// Remove da fila
int removerDaFila(Fila* f, Peca* removida) {
    if (f->quantidade == 0) return 0;
    *removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return 1;
}

// Insere na pilha
int inserirNaPilha(Pilha* p, Peca nova) {
    if (p->topo == TAM_PILHA - 1) return 0;
    p->topo++;
    p->pilha[p->topo] = nova;
    return 1;
}

// Remove da pilha
int removerDaPilha(Pilha* p, Peca* removida) {
    if (p->topo == -1) return 0;
    *removida = p->pilha[p->topo];
    p->topo--;
    return 1;
}

// Exibe fila
void exibirFila(Fila* f) {
    printf("\n📦 Fila de peças:\n");
    int i = f->inicio;
    for (int count = 0; count < f->quantidade; count++) {
        printf("[%c %d] ", f->fila[i].nome, f->fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

// Exibe pilha
void exibirPilha(Pilha* p) {
    printf("🗄️ Pilha de reserva (Topo -> Base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->pilha[i].nome, p->pilha[i].id);
    }
    printf("\n");
}

// Troca peça da frente da fila com topo da pilha
int trocarTopoComFrente(Fila* f, Pilha* p) {
    if (f->quantidade == 0 || p->topo == -1) return 0;
    int frente = f->inicio;
    Peca temp = f->fila[frente];
    f->fila[frente] = p->pilha[p->topo];
    p->pilha[p->topo] = temp;
    return 1;
}

// Troca múltipla entre 3 da fila e 3 da pilha
int trocaMultipla(Fila* f, Pilha* p) {
    if (f->quantidade < 3 || p->topo < 2) return 0;
    for (int i = 0; i < 3; i++) {
        int posFila = (f->inicio + i) % TAM_FILA;
        Peca temp = f->fila[posFila];
        f->fila[posFila] = p->pilha[p->topo - i];
        p->pilha[p->topo - i] = temp;
    }
    return 1;
}

// Exibe estado completo
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

    // Preenche fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        inserirNaFila(&fila, gerarPeca(idGlobal++));
    }

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        printf("\n🎮 Opções disponíveis:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
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
                }
                break;
            case 3:
                if (removerDaPilha(&pilha, &manipulada)) {
                    printf("🧩 Peça usada da reserva: [%c %d]\n", manipulada.nome, manipulada.id);
                } else {
                    printf("⚠️ Pilha vazia!\n");
                }
                break;
            case 4:
                if (trocarTopoComFrente(&fila, &pilha)) {
                    printf("🔄 Troca realizada entre frente da fila e topo da pilha.\n");
                } else {
                    printf("⚠️ Troca impossível. Verifique se há peças suficientes.\n");
                }
                break;
            case 5:
                if (trocaMultipla(&fila, &pilha)) {
                    printf("🔁 Troca múltipla realizada com sucesso!\n");
                } else {
                    printf("⚠️ Troca múltipla não permitida. Verifique se há 3 peças em cada estrutura.\n");
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