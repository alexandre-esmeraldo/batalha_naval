#include <stdio.h>

#define TAM_TAB 10       // Tamanho do tabuleiro
#define TAM_HAB 5        // Tamanho das habilidades (matriz 5x5)
#define NAVIO 3          // Valor do navio
#define HABILIDADE 5     // Valor da habilidade (área de efeito)

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função que gera uma matriz de habilidade do tipo Cone (forma triangular descendente)
void gerarMatrizCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função que gera uma matriz de habilidade do tipo Cruz (formato +)
void gerarMatrizCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função que gera uma matriz de habilidade do tipo Octaedro (losango)
void gerarMatrizOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    int meio = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica uma matriz de habilidade ao tabuleiro, centralizando no ponto (lin, col)
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int hab[TAM_HAB][TAM_HAB], int lin, int col) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int tabLinha = lin - offset + i;
            int tabColuna = col - offset + j;

            // Valida se está dentro dos limites do tabuleiro
            if (tabLinha >= 0 && tabLinha < TAM_TAB && tabColuna >= 0 && tabColuna < TAM_TAB) {
                if (hab[i][j] == 1 && tabuleiro[tabLinha][tabColuna] == 0)
                    tabuleiro[tabLinha][tabColuna] = HABILIDADE;
            }
        }
    }
}

// Função principal
int main() {
    int tabuleiro[TAM_TAB][TAM_TAB] = {0}; // Inicializa com água (0)

    // Posiciona alguns navios (fixos)
    tabuleiro[2][2] = NAVIO;
    tabuleiro[2][3] = NAVIO;
    tabuleiro[2][4] = NAVIO;

    tabuleiro[5][6] = NAVIO;
    tabuleiro[6][6] = NAVIO;
    tabuleiro[7][6] = NAVIO;

    tabuleiro[0][0] = NAVIO;
    tabuleiro[1][1] = NAVIO;
    tabuleiro[2][2] = NAVIO;

    tabuleiro[0][9] = NAVIO;
    tabuleiro[1][8] = NAVIO;
    tabuleiro[2][7] = NAVIO;

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    gerarMatrizCone(cone);
    gerarMatrizCruz(cruz);
    gerarMatrizOctaedro(octaedro);

    // Aplicar habilidades ao tabuleiro (posições fixas)
    aplicarHabilidade(tabuleiro, cone, 3, 3);      // Aplica cone centrado em (3,3)
    aplicarHabilidade(tabuleiro, cruz, 6, 6);      // Aplica cruz centrado em (6,6)
    aplicarHabilidade(tabuleiro, octaedro, 5, 2);  // Aplica octaedro centrado em (5,2)

    // Exibir tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
