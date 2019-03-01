#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;
#include "IO_Jogo.hpp"
IO_Jogo::IO_Jogo() {}

IO_Jogo::~IO_Jogo() {}

void IO_Jogo::Interface() {
  int Resp = 0;
  cout << "Opções de Jogo:\n";
  cout << "0 . Iniciar novo jogo\n";
  cout << "1 . Iniciar jogo a partir de arquivo\n";
  cout << "R: ";
  cin >> Resp;

  if (Resp == 0) {
    jogaJogo();
  } else if (Resp == 1) {
    string Keyboard;
    cout << "Nome do arquivo [.dat]: ";
    cin >> Keyboard;
    jogaJogo(Keyboard);
  }
}

void IO_Jogo::jogaJogo() {
  string   jogada = "Yay!";
  ofstream jogo;
  jogo.open("Log.dat", ios::out);
  int Xf, Yf;

  // Verificar se for pra fora do Tabuleiro?
  if (jogo.is_open()) {
    while (jogada != "Desisto") {
      m_Tabuleiro.printTab();
      cout << "Jogada: ";
      cin >> jogada;
      if (islower(jogada[0])) {     // Entra se for peão
        if (jogada.size() == 2) {   // Ex: e4
          Xf = jogada[0] - 'a';
          Yf = jogada[1] - '0' - 1;
          if (m_Tabuleiro.movePeca('P', Xf, Yf)) {
            jogo << jogada << (m_Tabuleiro.getVez() == 'B' ? " " : "\n");
          } else {
            m_Tabuleiro.trocaVez();
          }
        } else if (jogada.size() == 3) {   // Ex: e4+ ou e8B
          Xf = jogada[0] - 'a';
          Yf = jogada[1] - '0' - 1;
          if (m_Tabuleiro.movePeca('P', Xf, Yf)) {
            jogo << jogada << (m_Tabuleiro.getVez() == 'B' ? " " : "\n");
            if (jogada[3] == '+') {
              if (m_Tabuleiro.xeque(Xf, Yf, m_Tabuleiro.getVez())) {
                jogada = "Desisto";
              }
            } else {
              m_Tabuleiro.promocao(jogada[2], Xf, Yf);
            }
          } else {
            m_Tabuleiro.trocaVez();
          }
        } else if (jogada.size() == 4) {   // Ex: exd4
          Xf = jogada[2] - 'a';
          Yf = jogada[3] - '0' - 1;
          if (m_Tabuleiro.desambiguacao('P', jogada[0], Xf, Yf, true)) {
            m_Tabuleiro.somaPecasComidas();
            jogo << jogada << (m_Tabuleiro.getVez() == 'B' ? " " : "\n");
          } else {
            m_Tabuleiro.trocaVez();
          }
        } else {
          Xf = jogada[2] - 'a';
          Yf = jogada[3] - '0' - 1;
          if (m_Tabuleiro.enPassant(jogada[0] - 'a', Xf, Yf)) {
            jogo << jogada << (m_Tabuleiro.getVez() == 'B' ? " " : "\n");
            m_Tabuleiro.somaPecasComidas();
          }
        }
      } else {                      // Entra se não for peão
        if (jogada.size() == 3) {   // Ex: O-O ou Cb5
          if (jogada[0] == 'O' || jogada[0] == '0') {
            m_Tabuleiro.roque<false>();
          } else {
            Xf = jogada[1] - 'a';
            Yf = jogada[2] - '0' - 1;
            if (m_Tabuleiro.movePeca(jogada[0], Xf, Yf)) {
              jogo << jogada << (m_Tabuleiro.getVez() == 'B' ? " " : "\n");
            } else {
              m_Tabuleiro.trocaVez();
            }
          }
        } else if (jogada.size() == 4) {   // Ex: Cxd4 ou Cd4+ ou Cad4
          if (jogada[1] == 'x') {
            Xf = jogada[2] - 'a';
            Yf = jogada[3] - '0' - 1;
            if (m_Tabuleiro.movePeca(jogada[0], Xf, Yf, true)) {
              m_Tabuleiro.somaPecasComidas();
              jogo << jogada << (m_Tabuleiro.getVez() == 'B' ? " " : "\n");
            } else {
              m_Tabuleiro.trocaVez();
            }
          } else if (jogada[3] == '+') {
            Xf = jogada[1] - 'a';
            Yf = jogada[2] - '0' - 1;
            if (m_Tabuleiro.movePeca(jogada[0], Xf, Yf)) {
              jogo << jogada << (m_Tabuleiro.getVez() == 'B' ? " " : "\n");
              m_Tabuleiro.printTab();
              if (m_Tabuleiro.xeque(Xf, Yf, m_Tabuleiro.getVez())) {
                jogada = "Desisto";
              }
            } else {
              m_Tabuleiro.trocaVez();
            }
          } else {
            Xf = jogada[2] - 'a';
            Yf = jogada[3] - '0' - 1;
            m_Tabuleiro.desambiguacao(
              jogada[0],
              (isalpha(jogada[1]) ? jogada[1] - 'a' : jogada[1] - '0' - 1), Xf,
              Yf);   // recebe se come ou n
          }
        } else if (jogada.size() == 5) {   // Ex: O-O-O ou Caxd4 ou Cxd4+
          if (jogada[0] == 'O' || jogada[0] == '0') {
            m_Tabuleiro.roque<true>();
          } else {
            Xf = jogada[3] - 'a';
            Yf = jogada[4] - '0' - 1;
            if (m_Tabuleiro.desambiguacao(
                  jogada[0],
                  (isalpha(jogada[1]) ? jogada[1] - 'a' : jogada[1] - '0' - 1),
                  Xf, Yf, true)) {
              jogo << jogada << (m_Tabuleiro.getVez() == 'B' ? " " : "\n");
              m_Tabuleiro.somaPecasComidas();
            }
          }
        }
      }
      m_Tabuleiro.trocaVez();
    }
  }

  if (jogada == "Desisto") {
    jogo << "FIM";
  }
  cout << "Fim de jogo!\nJogador \033[1;"
       << (m_Tabuleiro.getVez() == 'B' ? "36mBranco" : "35mPreto")
       << "\033[0m venceu!\nPeças capturadas por \033[1;36mBranco\033[0m: "
       << m_Tabuleiro.getPecasComidas('B')
       << "\nPeças capturadas por \033[1;35mPreto\033[0m: "
       << m_Tabuleiro.getPecasComidas('P') << endl;
  jogo.close();
}

void IO_Jogo::jogaJogo(string t_Keyboard) {
  ifstream jogo;
  string   jogada = "Yay!";
  jogo.open(t_Keyboard.c_str(), ios::in);
  int Xf, Yf;

  if (jogo.is_open() && jogo.peek() != std::ifstream::traits_type::eof()) {
    while (!jogo.eof()) {
      m_Tabuleiro.printTab();
      jogo >> jogada;
      if (jogada == "FIM") {
        m_Tabuleiro.trocaVez();
        break;
      }
      if (islower(jogada[0])) {     // Entra se for peão
        if (jogada.size() == 2) {   // Ex: e4
          Xf = jogada[0] - 'a';
          Yf = jogada[1] - '0' - 1;
          m_Tabuleiro.movePeca('P', Xf, Yf);
        } else if (jogada.size() == 3) {   // Ex: e4+ ou e8B
          Xf = jogada[0] - 'a';
          Yf = jogada[1] - '0' - 1;
          if (m_Tabuleiro.movePeca('P', Xf, Yf)) {
            if (jogada[3] == '+') {
              if (m_Tabuleiro.xeque(Xf, Yf, m_Tabuleiro.getVez())) {
                jogada = "Desisto";
              }
            } else {
              m_Tabuleiro.promocao(jogada[2], Xf, Yf);
            }
          }
        } else if (jogada.size() == 4) {   // Ex: exd4
          Xf = jogada[2] - 'a';
          Yf = jogada[3] - '0' - 1;
          if (m_Tabuleiro.desambiguacao('P', jogada[0], Xf, Yf, true)) {
            m_Tabuleiro.somaPecasComidas();
          }
        } else {
          Xf = jogada[2] - 'a';
          Yf = jogada[3] - '0' - 1;
          if (m_Tabuleiro.enPassant(jogada[0] - 'a', Xf, Yf)) {
            m_Tabuleiro.somaPecasComidas();
          }
        }
      } else {                      // Entra se não for peão
        if (jogada.size() == 3) {   // Ex: O-O ou Cb5
          if (jogada[0] == 'O' || jogada[0] == '0') {
            m_Tabuleiro.roque<false>();
          } else {
            Xf = jogada[1] - 'a';
            Yf = jogada[2] - '0' - 1;
            m_Tabuleiro.movePeca(jogada[0], Xf, Yf);
            cout << jogada[0] << jogada[1] << jogada[2] << endl;
          }
        } else if (jogada.size() == 4) {   // Ex: Cxd4 ou Cd4+ ou Cad4
          if (jogada[1] == 'x') {
            Xf = jogada[2] - 'a';
            Yf = jogada[3] - '0' - 1;
            if (m_Tabuleiro.movePeca(jogada[0], Xf, Yf, true)) {
              m_Tabuleiro.somaPecasComidas();
            }
          } else if (jogada[3] == '+') {
            Xf = jogada[1] - 'a';
            Yf = jogada[2] - '0' - 1;
            if (m_Tabuleiro.movePeca(jogada[0], Xf, Yf)) {
              if (m_Tabuleiro.xeque(Xf, Yf, m_Tabuleiro.getVez())) {
                jogada = "Desisto";
              }
            }
          } else {
            Xf = jogada[2] - 'a';
            Yf = jogada[3] - '0' - 1;
            m_Tabuleiro.desambiguacao(
              jogada[0],
              (isalpha(jogada[1]) ? jogada[1] - 'a' : jogada[1] - '0' - 1), Xf,
              Yf);   // recebe se come ou n
          }
        } else if (jogada.size() == 5) {   // Ex: O-O-O ou Caxd4 ou Cxc7+
          if (jogada[0] == 'O' || jogada[0] == '0') {
            m_Tabuleiro.roque<true>();
          } else if (jogada[1] == 'x' && jogada[4] == '+') {
            Xf = jogada[2] - 'a';
            Yf = jogada[3] - '0' - 1;
            if (m_Tabuleiro.movePeca(jogada[0], Xf, Yf, true)) {
              m_Tabuleiro.somaPecasComidas();
              if (m_Tabuleiro.xeque(Xf, Yf, m_Tabuleiro.getVez())) {
                jogada = "Desisto";
              }
            }
          } else {
            Xf = jogada[3] - 'a';
            Yf = jogada[4] - '0' - 1;
            m_Tabuleiro.desambiguacao(
              jogada[0],
              (isalpha(jogada[1]) ? jogada[1] - 'a' : jogada[1] - '0' - 1), Xf,
              Yf, true);   // come = true
          }
        }
      }
      m_Tabuleiro.trocaVez();
    }
  } else {
    m_Tabuleiro.trocaVez();
  }

  jogo.close();
  if (jogada != "Desisto") {
    m_Tabuleiro.trocaVez();
    jogaJogo();
  } else {
    m_Tabuleiro.printTab();
    cout << "Fim de jogo!\nJogador \033[1;"
         << (m_Tabuleiro.getVez() != 'B' ? "36mBranco" : "35mPreto")
         << "\033[0m venceu!\nPeças capturadas por \033[1;36mBranco\033[0m: "
         << m_Tabuleiro.getPecasComidas('B')
         << "\nPeças capturadas por \033[1;35mPreto\033[0m: "
         << m_Tabuleiro.getPecasComidas('P') << endl;
  }
}
