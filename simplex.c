#include "simplex.h"

// Lê problema do arquivo CSV
// Formato: primeira linha = coeficientes função objetivo
//          linhas seguintes = coeficientes restrições (último valor = RHS)
void ler_problema_csv(const char *arquivo, Tableau *t) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        fprintf(stderr, "ERRO: Não foi possível abrir o arquivo %s\n", arquivo);
        exit(1);
    }

    char linha[1024];
    double obj[MAX_COLS];
    double restricoes[MAX_ROWS][MAX_COLS];
    double rhs[MAX_ROWS];
    int n_vars = 0;
    int n_rest = 0;

    // Ler função objetivo
    if (fgets(linha, sizeof(linha), fp)) {
        char *token = strtok(linha, ",");
        while (token && n_vars < MAX_COLS) {
            obj[n_vars++] = atof(token);
            token = strtok(NULL, ",");
        }
    }

    // Ler restrições
    while (fgets(linha, sizeof(linha), fp) && n_rest < MAX_ROWS) {
        char *token = strtok(linha, ",");
        int col = 0;
        while (token) {
            double val = atof(token);
            if (col < n_vars) {
                restricoes[n_rest][col] = val;
            } else {
                rhs[n_rest] = val;  // Último valor é RHS
            }
            col++;
            token = strtok(NULL, ",");
        }
        n_rest++;
    }

    fclose(fp);

    // Converter array 2D para ponteiros
    double *ptr_restricoes[MAX_ROWS];
    for (int i = 0; i < n_rest; i++) {
        ptr_restricoes[i] = restricoes[i];
    }

    inicializar_tableau(t, obj, ptr_restricoes, rhs, n_vars, n_rest);
}

// Inicializa tableau com variáveis de folga
void inicializar_tableau(Tableau *t, double *obj, double **restricoes, double *rhs, int n_vars, int n_rest) {
    t->num_variaveis = n_vars;
    t->num_restricoes = n_rest;
    t->num_colunas = n_vars + n_rest + 1;  // vars originais + folgas + RHS
    t->iteracao = 0;
    t->status = STATUS_ITERANDO;
    t->degenerado = false;

    // Zerar matriz
    for (int i = 0; i <= n_rest; i++) {
        for (int j = 0; j < t->num_colunas; j++) {
            t->matriz[i][j] = 0.0;
        }
    }

    // Função objetivo (linha 0) - negativos para maximização
    for (int j = 0; j < n_vars; j++) {
        t->matriz[0][j] = -obj[j];
    }

    // Restrições
    for (int i = 0; i < n_rest; i++) {
        // Coeficientes das variáveis originais
        for (int j = 0; j < n_vars; j++) {
            t->matriz[i + 1][j] = restricoes[i][j];
        }
        // Variável de folga (forma identidade)
        t->matriz[i + 1][n_vars + i] = 1.0;
        // RHS
        t->matriz[i + 1][t->num_colunas - 1] = rhs[i];
    }
}

// Imprime tableau atual
void imprimir_tableau(Tableau *t) {
    printf("\n=== ITERAÇÃO %d ===\n", t->iteracao);
    printf("     ");
    for (int j = 0; j < t->num_variaveis; j++) {
        printf("x%-6d ", j + 1);
    }
    for (int j = 0; j < t->num_restricoes; j++) {
        printf("f%-6d ", j + 1);
    }
    printf("RHS    \n");

    for (int i = 0; i <= t->num_restricoes; i++) {
        if (i == 0) {
            printf("Z    ");
        } else {
            printf("R%-3d ", i);
        }
        for (int j = 0; j < t->num_colunas; j++) {
            printf("%7.2f ", t->matriz[i][j]);
        }
        printf("\n");
    }
}

// Encontra coluna pivoteante (regra: mais negativo na linha Z)
int encontrar_coluna_pivoteante(Tableau *t) {
    int col_pivo = -1;
    double min_val = -EPSILON;  // Só considera negativos significativos

    for (int j = 0; j < t->num_colunas - 1; j++) {
        if (t->matriz[0][j] < min_val) {
            min_val = t->matriz[0][j];
            col_pivo = j;
        }
    }

    return col_pivo;
}

// Encontra linha pivoteante (razão mínima positiva)
int encontrar_linha_pivoteante(Tableau *t, int col_pivo) {
    int linha_pivo = -1;
    double min_razao = DBL_MAX;
    int empates = 0;

    for (int i = 1; i <= t->num_restricoes; i++) {
        if (t->matriz[i][col_pivo] > EPSILON) {
            double razao = t->matriz[i][t->num_colunas - 1] / t->matriz[i][col_pivo];
            
            if (razao < -EPSILON) continue;  // Ignora razões negativas

            if (fabs(razao) < EPSILON) {
                empates++;  // Razão zero indica degeneração
            }

            if (razao < min_razao) {
                min_razao = razao;
                linha_pivo = i;
            }
        }
    }

    if (empates > 0) {
        t->degenerado = true;
    }

    return linha_pivo;
}

// Realiza pivoteamento
void pivotar(Tableau *t, int linha_pivo, int col_pivo) {
    double pivo = t->matriz[linha_pivo][col_pivo];

    // Normaliza linha do pivô
    for (int j = 0; j < t->num_colunas; j++) {
        t->matriz[linha_pivo][j] /= pivo;
    }

    // Eliminação gaussiana nas outras linhas
    for (int i = 0; i <= t->num_restricoes; i++) {
        if (i != linha_pivo) {
            double fator = t->matriz[i][col_pivo];
            for (int j = 0; j < t->num_colunas; j++) {
                t->matriz[i][j] -= fator * t->matriz[linha_pivo][j];
            }
        }
    }
}

// Verifica se há degeneração
void verificar_degeneracao(Tableau *t) {
    for (int i = 1; i <= t->num_restricoes; i++) {
        if (fabs(t->matriz[i][t->num_colunas - 1]) < EPSILON) {
            t->degenerado = true;
            return;
        }
    }
}

// Algoritmo SIMPLEX principal
void resolver_simplex(Tableau *t) {
    printf("\n========== INICIANDO SIMPLEX ==========\n");
    imprimir_tableau(t);

    while (t->status == STATUS_ITERANDO) {
        // Verifica inviabilidade (RHS negativo nas restrições)
        for (int i = 1; i <= t->num_restricoes; i++) {
            if (t->matriz[i][t->num_colunas - 1] < -EPSILON) {
                t->status = STATUS_INVIAVEL;
                printf("\nPROBLEMA INVIÁVEL: RHS negativo detectado na linha %d\n", i);
                return;
            }
        }

        // Encontrar coluna pivoteante
        int col_pivo = encontrar_coluna_pivoteante(t);
        
        if (col_pivo == -1) {
            // Sem coeficientes negativos em Z = solução ótima
            t->status = STATUS_OTIMO;
            break;
        }

        // Encontrar linha pivoteante
        int linha_pivo = encontrar_linha_pivoteante(t, col_pivo);

        if (linha_pivo == -1) {
            // Nenhuma razão válida = problema sem fronteira
            t->status = STATUS_SEM_FRONTEIRA;
            printf("\nPROBLEMA SEM FRONTEIRA: Coluna %d não tem razões positivas\n", col_pivo + 1);
            return;
        }

        // Pivotar
        printf("\nPivô: Linha %d, Coluna %d (x%d)\n", linha_pivo, col_pivo + 1, col_pivo + 1);
        pivotar(t, linha_pivo, col_pivo);
        t->iteracao++;

        imprimir_tableau(t);

        // Verificar degeneração
        verificar_degeneracao(t);

        // Limite de iterações (prevenir loop infinito)
        if (t->iteracao > 1000) {
            printf("\nERRO: Limite de iterações excedido\n");
            break;
        }
    }
}

// Imprime solução final
void imprimir_solucao(Tableau *t) {
    printf("\n========== RESULTADO ==========\n");
    printf("Status: ");
    
    switch (t->status) {
        case STATUS_OTIMO:
            printf("ÓTIMO ENCONTRADO\n");
            break;
        case STATUS_INVIAVEL:
            printf("PROBLEMA INVIÁVEL\n");
            return;
        case STATUS_SEM_FRONTEIRA:
            printf("PROBLEMA SEM FRONTEIRA\n");
            return;
        default:
            printf("INDETERMINADO\n");
            return;
    }

    if (t->degenerado) {
        printf("ATENÇÃO: Problema apresenta DEGENERAÇÃO\n");
    }

    printf("\nNúmero de iterações: %d\n", t->iteracao);
    printf("\nValor ótimo de Z: %.4f\n", t->matriz[0][t->num_colunas - 1]);

    printf("\nVariáveis básicas:\n");
    
    // Identificar variáveis básicas (colunas com um único 1 e resto 0)
    for (int j = 0; j < t->num_colunas - 1; j++) {
        int count_one = 0;
        int row_one = -1;
        bool is_basic = true;

        for (int i = 0; i <= t->num_restricoes; i++) {
            if (fabs(t->matriz[i][j] - 1.0) < EPSILON) {
                count_one++;
                row_one = i;
            } else if (fabs(t->matriz[i][j]) > EPSILON) {
                is_basic = false;
                break;
            }
        }

        if (is_basic && count_one == 1 && row_one > 0) {
            if (j < t->num_variaveis) {
                printf("  x%d = %.4f\n", j + 1, t->matriz[row_one][t->num_colunas - 1]);
            } else {
                printf("  f%d = %.4f\n", j - t->num_variaveis + 1, t->matriz[row_one][t->num_colunas - 1]);
            }
        }
    }

    printf("\nVariáveis não-básicas (valor = 0):\n");
    for (int j = 0; j < t->num_variaveis; j++) {
        int count_one = 0;
        int row_one = -1;
        bool is_basic = true;

        for (int i = 0; i <= t->num_restricoes; i++) {
            if (fabs(t->matriz[i][j] - 1.0) < EPSILON) {
                count_one++;
                row_one = i;
            } else if (fabs(t->matriz[i][j]) > EPSILON) {
                is_basic = false;
                break;
            }
        }

        if (!(is_basic && count_one == 1 && row_one > 0)) {
            printf("  x%d = 0.0000\n", j + 1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo.csv>\n", argv[0]);
        printf("\nFormato do CSV:\n");
        printf("  Linha 1: Coeficientes da função objetivo (separados por vírgula)\n");
        printf("  Linhas seguintes: Coeficientes das restrições + RHS no final\n");
        printf("\nExemplo:\n");
        printf("  3,5\n");
        printf("  1,0,4\n");
        printf("  0,2,12\n");
        printf("  3,2,18\n");
        printf("\nSignifica:\n");
        printf("  Maximizar Z = 3x1 + 5x2\n");
        printf("  Sujeito a: x1 <= 4\n");
        printf("            2x2 <= 12\n");
        printf("            3x1 + 2x2 <= 18\n");
        return 1;
    }

    Tableau t;
    ler_problema_csv(argv[1], &t);
    resolver_simplex(&t);
    imprimir_solucao(&t);

    return 0;
}
