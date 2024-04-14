#!/bin/bash

# Deleta pasta se existir
rm -rf build

# Criar diretório build se não existir
mkdir -p build

# Entrar no diretório build
cd build

# Executar o CMake
cmake ..

# Compilar o projeto com make
make