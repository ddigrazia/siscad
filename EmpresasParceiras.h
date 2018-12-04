/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Cadastro de Empresas e Promoções
 * Copyright 2018 - Dian de Grazia, Letícia Sena e Mateus Tudéia
 * Empresas.h - Arquivo que declara os atributos e métodos referentes
 * a uma empresa dentro do sistema
*/

#ifndef EMPRESAS_PARCEIRAS_H
#define EMPRESAS_PARCEIRAS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <limits>

using namespace std;

struct Empresas {
        int id;
		char nome[50]; 
		char categoria[50];
		char telefone[14];
		char email[50];
};

class EmpresasParceiras {
	public:
		EmpresasParceiras();
        EmpresasParceiras(const char *NOME, const char *NOMEAUX);
        void inserirEmpresa(Empresas empresa);
        void resgatarDadosEmpresa();
        void resgatarDadosEmpresa(int id);
        int resgatarPrimeiro();
        int resgatarUltimo();
        void checarArquivoAberto();
        void deletarEmpresa(int id);
        void deletarEmpresa(char nome[50]);
        int resgatarQuantidade();
        void exportarParaTxt();
    private:
        fstream _arquivo;
        const char* _nomeArquivo;
        const char* _nomeArquivoAux;
        inline bool _estaAberto();
        int _quantidade;
        int _primeiroId;
        int _ultimoId;
};

#endif
