#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3   // Tamanho fixo dos navios

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // ============================================================
    // 1️⃣ Inicializando o tabuleiro com 0 (água)
    // ============================================================
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // ============================================================
    // 2️⃣ Definindo os navios (todos com tamanho 3)
    // ============================================================
    int navioH[TAM_NAVIO] = {3, 3, 3}; // Navio horizontal
    int navioV[TAM_NAVIO] = {3, 3, 3}; // Navio vertical
    int navioD1[TAM_NAVIO] = {3, 3, 3}; // Navio diagonal principal (↘)
    int navioD2[TAM_NAVIO] = {3, 3, 3}; // Navio diagonal secundária (↙)

    // ============================================================
    // 3️⃣ Coordenadas iniciais para cada navio
    // ============================================================
    int linhaH = 2, colunaH = 4; // Horizontal (→)
    int linhaV = 5, colunaV = 7; // Vertical (↓)
    int linhaD1 = 0, colunaD1 = 0; // Diagonal principal (↘)
    int linhaD2 = 0, colunaD2 = 9; // Diagonal secundária (↙)

    // ============================================================
    // 4️⃣ Verificando limites do tabuleiro
    // ============================================================
    if (colunaH + TAM_NAVIO > TAM || linhaV + TAM_NAVIO > TAM ||
        linhaD1 + TAM_NAVIO > TAM || colunaD1 + TAM_NAVIO > TAM ||
        linhaD2 + TAM_NAVIO > TAM || colunaD2 - (TAM_NAVIO - 1) < 0) {
        printf("Erro: um dos navios ultrapassa os limites do tabuleiro.\n");
        return 1;
    }

    // ============================================================
    // 5️⃣ Função auxiliar: checar sobreposição antes de posicionar
    // ============================================================
    int sobreposicao = 0;

    // 🔹 Verifica horizontal
    for (i = 0; i < TAM_NAVIO; i++)
        if (tabuleiro[linhaH][colunaH + i] != 0)
            sobreposicao = 1;

    // 🔹 Verifica vertical
    for (i = 0; i < TAM_NAVIO; i++)
        if (tabuleiro[linhaV + i][colunaV] != 0)
            sobreposicao = 1;

    // 🔹 Verifica diagonal principal ↘
    for (i = 0; i < TAM_NAVIO; i++)
        if (tabuleiro[linhaD1 + i][colunaD1 + i] != 0)
            sobreposicao = 1;

    // 🔹 Verifica diagonal secundária ↙
    for (i = 0; i < TAM_NAVIO; i++)
        if (tabuleiro[linhaD2 + i][colunaD2 - i] != 0)
            sobreposicao = 1;

    if (sobreposicao) {
        printf("Erro: navios se sobrepõem.\n");
        return 1;
    }

    // ============================================================
    // 6️⃣ Posicionando os navios
    // ============================================================

    // Horizontal (→)
    for (i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaH][colunaH + i] = navioH[i];

    // Vertical (↓)
    for (i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaV + i][colunaV] = navioV[i];

    // Diagonal principal (↘)
    for (i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaD1 + i][colunaD1 + i] = navioD1[i];

    // Diagonal secundária (↙)
    for (i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaD2 + i][colunaD2 - i] = navioD2[i];

    // ============================================================
    // 7️⃣ Exibindo o tabuleiro completo
    // ============================================================
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = água | 3 = navio (horizontal, vertical ou diagonal)\n");

    return 0;
}
