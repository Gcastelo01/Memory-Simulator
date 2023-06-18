#!/usr/bin/env bash

CURRDIR=$(dirname "$(readlink -f "$0")")
VENV_DIR="$PWD/venv/bin"

mkdir $CURRDIR/logs

if [ ! -d "$CURRDIR/venv" ]
then
    echo "[+] Criando ambiente virtual Python3 para execução do script..."
    python3 -m venv venv

    if [ $? -ne 0 ]
    then
        echo "[!] Erro criando VENV.  Deseja tentar instalar o gerenciador de venv python? [y/n]"
        read resp

        if [ $resp = 'y' ]
        then
            apt install python3-venv -y
            python3 -m venv venv
        else
            exit 1
        fi
    fi
fi

echo "[+] Ativando VENV"

source $CURRDIR/venv/bin/activate  

echo "[+] Instalando dependências do Python"

pip install -r requirements.txt

echo "[+] Compilando arquivos C"

/usr/bin/gcc $PWD/src/tp2virtual.c -o tp2virtual

echo "[+] Iniciando testes"

for j  in "compilador" "compressor" "matriz" "simulador"
do
    for i in 2 4 8 16 32 64 
    do 
        ./tp2virtual lru ./logs/$j.log $i 128 > $CURRDIR/logs/memtest-lru-$j-$i.log

        ./tp2virtual random ./logs/$j.log $i 128  > $CURRDIR/logs/memtest-random-$j-$i.log

        ./tp2virtual 2a ./logs/$j.log $i 128  > $CURRDIR/logs/memtest-2a-$j-$i.log

        ./tp2virtual fifo ./logs/$j.log $i 128  > $CURRDIR/logs/memtest-fifo-$j-$i.log
    done
done

echo "[+] Produzindo análise"

python3 main.py