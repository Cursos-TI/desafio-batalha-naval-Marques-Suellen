#include <stdio.h>
#include <stdlib.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3   // Tamanho fixo dos navios

// Matrizes de habilidade (tamanho 5x5 usado neste exemplo)
#define HSIZE 5
#define HCENTER (HSIZE/2)

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
    // 4️⃣ Verificando limites do tabuleiro para navios
    // ============================================================
    if (colunaH + TAM_NAVIO > TAM || linhaV + TAM_NAVIO > TAM ||
        linhaD1 + TAM_NAVIO > TAM || colunaD1 + TAM_NAVIO > TAM ||
        linhaD2 + TAM_NAVIO > TAM || colunaD2 - (TAM_NAVIO - 1) < 0) {
        printf("Erro: um dos navios ultrapassa os limites do tabuleiro.\n");
        return 1;
    }

    // ============================================================
    // 5️⃣ Checar sobreposição entre navios (pré-posicionamento)
    // ============================================================
    int sobreposicao = 0;

    // Verifica horizontal
    for (i = 0; i < TAM_NAVIO; i++)
        if (tabuleiro[linhaH][colunaH + i] != 0)
            sobreposicao = 1;

    // Verifica vertical
    for (i = 0; i < TAM_NAVIO; i++)
        if (tabuleiro[linhaV + i][colunaV] != 0)
            sobreposicao = 1;

    // Verifica diagonal principal ↘
    for (i = 0; i < TAM_NAVIO; i++)
        if (tabuleiro[linhaD1 + i][colunaD1 + i] != 0)
            sobreposicao = 1;

    // Verifica diagonal secundária ↙
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
    // 7️⃣ Construindo dinamicamente as matrizes de habilidade 5x5
    //     - cone: ponto no topo, expande para baixo (forma de cone)
    //     - cruz: linha central e coluna central marcadas
    //     - octaedro: forma de losango (taxa: |dx| + |dy| <= raio)
    // ============================================================
    int cone[HSIZE][HSIZE] = {0};
    int cruz[HSIZE][HSIZE] = {0};
    int octaedro[HSIZE][HSIZE] = {0};

    // Construir CONE (topo apontando para baixo)
    // lógica: para cada linha r (0..HSIZE-1), acende colunas do centro +/- r
    for (i = 0; i < HSIZE; i++) {
        int alcance = i; // quanto a "base" do cone se abre conforme a linha aumenta
        for (j = 0; j < HSIZE; j++) {
            if ( (j >= HCENTER - alcance) && (j <= HCENTER + alcance) ) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    // Construir CRUZ (linha central + coluna central)
    for (i = 0; i < HSIZE; i++) {
        for (j = 0; j < HSIZE; j++) {
            if (i == HCENTER || j == HCENTER) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }

    // Construir OCTAEDRO (vista frontal ≈ losango/diamante)
    // critério: |dx| + |dy| <= raio, com raio = HCENTER (2 para HSIZE=5)
    for (i = 0; i < HSIZE; i++) {
        for (j = 0; j < HSIZE; j++) {
            int dx = i - HCENTER;
            int dy = j - HCENTER;
            if ( (abs(dx) + abs(dy)) <= HCENTER ) octaedro[i][j] = 1;
            else octaedro[i][j] = 0;
        }
    }

    // ============================================================
    // 8️⃣ Definindo pontos de origem (centro) no tabuleiro para cada habilidade
    // ============================================================
    // Valores definidos diretamente no código conforme simplificação
    int origemConeLinha = 3, origemConeColuna = 2;
    int origemCruzLinha = 7, origemCruzColuna = 5;
    int origemOctLinha  = 4, origemOctColuna  = 8;

    // ============================================================
    // 9️⃣ Função de sobreposição: aplica matriz de habilidade ao tabuleiro
    //    - Para cada célula da matriz de habilidade que vale 1,
    //      calcula sua posição no tabuleiro e marca como 5.
    //    - Verifica limites do tabuleiro antes de escrever.
    // ============================================================
    int r, c;
    // Aplicar CONE
    for (r = 0; r < HSIZE; r++) {
        for (c = 0; c < HSIZE; c++) {
            if (cone[r][c] == 1) {
                int boardR = origemConeLinha + (r - HCENTER);
                int boardC = origemConeColuna + (c - HCENTER);
                if (boardR >= 0 && boardR < TAM && boardC >= 0 && boardC < TAM) {
                    tabuleiro[boardR][boardC] = 5; // marca área afetada com 5
                }
            }
        }
    }

    // Aplicar CRUZ
    for (r = 0; r < HSIZE; r++) {
        for (c = 0; c < HSIZE; c++) {
            if (cruz[r][c] == 1) {
                int boardR = origemCruzLinha + (r - HCENTER);
                int boardC = origemCruzColuna + (c - HCENTER);
                if (boardR >= 0 && boardR < TAM && boardC >= 0 && boardC < TAM) {
                    tabuleiro[boardR][boardC] = 5;
                }
            }
        }
    }

    // Aplicar OCTAEDRO
    for (r = 0; r < HSIZE; r++) {
        for (c = 0; c < HSIZE; c++) {
            if (octaedro[r][c] == 1) {
                int boardR = origemOctLinha + (r - HCENTER);
                int boardC = origemOctColuna + (c - HCENTER);
                if (boardR >= 0 && boardR < TAM && boardC >= 0 && boardC < TAM) {
                    tabuleiro[boardR][boardC] = 5;
                }
            }
        }
    }

    // ============================================================
    // 10️⃣ Exibindo o tabuleiro completo com habilidades
    //      Representação numérica:
    //         0 = água
    //         3 = navio
    //         5 = área afetada por habilidade
    // ============================================================
    printf("\n=== TABULEIRO DE BATALHA NAVAL (nível mestre) ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = água | 3 = navio | 5 = área de habilidade\n");

    return 0;
}