#!/bin/bash

# Verifica se o argumento foi fornecido
if [ $# -eq 0 ]; then
    echo "Uso: $0 <nome_do_arquivo.cpp>"
    exit 1
fi

# Nome do arquivo .cpp fornecido como argumento
cpp_file="$1"

# Verifica se a pasta "build" existe, caso não exista, cria-a
if [ ! -d "build" ]; then
    mkdir build
fi

# Entra na pasta "build"
cd build

# Executa o comando "cmake" para configurar o ambiente de compilação
cmake -DFILE_TO_COMPILE="${cpp_file}" ..

# Executa o comando "make" para compilar o projeto
make

# Verifica se o arquivo executável foi criado
if [ -f "${cpp_file%.cpp}" ]; then
    # Move o arquivo executável para a pasta anterior (assumindo que a pasta anterior é o diretório pai)
    mv "${cpp_file%.cpp}" ..
fi

# Retorna para a pasta anterior
cd ..

# Executa o programa compilado com o nome do arquivo .cpp fornecido como argumento (opcional)
if [ -f "${cpp_file%.cpp}" ]; then
    "./${cpp_file%.cpp}"
fi

