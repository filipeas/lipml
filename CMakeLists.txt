cmake_minimum_required(VERSION 3.10)
project(LIPML)

# Configuração do padrão C++ para o projeto
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona os arquivos de cabeçalho
include_directories(include)

# Adiciona todos os arquivos fonte na pasta src ao executável
file(GLOB SOURCES "src/*.cpp")

# Cria o executável a partir dos arquivos fonte
add_executable(lipml ${SOURCES})