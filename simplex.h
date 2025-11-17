#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define EPSILON 1e-10

// Estados do problema
typedef enum {
    STATUS_OTIMO,
    STATUS_INVIAVEL,
    STATUS_SEM_FRONTEIRA,
    STATUS_DEGENERADO,
    STATUS_ITERANDO
} Status;

// Estrutura do tableau SIMPLEX
typedef struct {
    double matriz[MAX_ROWS][MAX_COLS];
    int num_restricoes;
    int num_variaveis;
    int num_colunas;  // variaveis + folgas + RHS
    int iteracao;
    Status status;
    bool degenerado;
} Tableau;

// Funções principais
void ler_problema_csv(const char *arquivo, Tableau *t);
void inicializar_tableau(Tableau *t, double *obj, double **restricoes, double *rhs, int n_vars, int n_rest);
void imprimir_tableau(Tableau *t);
void resolver_simplex(Tableau *t);
int encontrar_coluna_pivoteante(Tableau *t);
int encontrar_linha_pivoteante(Tableau *t, int col_pivo);
void pivotar(Tableau *t, int linha_pivo, int col_pivo);
void verificar_degeneracao(Tableau *t);
void imprimir_solucao(Tableau *t);

#endif
