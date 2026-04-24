#!/bin/bash

RAIZ="$(cd "$(dirname "$0")/.." && pwd)"
TRADUTOR="$RAIZ/tradutor"
PASSOU=0
FALHOU=0

rodar_teste_valido()
{
    local nome="$1"
    local arquivo_ula="$2"
    local esperado="$3"

    cp "$arquivo_ula" "$RAIZ/testeula.ula"
    cd "$RAIZ"
    saida=$("$TRADUTOR" 2>&1)
    resultado=$(cat "$RAIZ/testeula.hex" 2>/dev/null)
    cd - > /dev/null

    if [ "$resultado" = "$esperado" ]; then
        echo "[OK] $nome"
        PASSOU=$((PASSOU + 1))
    else
        echo "[FALHOU] $nome"
        echo "  Esperado : $(echo "$esperado" | tr '\n' '|')"
        echo "  Obtido   : $(echo "$resultado" | tr '\n' '|')"
        FALHOU=$((FALHOU + 1))
    fi
}

rodar_teste_valido_arquivo()
{
    local nome="$1"
    local arquivo_ula="$2"
    local arquivo_esperado="$3"

    cp "$arquivo_ula" "$RAIZ/testeula.ula"
    cd "$RAIZ"
    saida=$("$TRADUTOR" 2>&1)
    resultado=$(cat "$RAIZ/testeula.hex" 2>/dev/null)
    cd - > /dev/null

    esperado=$(cat "$arquivo_esperado" 2>/dev/null)

    if [ "$resultado" = "$esperado" ]; then
        echo "[OK] $nome"
        PASSOU=$((PASSOU + 1))
    else
        diff_saida=$(diff <(echo "$esperado") <(echo "$resultado"))
        echo "[FALHOU] $nome"
        echo "  Diff (esperado vs obtido):"
        echo "$diff_saida" | head -20
        FALHOU=$((FALHOU + 1))
    fi
}

rodar_teste_erro()
{
    local nome="$1"
    local arquivo_ula="$2"
    local msg_esperada="$3"

    cp "$arquivo_ula" "$RAIZ/testeula.ula"
    cd "$RAIZ"
    saida=$("$TRADUTOR" 2>&1)
    cd - > /dev/null

    if echo "$saida" | grep -q "$msg_esperada"; then
        echo "[OK] $nome"
        PASSOU=$((PASSOU + 1))
    else
        echo "[FALHOU] $nome"
        echo "  Esperado conter : $msg_esperada"
        echo "  Saida obtida    : $saida"
        FALHOU=$((FALHOU + 1))
    fi
}

cd "$(dirname "$0")"

echo "=== Bateria de Testes ==="
echo ""

rodar_teste_valido \
    "T1 - Programa basico (exemplo do PDF)" \
    "t1_basico.ula" \
    "C6B"

rodar_teste_valido \
    "T2 - Multiplas instrucoes (exemplo do PDF)" \
    "t2_multiplas_instrucoes.ula" \
    "C6B
A3E
A34
D35"

rodar_teste_valido \
    "T3 - Todos os 16 mnemonicos" \
    "t3_todos_mnemonicos.ula" \
    "120
121
122
123
124
125
126
127
128
129
12A
12B
12C
12D
12E
12F"

rodar_teste_valido \
    "T4 - Valores limite (X=0,Y=0 e X=15,Y=15)" \
    "t4_valores_limite.ula" \
    "00A
FF9"

rodar_teste_erro \
    "T5 - Erro: linha em branco" \
    "t5_erro_linha_branca.ula" \
    "Linha em branco"

rodar_teste_erro \
    "T6 - Erro: falta ponto e virgula" \
    "t6_erro_sem_ponto_virgula.ula" \
    "Faltando ';'"

rodar_teste_erro \
    "T7 - Erro: mnemonico invalido" \
    "t7_erro_mnemonico_invalido.ula" \
    "invalido"

rodar_teste_valido_arquivo \
    "T8 - 200 linhas com variaveis independentes" \
    "t8_200_linhas.ula" \
    "t8_200_linhas_esperado.hex"

echo ""
echo "=== Resultado: $PASSOU passou(aram), $FALHOU falhou(aram) ==="
