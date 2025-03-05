#include <stdio.h>
// Tamanho do tabuleiro

#define TAMANHO 10

// Tamanho dos navios
#define TAMANHO_NAVIO 4

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime cada célula do tabuleiro
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }
}

// Função para posicionar um navio horizontalmente (pra direita)
void posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 7; // Marca as posições do navio com 7
    }
}

// Função para posicionar um navio verticalmente (pra baixo)
void posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 7; // Marca as posições do navio com 7
    }
}

// Função para posicionar um navio na diagonal principal (pra baixo e pra direita) (linha = coluna)
void posicionarNavioDiagonalPrincipal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 7; // Marca as posições do navio com 7
    }
}

// Função para posicionar um navio na diagonal secundária (pra baixo e pra esquerda) (linha + coluna = constante)
void posicionarNavioDiagonalSecundaria(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = 7; // Marca as posições do navio com 7
    }
}

// Função para validar se as coordenadas estão dentro dos limites do tabuleiro
int coordenadasValidas(int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // Navio horizontal (pra direita)
        return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna + TAMANHO_NAVIO <= TAMANHO);
    } else if (orientacao == 1) { // Navio vertical (pra baixo)
        return (linha >= 0 && linha + TAMANHO_NAVIO <= TAMANHO && coluna >= 0 && coluna < TAMANHO);
    } else if (orientacao == 2) { // Navio diagonal principal (pra baixo e pra direita)
        return (linha >= 0 && linha + TAMANHO_NAVIO <= TAMANHO && coluna >= 0 && coluna + TAMANHO_NAVIO <= TAMANHO);
    } else if (orientacao == 3) { // Navio diagonal secundária (pra baixo e pra esquerda)
        return (linha >= 0 && linha + TAMANHO_NAVIO <= TAMANHO && coluna - TAMANHO_NAVIO + 1 >= 0 && coluna < TAMANHO);
    }
    return 0; // Orientação inválida
}

// Função para verificar se há sobreposição de navios
int semSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // Navio horizontal  (pra direita)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) {
                return 0; // Há sobreposição
            }
        }
    } else if (orientacao == 1) { // Navio vertical  (pra baixo)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) {
                return 0; // Há sobreposição
            }
        }
    } else if (orientacao == 2) { // Navio diagonal principal (pra baixo e pra direita)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) {
                return 0; // Há sobreposição
            }
        }
    } else if (orientacao == 3) { // Navio diagonal secundária (pra baixo e pra esquerda)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna - i] != 0) {
                return 0; // Há sobreposição
            }
        }
    }
    return 1; // Não há sobreposição
}

int main() {
    // Inicializa o tabuleiro com 0s (água)
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // Coordenadas iniciais dos navios (definidas no código)
    int linhaNavio1 = 2, colunaNavio1 = 6; // Navio horizontal (pra direita)
    int linhaNavio2 = 5, colunaNavio2 = 6; // Navio vertical (pra baixo)
    int linhaNavio3 = 1, colunaNavio3 = 1; // Navio diagonal principal (pra baixo e pra direita)
    int linhaNavio4 = 6, colunaNavio4 = 5; // Navio diagonal secundária (pra baixo e pra esquerda)

    // Posiciona o navio horizontal (pra direita)
    if (coordenadasValidas(linhaNavio1, colunaNavio1, 0) && semSobreposicao(tabuleiro, linhaNavio1, colunaNavio1, 0)) {
        posicionarNavioHorizontal(tabuleiro, linhaNavio1, colunaNavio1);
    } else {
        printf("Erro: Coordenadas inválidas ou sobreposição para o navio horizontal (pra direita).\n");
        return 1;
    }

    // Posiciona o navio vertical (pra baixo)
    if (coordenadasValidas(linhaNavio2, colunaNavio2, 1) && semSobreposicao(tabuleiro, linhaNavio2, colunaNavio2, 1)) {
        posicionarNavioVertical(tabuleiro, linhaNavio2, colunaNavio2);
    } else {
        printf("Erro: Coordenadas inválidas ou sobreposição para o navio vertical (pra baixo).\n");
        return 1;
    }

    // Posiciona o navio diagonal principal (pra baixo)
    if (coordenadasValidas(linhaNavio3, colunaNavio3, 2) && semSobreposicao(tabuleiro, linhaNavio3, colunaNavio3, 2)) {
        posicionarNavioDiagonalPrincipal(tabuleiro, linhaNavio3, colunaNavio3);
    } else {
        printf("Erro: Coordenadas inválidas ou sobreposição para o navio diagonal principal (pra baixo e pra direita).\n");
        return 1;
    }

    // Posiciona o navio diagonal secundária (pra baixo e pra esquerda)
    if (coordenadasValidas(linhaNavio4, colunaNavio4, 3) && semSobreposicao(tabuleiro, linhaNavio4, colunaNavio4, 3)) {
        posicionarNavioDiagonalSecundaria(tabuleiro, linhaNavio4, colunaNavio4);
    } else {
        printf("Erro: Coordenadas inválidas ou sobreposição para o navio diagonal secundária (pra baixo e pra esquerda).\n");
        return 1;
    }

    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);

    return 0;
}