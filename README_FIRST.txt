================================================================================
                    ★ LEIA-ME PRIMEIRO ★
                   PROGRAMA SIMPLEX - PUC-PR
          Otimização de Sistemas Lineares - Prof. Holisses Bellon
================================================================================

VOCÊ ACABOU DE BAIXAR O PROJETO SIMPLEX COMPLETO!

Este pacote contém TUDO que você precisa para:
✓ Compilar e executar o programa
✓ Testar todos os casos (ótimo, unbounded, inviável, degenerado)
✓ Entender o código
✓ Preparar para a defesa
✓ Entregar no Blackboard


SEUS PRÓXIMOS PASSOS (ESCOLHA SEU CAMINHO)
================================================================================

【 CAMINHO RÁPIDO - SÓ QUERO TESTAR 】
────────────────────────────────────
1. Abra um terminal neste diretório
2. Digite: make
3. Digite: ./simplex exemplo.csv
4. Pronto! Deve mostrar Z = 36

👉 Depois leia: INICIO_RAPIDO.txt


【 CAMINHO COMPLETO - QUERO ENTENDER 】
────────────────────────────────────
1. Leia: INDEX.txt (mapa de todos os arquivos)
2. Leia: README.txt (visão geral técnica)
3. Leia: TUTORIAL.txt (como usar)
4. Estude: simplex.c (o código)
5. Execute: bash test.sh (testes automáticos)

👉 Depois leia: EXEMPLOS.txt


【 CAMINHO DEFESA - PREPARAR APRESENTAÇÃO 】
────────────────────────────────────
1. Leia: RESUMO.txt (resumo executivo)
2. Leia: CHECKLIST.txt (o que estudar)
3. Estude: simplex.c (foco nas funções principais)
4. Pratique: modificações simples no código
5. Revise: perguntas esperadas no RESUMO.txt


ESTRUTURA DOS ARQUIVOS (15 arquivos)
================================================================================

📁 CÓDIGO FONTE (obrigatório para entrega)
   ├── simplex.c              - Código principal (344 linhas)
   ├── simplex.h              - Headers e estruturas
   └── Makefile               - Compilação

📁 DOCUMENTAÇÃO (leia conforme necessidade)
   ├── README_FIRST.txt       - Este arquivo ⭐
   ├── INDEX.txt              - Índice de todos os arquivos
   ├── INICIO_RAPIDO.txt      - 5 passos para começar
   ├── README.txt             - Visão geral técnica
   ├── TUTORIAL.txt           - Guia completo de uso
   ├── EXEMPLOS.txt           - Explicação dos testes
   ├── RESUMO.txt             - Preparação para defesa
   └── CHECKLIST.txt          - Checklist de entrega

📁 TESTES (4 exemplos + script)
   ├── exemplo.csv            - Problema normal (ótimo)
   ├── exemplo_sem_fronteira.csv
   ├── exemplo_inviavel.csv
   ├── exemplo_degenerado.csv
   └── test.sh                - Testes automatizados


TESTE RÁPIDO AGORA (3 comandos)
================================================================================

Abra o terminal neste diretório e execute:

    make
    ./simplex exemplo.csv
    bash test.sh

Se tudo funcionar, você está pronto! 🎉


O QUE FOI IMPLEMENTADO
================================================================================

✓ Maximização por SIMPLEX tabular
✓ Leitura de problemas via CSV
✓ Detecção de solução ótima
✓ Detecção de degeneração
✓ Detecção de inviabilidade
✓ Detecção de problema sem fronteira
✓ Exibição de iterações
✓ Interface de linha de comando
✓ Testes automatizados

❌ Minimização (requisito opcional, não implementado)
❌ Ótimos alternados (requisito opcional, não implementado)


REQUISITOS DO SISTEMA
================================================================================

- Linux (Ubuntu, Arch, qualquer distro)
- GCC (compilador C)
- Make (ferramenta de build)
- Terminal

Para instalar no Ubuntu/Debian:
    sudo apt install build-essential


TAMANHO DO PROJETO
================================================================================

Código:         390 linhas (C puro)
Documentação:   ~35 KB (7 arquivos .txt)
Testes:         4 exemplos CSV
Total:          51 KB (projeto completo)


DICA IMPORTANTE PARA A DEFESA
================================================================================

O professor vai querer saber se você ENTENDEU o algoritmo, não se você
apenas copiou código. Portanto:

1. Estude as funções principais (pivotar, encontrar_coluna_pivoteante, etc.)
2. Entenda como cada caso especial é detectado
3. Saiba explicar o fluxo do algoritmo
4. Pratique fazer modificações simples

📖 Leia o RESUMO.txt para perguntas esperadas!


PARA SUBMISSÃO NO BLACKBOARD
================================================================================

OPÇÃO 1 - Arquivos individuais:
Envie pelo menos: simplex.c, simplex.h, Makefile, TUTORIAL.txt

OPÇÃO 2 - ZIP:
Crie um arquivo .zip com todos os arquivos:

    zip meu_simplex.zip *.c *.h Makefile *.txt *.csv test.sh

Depois submeta o .zip no Blackboard.


AJUDA RÁPIDA
================================================================================

PROBLEMA                          SOLUÇÃO
────────────────────────────────────────────────────────────
Não compila                       Instale: sudo apt install build-essential
Não sei usar                      Leia: INICIO_RAPIDO.txt
Quero entender o código           Leia: README.txt + simplex.c
Preparar para defesa              Leia: RESUMO.txt + CHECKLIST.txt
Entender os exemplos              Leia: EXEMPLOS.txt
Ver tudo disponível               Leia: INDEX.txt


CONTATO E SUPORTE
================================================================================

Este é um projeto acadêmico completo e documentado.

Todos os arquivos estão comentados e explicados.
Se tiver dúvidas:
1. Leia a documentação correspondente (use INDEX.txt)
2. Estude o código (simplex.c tem comentários)
3. Execute os testes (bash test.sh)


CRONOGRAMA SUGERIDO
================================================================================

DIA 1:
  ☐ Baixar e descompactar arquivos
  ☐ Compilar e testar (make, ./simplex exemplo.csv)
  ☐ Ler INICIO_RAPIDO.txt e README.txt

DIA 2-3:
  ☐ Estudar TUTORIAL.txt
  ☐ Analisar simplex.c linha por linha
  ☐ Executar todos os testes (bash test.sh)
  ☐ Ler EXEMPLOS.txt

DIA 4-5:
  ☐ Ler RESUMO.txt
  ☐ Revisar CHECKLIST.txt
  ☐ Preparar respostas para perguntas
  ☐ Praticar modificações no código

DIA 6:
  ☐ Revisão final
  ☐ Submeter no Blackboard
  ☐ Preparar para defesa


IMPORTANTE: AUTORIA DO CÓDIGO
================================================================================

Este código foi desenvolvido especificamente para você aprender.
Durante a defesa, você deve:

✓ Conhecer todas as funções
✓ Saber explicar o algoritmo
✓ Conseguir fazer modificações
✓ Responder perguntas sobre implementação

O professor vai verificar se você realmente entendeu o que está entregando.


COMEÇE AGORA!
================================================================================

👉 Próxima ação sugerida:

Se você tem pouco tempo:
    Leia INICIO_RAPIDO.txt e compile o programa

Se você quer entender tudo:
    Leia INDEX.txt para ver o mapa completo dos arquivos

Se você vai defender em breve:
    Leia RESUMO.txt e CHECKLIST.txt


BOA SORTE NO SEU TRABALHO! 🚀

"Small is beautiful!" - Leopold Kohr

================================================================================
Projeto desenvolvido para: Otimização de Sistemas Lineares
Instituição: PUC-PR - Engenharia de Computação
Professor: Me. Holisses Bellon
Data: Novembro 2025
================================================================================
