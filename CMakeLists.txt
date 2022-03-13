cmake_minimum_required(VERSION 3.21)
project(jogo_de_xadrez)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(jogo_de_xadrez
        src/Bispo.cpp
        src/Bispo.hpp
        src/Cavalo.cpp
        src/Cavalo.hpp
        src/Dama.cpp
        src/Dama.hpp
        src/IO_Jogo.cpp
        src/IO_Jogo.hpp
        src/main.cpp
        src/Peao.cpp
        src/Peao.hpp
        src/Peca.cpp
        src/Peca.hpp
        src/Rei.cpp
        src/Rei.hpp
        src/Tabuleiro.cpp
        src/Tabuleiro.hpp
        src/Torre.cpp
        src/Torre.hpp)
