#include <stdio.h>

#define TAM 10   // Tamanho do tabuleiro 10x10
#define TAM_NAVIO 3  // Tamanho fixo de cada navio

int main() {
    int tabuleiro[TAM][TAM];  // Matriz do tabuleiro
    int i, j;

    // ===========================
    // 1️⃣ Inicializando o tabuleiro com 0 (água)
    // ===========================
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // ===========================
    // 2️⃣ Definindo os navios (vetores)
    // ===========================
    int navioHorizontal[TAM_NAVIO] = {3, 3, 3}; // Navio horizontal
    int navioVertical[TAM_NAVIO]   = {3, 3, 3}; // Navio vertical

    // ===========================
    // 3️⃣ Coordenadas iniciais (definidas no código)
    // ===========================
    int linhaH = 2;  // linha inicial do navio horizontal
    int colunaH = 4; // coluna inicial do navio horizontal

    int linhaV = 5;  // linha inicial do navio vertical
    int colunaV = 7; // coluna inicial do navio vertical

    // ===========================
    // 4️⃣ Validação simples para evitar sobreposição e limites
    // ===========================
    if (colunaH + TAM_NAVIO > TAM || linhaV + TAM_NAVIO > TAM) {
        printf("Erro: navio fora dos limites do tabuleiro.\n");
        return 1;
    }

    // ===========================
    // 5️⃣ Posicionando o navio horizontal
    // ===========================
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
    }

    // ===========================
    // 6️⃣ Posicionando o navio vertical (garantindo que não sobreponha)
    // ===========================
    int sobreposicao = 0;
    for (i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaV + i][colunaV] != 0) {
            sobreposicao = 1;
            break;
        }
    }

    if (sobreposicao) {
        printf("Erro: navios se sobrepõem.\n");
        return 1;
    }

    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = navioVertical[i];
    }

    // ===========================
    // 7️⃣ Exibindo o tabuleiro
    // ===========================
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = água | 3 = navio\n");

    return 0;
}
