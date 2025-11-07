🧩 Tetris Stack – Gerenciador Avançado de Peças em C
Este projeto simula o gerenciamento estratégico de peças no jogo Tetris Stack, utilizando estruturas de dados fundamentais: fila circular e pilha linear. O sistema permite ao jogador executar ações como jogar, reservar, recuperar e realizar trocas entre peças, consolidando conceitos de lógica, modularização e controle de fluxo em C.

🎯 Objetivo
Desenvolver um sistema interativo em C que gerencia peças do jogo Tetris Stack com base em estruturas de dados. O jogador pode manipular peças entre fila e pilha, realizar trocas diretas ou múltiplas e acompanhar o estado atual do jogo em tempo real.

🛠️ Tecnologias Utilizadas
- Linguagem: C
- Bibliotecas: stdio.h, stdlib.h, time.h
- Ferramentas: compilador GCC ou qualquer ambiente C compatível

🧱 Estrutura do Código
O projeto é modularizado em funções específicas para facilitar manutenção, clareza e expansão:
|  |  | 
| main() |  | 
| inicializarFila()inicializarPilha() |  | 
| gerarPeca() |  | 
| inserirNaFila()removerDaFila() |  | 
| inserirNaPilha()removerDaPilha() |  | 
| trocarTopoComFrente() |  | 
| trocaMultipla() |  | 
| exibirEstado() |  | 



📦 Estrutura das Peças
Cada peça é representada por uma struct com os seguintes campos:
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;



🔍 Funcionalidades
- Fila circular com 5 posições
- Pilha linear com 3 posições
- Geração automática de peças
- Ações disponíveis:
- Jogar peça da fila
- Reservar peça na pilha
- Usar peça da pilha
- Trocar frente da fila com topo da pilha
- Troca múltipla entre fila e pilha
- Exibição clara do estado atual
- Menu interativo com validações

🧪 Como Executar
- Clone o repositório:
git clone https://github.com/seu-usuario/tetris-stack-avancado.git
cd tetris-stack-avancado
- Compile o código:
gcc tetris.c -o tetris
- Execute o jogo:
./tetris



📚 Aprendizado
Este projeto reforça conceitos fundamentais como:
- Fila circular e pilha linear
- Modularização e clareza de código
- Controle de fluxo com operadores lógicos
- Manipulação de structs e arrays
- Simulação de lógica de jogos em C

📄 Licença
Este projeto está licenciado sob a MIT License.
