#include <stdio.h>
#include <stdbool.h>

// Dimensões do tabuleiro e das matrizes de habilidade
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Tamanho das matrizes de habilidade (5x5)

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Água
        }
    }
}

// Função para verificar se a posição do navio é válida
bool verificarPosicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                           int linha, int coluna, int tamanho, char tipo) {
    if (tipo == 'H') { // Horizontal
        if (coluna + tamanho > TAMANHO_TABULEIRO) return false;
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] != 0) return false; // Verifica sobreposição
        }
    } else if (tipo == 'V') { // Vertical
        if (linha + tamanho > TAMANHO_TABULEIRO) return false;
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] != 0) return false; // Verifica sobreposição
        }
    } else if (tipo == 'D') { // Diagonal crescente
        if (linha + tamanho > TAMANHO_TABULEIRO || coluna + tamanho > TAMANHO_TABULEIRO) return false;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) return false; // Verifica sobreposição
        }
    } else if (tipo == 'E') { // Diagonal decrescente
        if (linha + tamanho > TAMANHO_TABULEIRO || coluna - tamanho + 1 < 0) return false;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna - i] != 0) return false; // Verifica sobreposição
        }
    }
    return true;
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int tamanho, char tipo) {
    if (tipo == 'H') { // Horizontal
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = 3; // Marca o navio
        }
    } else if (tipo == 'V') { // Vertical
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = 3; // Marca o navio
        }
    } else if (tipo == 'D') { // Diagonal crescente
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna + i] = 3; // Marca o navio
        }
    } else if (tipo == 'E') { // Diagonal decrescente
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna - i] = 3; // Marca o navio
        }
    }
}

// Função para inicializar a matriz de habilidade em cone
void inicializarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cone: linha 0 tem 1 célula, linha 1 tem 3 células, linha 2 tem 5 células, etc.
            if (j >= (TAMANHO_HABILIDADE/2 - i) && j <= (TAMANHO_HABILIDADE/2 + i)) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para inicializar a matriz de habilidade em cruz
void inicializarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cruz: linha e coluna centrais são afetadas
            if (i == TAMANHO_HABILIDADE/2 || j == TAMANHO_HABILIDADE/2) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para inicializar a matriz de habilidade em octaedro (losango)
void inicializarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Octaedro: forma de losango centrada no ponto (2,2) para matriz 5x5
            int centro = TAMANHO_HABILIDADE/2;
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para sobrepor a matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                      int origem_linha, int origem_coluna) {
    // Centro da matriz de habilidade
    int centro = TAMANHO_HABILIDADE/2;
    
    // Percorre a matriz de habilidade
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a posição correspondente no tabuleiro
            int tab_linha = origem_linha + (i - centro);
            int tab_coluna = origem_coluna + (j - centro);
            
            // Verifica se a posição está dentro dos limites do tabuleiro
            if (tab_linha >= 0 && tab_linha < TAMANHO_TABULEIRO && 
                tab_coluna >= 0 && tab_coluna < TAMANHO_TABULEIRO) {
                // Aplica a habilidade (valor 5) se a posição na matriz de habilidade for 1
                // e se a posição não contém um navio (3)
                if (habilidade[i][j] == 1 && tabuleiro[tab_linha][tab_coluna] != 3) {
                    tabuleiro[tab_linha][tab_coluna] = 5; // Marca área afetada
                }
            }
        }
    }
}

// Função para exibir o tabuleiro com diferentes caracteres
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprimir cabeçalho de colunas
    printf("\n  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Imprimir linhas com conteúdo do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" ~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf(" N "); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf(" X "); // Área de efeito
            }
        }
        printf("\n");
    }
}

int main() {
    // Declaração do tabuleiro e matrizes de habilidade
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Inicializar tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    // Definir coordenadas iniciais dos navios (fixas no código)
    struct {
        int linha;
        int coluna;
        char tipo; // 'H': Horizontal, 'V': Vertical, 'D': Diagonal crescente, 'E': Diagonal decrescente
    } navios[4] = {
        {2, 3, 'H'}, // Navio horizontal
        {6, 7, 'V'}, // Navio vertical
        {1, 1, 'D'}, // Navio diagonal crescente
        {3, 8, 'E'}  // Navio diagonal decrescente
    };
    
    // Posicionar os quatro navios
    for (int i = 0; i < 4; i++) {
        if (verificarPosicaoValida(tabuleiro, navios[i].linha, navios[i].coluna, TAMANHO_NAVIO, navios[i].tipo)) {
            posicionarNavio(tabuleiro, navios[i].linha, navios[i].coluna, TAMANHO_NAVIO, navios[i].tipo);
        } else {
            printf("Erro: Posição inválida para o navio %d!\n", i + 1);
            return 1;
        }
    }
    
    // Inicializar matrizes de habilidade
    inicializarHabilidadeCone(habilidadeCone);
    inicializarHabilidadeCruz(habilidadeCruz);
    inicializarHabilidadeOctaedro(habilidadeOctaedro);
    
    // Definir pontos de origem das habilidades (fixos no código)
    struct {
        int linha;
        int coluna;
    } origens[3] = {
        {4, 4}, // Cone
        {7, 2}, // Cruz
        {1, 7}  // Octaedro
    };
    
    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, origens[0].linha, origens[0].coluna);
    aplicarHabilidade(tabuleiro, habilidadeCruz, origens[1].linha, origens[1].coluna);
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, origens[2].linha, origens[2].coluna);
    
    // Exibir o tabuleiro com navios e áreas de efeito
    printf("Tabuleiro com navios e áreas de efeito:\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
