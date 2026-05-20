#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int grid[9][9] = {
    {5, 3, 0,  0, 7, 0,  0, 0, 0},
    {6, 0, 0,  1, 9, 5,  0, 0, 0},
    {0, 9, 8,  0, 0, 0,  0, 6, 0},

    {8, 0, 0,  0, 6, 0,  0, 0, 3},
    {4, 0, 0,  8, 0, 3,  0, 0, 1},
    {7, 0, 0,  0, 2, 0,  0, 0, 6},

    {0, 6, 0,  0, 0, 0,  2, 8, 0},
    {0, 0, 0,  4, 1, 9,  0, 0, 5},
    {0, 0, 0,  0, 8, 0,  0, 7, 9}
};

int fixo[9][9] = {
    {1, 1, 0,  0, 1, 0,  0, 0, 0},
    {1, 0, 0,  1, 1, 1,  0, 0, 0},
    {0, 1, 1,  0, 0, 0,  0, 1, 0},

    {1, 0, 0,  0, 1, 0,  0, 0, 1},
    {1, 0, 0,  1, 0, 1,  0, 0, 1},
    {1, 0, 0,  0, 1, 0,  0, 0, 1},

    {0, 1, 0,  0, 0, 0,  1, 1, 0},
    {0, 0, 0,  1, 1, 1,  0, 0, 1},
    {0, 0, 0,  0, 1, 0,  0, 1, 1}
};

int verificar_linha(int linha, int num) {
    for (int col = 0; col < 9; col++) {
        if (grid[linha][col] == num)
            return 0;
    }
    return 1;
}

int verificar_coluna(int col, int num) {
    for (int linha = 0; linha < 9; linha++) {
        if (grid[linha][col] == num)
            return 0;
    }
    return 1;
}

int verificar_quadrante(int linha, int col, int num) {
    int inicio_linha = (linha / 3) * 3;
    int inicio_col   = (col  / 3) * 3;

    for (int i = inicio_linha; i < inicio_linha + 3; i++) {
        for (int j = inicio_col; j < inicio_col + 3; j++) {
            if (grid[i][j] == num)
                return 0;
        }
    }
    return 1;
}

void exibir_grid() {
    printf("\n    A B C   D E F   G H I\n");
    printf("  +-------+-------+-------+\n");

    for (int i = 0; i < 9; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0)
                printf(" .");
            else
                printf(" %d", grid[i][j]);

            if (j == 2 || j == 5)
                printf(" |");
        }
        printf(" |\n");

        if (i == 2 || i == 5)
            printf("  +-------+-------+-------+\n");
    }
    printf("  +-------+-------+-------+\n");
}

int puzzle_completo() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (grid[i][j] == 0)
                return 0;
    return 1;
}

int main() {
    char entrada[10];
    char col_char;
    int  linha, col_idx, num;

    printf("=== SUDOKU ===\n");
    printf("Digite a coordenada (ex: A3) e depois o numero (1-9).\n");
    printf("Digite 'S' para encerrar.\n");

    while (1) {
        exibir_grid();

        if (puzzle_completo()) {
            printf("\nParabens! Voce completou o Sudoku!\n");
            break;
        }

        printf("\nCoordenada (coluna+linha, ex: B4): ");
        if (scanf("%9s", entrada) != 1) continue;

        if (toupper(entrada[0]) == 'S') {
            break;
        }

        if (!(isalpha(entrada[0]) && isdigit(entrada[1]) && entrada[2] == '\0')) {
            printf("Formato invalido! Use letra (A-I) + numero (1-9). Ex: C5\n");
            continue;
        }

        col_char = toupper(entrada[0]);
        linha    = entrada[1] - '1';
        col_idx  = col_char - 'A';

        if (col_idx < 0 || col_idx > 8 || linha < 0 || linha > 8) {
            printf("Coordenada fora do intervalo! Colunas: A-I, Linhas: 1-9.\n");
            continue;
        }

        if (fixo[linha][col_idx]) {
            printf("Essa celula faz parte do puzzle original e nao pode ser alterada!\n");
            continue;
        }

        printf("Numero (1-9, ou 0 para apagar): ");
        if (scanf("%d", &num) != 1) {
            printf("Entrada invalida.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (num < 0 || num > 9) {
            printf("Numero fora do intervalo! Use 1-9 (ou 0 para apagar).\n");
            continue;
        }

        if (num == 0) {
            grid[linha][col_idx] = 0;
            printf("Celula %c%d apagada.\n", col_char, linha + 1);
            continue;
        }

        if (!verificar_linha(linha, num)) {
            printf("Invalido! O numero %d ja existe na linha %d.\n", num, linha + 1);
            continue;
        }
        if (!verificar_coluna(col_idx, num)) {
            printf("Invalido! O numero %d ja existe na coluna %c.\n", num, col_char);
            continue;
        }
        if (!verificar_quadrante(linha, col_idx, num)) {
            printf("Invalido! O numero %d ja existe no quadrante 3x3.\n", num);
            continue;
        }

        grid[linha][col_idx] = num;
        printf("Numero %d inserido em %c%d!\n", num, col_char, linha + 1);
    }

    return 0;
}