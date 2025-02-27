#include <stdio.h>
#include <stdbool.h>

// Constantes para o tamanho do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Valores para representar água e navios
#define AGUA 0
#define NAVIO 3

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

    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);

    return 0;
}