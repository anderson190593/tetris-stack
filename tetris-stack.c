#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Fila circular de peças
typedef struct {
    Peca fila[TAMANHO_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Função que inicializa a fila
void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Função que gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Função para inserir uma peça no final da fila (enqueue)
int inserirPeca(Fila* f, Peca nova) {
    if (f->quantidade == TAMANHO_FILA) {
        printf("⚠️ Fila cheia! Não é possível inserir nova peça.\n");
        return 0;
    }
    f->fila[f->fim] = nova;
    f->fim = (f->fim + 1) % TAMANHO_FILA;
    f->quantidade++;
    return 1;
}

// Função para remover a peça da frente da fila (dequeue)
int jogarPeca(Fila* f) {
    if (f->quantidade == 0) {
        printf("⚠️ Fila vazia! Nenhuma peça para jogar.\n");
        return 0;
    }
    Peca removida = f->fila[f->inicio];
    printf("🧩 Peça jogada: [%c %d]\n", removida.nome, removida.id);
    f->inicio = (f->inicio + 1) % TAMANHO_FILA;
    f->quantidade--;
    return 1;
}

// Função para exibir o estado atual da fila
void exibirFila(Fila* f) {
    printf("\n📦 Fila de peças:\n");
    int i = f->inicio;
    for (int count = 0; count < f->quantidade; count++) {
        printf("[%c %d] ", f->fila[i].nome, f->fila[i].id);
        i = (i + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// Função principal com menu interativo
int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    Fila fila;
    inicializarFila(&fila);

    int idGlobal = 0;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirPeca(&fila, gerarPeca(idGlobal++));
    }

    int opcao;
    do {
        exibirFila(&fila);
        printf("\n🎮 Opções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                if (inserirPeca(&fila, gerarPeca(idGlobal++))) {
                    printf("✅ Nova peça inserida com sucesso.\n");
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