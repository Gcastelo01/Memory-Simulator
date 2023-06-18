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
        echo "[!] Erro criando VENV. Instalando python3.10-venvL"

        sudo apt install python3.10-venv -y
        python3 -m venv venv

    fi
fi

echo "[+] Ativando VENV"

source $CURRDIR/venv/bin/activate  

echo "[+] Instalando dependências do Python"

pip install -r $CURRDIR/requirements.txt

echo "[+] Compilando arquivos C"

make

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

python3 ./doc/main.py

echo "[+] Análise concluída! Resultado salvo em $PWD/result.png"
echo "[+] Limpando arquivos de testes..."

rm -r $CURRDIR/logs