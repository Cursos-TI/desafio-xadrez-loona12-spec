/*----------------------------------------------
                BIBLIOTECAS
----------------------------------------------*/
#include <stdio.h>   // Para funções de I/O (printf, etc.)
#include <stdbool.h> // Para uso de booleanos (não usado aqui, mas útil para expansões), Booleanos são um tipo de dado que representa valores lógicos, ou seja, apenas dois estados possíveis: true ou false

/*----------------------------------------------
                CONSTANTES
----------------------------------------------*/
#define TAMANHO_TABULEIRO 8 // Define o tamanho 8x8 do tabuleiro de xadrez

/*----------------------------------------------
        FUNÇÃO: imprimirTabuleiro()
        OBJETIVO: Mostrar o tabuleiro formatado
----------------------------------------------*/
void imprimirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n   +---+---+---+---+---+---+---+---+\n"); // Linha superior do tabuleiro
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d  |", i+1); // Número da linha (1-8)
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Substitui espaços vazios por '.' para melhor visualização
            printf(" %c |", tabuleiro[i][j] == ' ' ? '.' : tabuleiro[i][j]);
        }
        printf("\n   +---+---+---+---+---+---+---+---+\n"); // Linha divisória
    }
    printf("     a   b   c   d   e   f   g   h\n\n"); // Coordenadas das colunas
}

/*----------------------------------------------
        FUNÇÃO: moverTorreRecursivo()
        OBJETIVO: Movimentar a Torre em linha reta (horizontal/vertical)
        LÓGICA: Recursão até 'casas' chegar a 0
----------------------------------------------*/
void moverTorreRecursivo(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, char direcao, int casas) {
    if (casas == 0) return; // Condição de parada da recursão
    
    tabuleiro[x][y] = ' '; // Limpa a posição atual

    if (direcao == 'H') { // Horizontal (direita)
        y++;
        printf("Torre move para direita → (%c%d)\n", 'a'+y, x+1); // Notação xadrez (ex: b1)
    } else if (direcao == 'V') { // Vertical (baixo)
        x++;
        printf("Torre move para baixo ↓ (%c%d)\n", 'a'+y, x+1);
    }

    tabuleiro[x][y] = 'T'; // Atualiza nova posição
    imprimirTabuleiro(tabuleiro); // Mostra o tabuleiro após cada movimento
    moverTorreRecursivo(tabuleiro, x, y, direcao, casas - 1); // Chamada recursiva
}

/*----------------------------------------------
        FUNÇÃO: moverBispoRecursivo()
        OBJETIVO: Movimentar o Bispo na diagonal
        OBS: Alterna entre ↖ e ↘ quando chega nas bordas
----------------------------------------------*/
void moverBispoRecursivo(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, int casas) {
    if (casas == 0) return;
    
    tabuleiro[x][y] = ' ';

    // Verifica limites do tabuleiro para mudar direção
    if (x > 0 && y > 0) { // Diagonal superior esquerda
        x--; y--;
        printf("Bispo move para diagonal superior esquerdo ↖ (%c%d)\n", 'a'+y, x+1);
    } else if (x < TAMANHO_TABULEIRO - 1 && y < TAMANHO_TABULEIRO - 1) { // Diagonal inferior direita
        x++; y++;
        printf("Bispo move para diagonal inferior direito ↘ (%c%d)\n", 'a'+y, x+1);
    }

    tabuleiro[x][y] = 'B';
    imprimirTabuleiro(tabuleiro);
    moverBispoRecursivo(tabuleiro, x, y, casas - 1);
}

/*----------------------------------------------
        FUNÇÃO: moverRainhaRecursivo()
        OBJETIVO: Movimentar a Rainha (igual à Torre, mas poderia ser estendido)
        OBS: Rainha = Torre + Bispo (neste código só implementamos movimento linear)
----------------------------------------------*/
void moverRainhaRecursivo(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, char direcao, int casas) {
    if (casas == 0) return;

    tabuleiro[x][y] = ' ';

    if (direcao == 'H') { // Horizontal
        y++;
        printf("Rainha move para direita → (%c%d)\n", 'a'+y, x+1);
    } else if (direcao == 'V') { // Vertical
        x++;
        printf("Rainha move para baixo ↓ (%c%d)\n", 'a'+y, x+1);
    }

    tabuleiro[x][y] = 'Q';
    imprimirTabuleiro(tabuleiro);
    moverRainhaRecursivo(tabuleiro, x, y, direcao, casas - 1);
}

/*----------------------------------------------
        FUNÇÃO: moverCavalo()
        OBJETIVO: Movimentar o Cavalo em L (usando loops)
        DIFERENÇA: Única função não-recursiva (usa ponteiros para alterar x,y)
----------------------------------------------*/
void moverCavalo(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* x, int* y) {
    tabuleiro[*x][*y] = ' ';

    printf("\nMovimento do Cavalo:\n");
    // Loop externo: 2 movimentos para cima
    for (int i = 0; i < 2; i++) {
        printf("Cavalo move para cima ↑ (%c%d)\n", 'a'+*y, *x);
        (*x)--; // Decrementa a linha
        
        // Loop interno: 1 movimento para direita
        for (int j = 0; j < 1; j++) {
            printf("Cavalo move para direita → (%c%d)\n", 'a'+*y, *x+1);
            (*y)++; // Incrementa a coluna
        }
    }

    tabuleiro[*x][*y] = 'C';
    imprimirTabuleiro(tabuleiro);
}

/*----------------------------------------------
        FUNÇÃO PRINCIPAL
----------------------------------------------*/
int main() {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicialização do tabuleiro vazio
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = ' '; // Preenche com espaços
        }
    }

    // Posicionamento inicial das peças:
    tabuleiro[0][0] = 'T'; // Torre na casa a1
    tabuleiro[0][1] = 'B'; // Bispo na casa b1
    tabuleiro[0][2] = 'Q'; // Rainha na casa c1
    tabuleiro[1][1] = 'C'; // Cavalo na casa b2

    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(tabuleiro);

    // Demonstração de movimentos:
    printf("\nMovendo a torre para a horizontal:\n");
    moverTorreRecursivo(tabuleiro, 0, 0, 'H', 3); // Torre 3 casas →

    printf("\nMovendo o bispo (diagonal inferior direito):\n");
    moverBispoRecursivo(tabuleiro, 0, 1, 3); // Bispo 3 casas ↘

    printf("\nMovendo a rainha (horizontal):\n");
    moverRainhaRecursivo(tabuleiro, 0, 2, 'H', 3); // Rainha 3 casas →

    printf("\nMovendo o cavalo:\n");
    int xCavalo = 1, yCavalo = 1;
    moverCavalo(tabuleiro, &xCavalo, &yCavalo); // Cavalo em L

    return 0;
}