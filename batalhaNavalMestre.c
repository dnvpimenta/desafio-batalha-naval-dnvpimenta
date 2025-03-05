#include <stdio.h>
#include <stdbool.h>

// Constantes para o tamanho do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Valores para representar água, navios e áreas de habilidade
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Tamanho das matrizes de habilidade (5x5)
#define TAMANHO_HABILIDADE 5

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se as coordenadas estão dentro dos limites do tabuleiro
bool coordenadasValidas(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO;
}

// Função para verificar se o navio pode ser posicionado sem sobreposição
bool posicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, bool horizontal) {
    for (int i = 0; i < tamanho; i++) {
        int novaLinha = linha + (horizontal ? 0 : i);
        int novaColuna = coluna + (horizontal ? i : 0);
        
        if (!coordenadasValidas(novaLinha, novaColuna)) {
            return false; // Fora dos limites do tabuleiro
        }
        
        if (tabuleiro[novaLinha][novaColuna] != AGUA) {
            return false; // Sobreposição com outro navio
        }
    }
    return true;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, bool horizontal) {
    for (int i = 0; i < tamanho; i++) {
        int novaLinha = linha + (horizontal ? 0 : i);
        int novaColuna = coluna + (horizontal ? i : 0);
        
        tabuleiro[novaLinha][novaColuna] = NAVIO;
    }
}

// Função para criar a matriz de habilidade em formato de cone
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= i && j < TAMANHO_HABILIDADE - i) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de cruz
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para sobrepor a habilidade ao tabuleiro
void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linhaOrigem, int colunaOrigem) {
    int offset = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int novaLinha = linhaOrigem - offset + i;
            int novaColuna = colunaOrigem - offset + j;
            
            if (coordenadasValidas(novaLinha, novaColuna) && habilidade[i][j] == 1) {
                tabuleiro[novaLinha][novaColuna] = HABILIDADE;
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro com água
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Coordenadas iniciais dos navios (linha, coluna)
    int linhaNavio1 = 2, colunaNavio1 = 2; // Navio horizontal
    int linhaNavio2 = 5, colunaNavio2 = 5; // Navio vertical

    // Verifica se as posições dos navios são válidas
    if (!posicaoValida(tabuleiro, linhaNavio1, colunaNavio1, TAMANHO_NAVIO, true)) {
        printf("Erro: Navio 1 está fora dos limites ou sobrepõe outro navio.\n");
        return 1;
    }

    if (!posicaoValida(tabuleiro, linhaNavio2, colunaNavio2, TAMANHO_NAVIO, false)) {
        printf("Erro: Navio 2 está fora dos limites ou sobrepõe outro navio.\n");
        return 1;
    }

    // Posiciona os navios no tabuleiro
    posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, TAMANHO_NAVIO, true); // Navio horizontal
    posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, TAMANHO_NAVIO, false); // Navio vertical

    // Cria as matrizes de habilidade
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    // Define os pontos de origem das habilidades
    int linhaHabilidade1 = 1, colunaHabilidade1 = 1; // Cone
    int linhaHabilidade2 = 4, colunaHabilidade2 = 4; // Cruz
    int linhaHabilidade3 = 7, colunaHabilidade3 = 7; // Octaedro

    // Sobrepor as habilidades ao tabuleiro
    sobreporHabilidade(tabuleiro, habilidadeCone, linhaHabilidade1, colunaHabilidade1);
    sobreporHabilidade(tabuleiro, habilidadeCruz, linhaHabilidade2, colunaHabilidade2);
    sobreporHabilidade(tabuleiro, habilidadeOctaedro, linhaHabilidade3, colunaHabilidade3);

    // Exibe o tabuleiro com os navios e as áreas de habilidade
    exibirTabuleiro(tabuleiro);

    return 0;