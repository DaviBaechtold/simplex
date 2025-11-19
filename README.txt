================================================================================
                     PROGRAMA SIMPLEX - README
                 Otimização de Sistemas Lineares
                 PUC-PR - Engenharia de Computação
================================================================================

ESTRUTURA DO PROJETO
================================================================================

simplex.h               - Header com estruturas e declarações
simplex.c               - Implementação completa do algoritmo
Makefile                - Compilação automatizada
TUTORIAL.txt            - Guia completo de uso
README.txt              - Este arquivo

exemplo.csv             - Teste: problema normal (ótimo)
exemplo_sem_fronteira.csv   - Teste: problema unbounded
exemplo_degenerado.csv  - Teste: detecção de degeneração


REQUISITOS IMPLEMENTADOS
================================================================================

[X] 1. Maximização
[X] 2. Interface com usuário (linha de comando + CSV)
[X] 3. Informar número de iterações
[X] 4. Identificar Z ótimo e variáveis básicas
[X] 5. Apontar degeneração
[X] 6. Indicar inviabilidade
[X] 7. Indicar problema sem fronteira


COMPILAÇÃO RÁPIDA
================================================================================

    make            # Compila
    make test       # Compila e testa com exemplo.csv
    make clean      # Remove executável


EXECUÇÃO RÁPIDA
================================================================================

    ./simplex exemplo.csv


ALGORITMO
================================================================================

1. Lê problema do CSV
2. Monta tableau inicial com variáveis de folga
3. Loop principal:
   a. Verifica otimalidade (linha Z sem negativos)
   b. Verifica inviabilidade (RHS negativo)
   c. Escolhe coluna pivoteante (mais negativo em Z)
   d. Escolhe linha pivoteante (razão mínima)
   e. Verifica se é unbounded (sem razões válidas)
   f. Realiza pivoteamento (Gauss-Jordan)
   g. Verifica degeneração
4. Exibe solução final


DETECÇÃO DE CASOS ESPECIAIS
================================================================================

DEGENERAÇÃO:
- Razões mínimas empatadas na escolha do pivô
- Variável básica com valor zero ou próximo
- Flag t->degenerado = true

INVIABILIDADE:
- RHS negativo em qualquer iteração
- Status STATUS_INVIAVEL

SEM FRONTEIRA:
- Coluna pivoteante sem razões positivas válidas
- Solução pode crescer indefinidamente
- Status STATUS_SEM_FRONTEIRA


PRECISÃO NUMÉRICA
================================================================================

EPSILON = 1e-10
- Usado para comparações de ponto flutuante
- Evita erros de arredondamento
- Valores < EPSILON considerados zero


LIMITAÇÕES
================================================================================

- Máximo 100 variáveis
- Máximo 100 restrições
- Apenas maximização (requisito obrigatório)
- Restrições formato <= (pode-se converter >= e =)
- Variáveis não-negativas


TESTES FORNECIDOS
================================================================================

exemplo.csv:
    Maximizar Z = 3x1 + 5x2
    s.a. x1 <= 4, 2x2 <= 12, 3x1 + 2x2 <= 18
    Resultado esperado: Z = 36, x1 = 2, x2 = 6

exemplo_sem_fronteira.csv:
    Problema sem solução limitada
    Resultado esperado: STATUS_SEM_FRONTEIRA

exemplo_degenerado.csv:
    Problema com degeneração
    Resultado esperado: STATUS_OTIMO com aviso de degeneração

================================================================================
