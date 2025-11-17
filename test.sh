#!/bin/bash

# Script de testes automatizados para SIMPLEX
# Execute com: bash test.sh

echo "=================================="
echo "  TESTES AUTOMATIZADOS - SIMPLEX  "
echo "=================================="

# Compilar
echo -e "\n[1/5] Compilando..."
make clean > /dev/null 2>&1
make
if [ $? -ne 0 ]; then
    echo "ERRO: Falha na compilação"
    exit 1
fi
echo "OK: Compilação bem-sucedida"

# Teste 1: Problema normal
echo -e "\n[2/5] Teste: Problema normal (exemplo.csv)"
echo "Esperado: STATUS ÓTIMO, Z = 36"
./simplex exemplo.csv | grep -A2 "RESULTADO"
echo "---"

# Teste 2: Problema sem fronteira
echo -e "\n[3/5] Teste: Problema sem fronteira"
echo "Esperado: STATUS SEM FRONTEIRA"
./simplex exemplo_sem_fronteira.csv | grep "Status:"
echo "---"

# Teste 3: Problema inviável
echo -e "\n[4/5] Teste: Problema inviável"
echo "Esperado: STATUS INVIÁVEL"
./simplex exemplo_inviavel.csv | grep "Status:"
echo "---"

# Teste 4: Problema com degeneração
echo -e "\n[5/5] Teste: Degeneração"
echo "Esperado: DEGENERAÇÃO detectada"
./simplex exemplo_degenerado.csv | grep "DEGENERAÇÃO"
echo "---"

echo -e "\n=================================="
echo "  TESTES CONCLUÍDOS"
echo "=================================="
