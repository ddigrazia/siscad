/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Cadastro de EmpresasParceiras e Promoções
 * Copyright 2018 - Dian de Grazia, Letícia Sena e Mateus Tudéia
 * EmpresasParceiras.cpp - Arquivo gerencia os dados e ações referentes a uma
 * Empresa dentro do sistema (inserção, edição, deleção, busca)
*/

#include "EmpresasParceiras.h"

EmpresasParceiras::EmpresasParceiras(const char *NOME, const char *NOMEAUX) {
    _arquivo.open(NOME, ios_base::in | ios_base::out | ios_base::binary | ios_base::app);
    _nomeArquivo = NOME;
    _nomeArquivoAux = NOMEAUX;
    _quantidade = resgatarQuantidade();
    _primeiroId = resgatarPrimeiro();
    _ultimoId = resgatarUltimo();
}

inline bool EmpresasParceiras::_estaAberto() {
    return _arquivo.is_open();
}

void EmpresasParceiras::inserirEmpresa(Empresas empresa) {
    if(empresa.id <= 0){
        cout << "O id do empresa tem que ser maior ou igual a 1." << endl;
        return;
    }
    if(_estaAberto()) {
        fstream arquivoAux(_nomeArquivoAux, ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
        Empresas empresaAux;
        
        int counter = 0;
        bool inserted = false;        
        _arquivo.clear();
        _arquivo.seekg(0, _arquivo.beg);

        arquivoAux.clear();
        arquivoAux.seekg(0, arquivoAux.beg);
        
        while(_arquivo.read((char *) &empresaAux, sizeof(Empresas))) {
            if(empresaAux.id == empresa.id) {
                cout << endl << "Empresa com o id " << empresa.id << " ja existe." << endl;
                arquivoAux.close();
                remove(_nomeArquivoAux);
                return;
            }
            if(empresaAux.id < empresa.id || inserted) {
                ++counter;
            } else {
                arquivoAux.write((char *) &empresa, sizeof(Empresas));
                counter += 2;
                inserted = true;
            }
            arquivoAux.write((char *) &empresaAux, sizeof(Empresas));
        }
        if(counter == 0 || !inserted) {
            _arquivo.clear();
            _arquivo.seekg(0, _arquivo.beg);
            _arquivo.write((char *) &empresa, sizeof(Empresas));
        } else {
            _arquivo.close();
            _arquivo.open(_nomeArquivo, ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
            arquivoAux.clear();
            arquivoAux.seekg(0, arquivoAux.beg);
            while(arquivoAux.read((char *) &empresaAux, sizeof(Empresas))) {
                _arquivo.write((char *) &empresaAux, sizeof(Empresas));
            }
            _arquivo.close();
            _arquivo.open(_nomeArquivo, ios_base::in | ios_base::out | ios_base::binary | ios_base::app);
        }
        arquivoAux.close();
        remove(_nomeArquivoAux);
        ++_quantidade;
        _ultimoId = resgatarUltimo();
        _primeiroId = resgatarPrimeiro();
        cout << "Empresa inserido com sucesso." << endl;
    }
}

void EmpresasParceiras::resgatarDadosEmpresa() {
    if(_estaAberto()) {
        if(_quantidade > 0){
            Empresas empresa;
            _arquivo.clear();
            _arquivo.seekg(0, _arquivo.beg);
            cout << endl;
            while(_arquivo.read((char *) &empresa, sizeof(Empresas))) {
                cout << "id: " << empresa.id << endl;
                cout << "nome: " << empresa.nome << endl;
                cout << "categoria: " << empresa.categoria << endl;
                cout << "telefone: " << empresa.telefone << endl;
                cout << "email: " << empresa.email << endl;
                cout << "---------------------------------------" << endl;
            }
            cout << endl;
        } else {
            cout << "Ops! Não temos nenhuma Empresa cadastrada." << endl;
        }
    }
}

void EmpresasParceiras::resgatarDadosEmpresa(int id) {
    if(_estaAberto()) {
        if(_quantidade > 0) {
            if(id >= _primeiroId && id <= _ultimoId){
                const int SIZE = sizeof(Empresas);
                int positionLastEntry;
                bool found = false;
                
                _arquivo.clear();
                positionLastEntry = _arquivo.seekg(-SIZE, _arquivo.end).tellg();
                Empresas empresaAux;
                
                int number = positionLastEntry/SIZE + 1;

                int first = 0,
                    last = number,
                    middle = number/2;
                
                while(first <= last && !found) {
                    middle = (first + last)/2;
                    
                    _arquivo.clear();
                    _arquivo.seekg(middle * SIZE);
                    _arquivo.read((char *) &empresaAux, sizeof(Empresas));

                    if(empresaAux.id < id) {
                        first = middle + 1;
                    } else if(empresaAux.id > id) {
                        last = middle - 1;
                    } else {
                        found = true;
                    }
                }
                if(found){
                    cout << "id: "        << empresaAux.id        << endl;
                    cout << "nome: "      << empresaAux.nome      << endl;
					cout << "categoria: "   << empresaAux.categoria   << endl;
					cout << "telefone: " << empresaAux.telefone << endl;
					cout << "email: " << empresaAux.email << endl;
                    cout << "---------------------------------------" << endl;
                    return;
                } else {
                    cout << "Nenhuma empresa foi encontrado com o id " << id << "." << endl;
                }
            } else {
                cout << "Nenhuma empresa foi encontrado com o id " << id << "." << endl;
            }
        } else {
            cout << "Nao existe nenhuma empresa inserido." << endl;
        }
    }
}

int EmpresasParceiras::resgatarPrimeiro() {
    if(_estaAberto() && _quantidade) {
        _arquivo.clear();
        _arquivo.seekg(0, _arquivo.beg);
        Empresas empresa;
        _arquivo.read((char *) &empresa, sizeof(Empresas));
        return empresa.id;
    }
    return -1;
}

int EmpresasParceiras::resgatarUltimo() {
    if(_estaAberto() && _quantidade) {
        _arquivo.clear();
        _arquivo.seekg(-sizeof(Empresas), _arquivo.end);
        Empresas empresa;
        _arquivo.read((char *) &empresa, sizeof(Empresas));
        return empresa.id;
    }
    return -1;
}

void EmpresasParceiras::checarArquivoAberto() {
    cout << (_estaAberto() ? "Sim" : "Nao") << endl;
}

void EmpresasParceiras::deletarEmpresa(int id) {
    if(_estaAberto()) {
        if(_quantidade > 0){
            fstream arquivoAux(_nomeArquivoAux, ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
            Empresas empresaAux;

            bool exists = false;

            _arquivo.clear();
            _arquivo.seekg(0, _arquivo.beg);

            arquivoAux.clear();
            arquivoAux.seekg(0, arquivoAux.beg);

            while(_arquivo.read((char *) &empresaAux, sizeof(Empresas))) {
                if(empresaAux.id != id) {
                    arquivoAux.write((char *) &empresaAux, sizeof(Empresas));
                } else {
                    exists = true;
                }
            }
            if(exists) {
                _arquivo.close();
                _arquivo.open(_nomeArquivo, ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
                arquivoAux.clear();
                arquivoAux.seekg(0, arquivoAux.beg);
                while(arquivoAux.read((char *) &empresaAux, sizeof(Empresas))) {
                    _arquivo.write((char *) &empresaAux, sizeof(Empresas));
                }
                _arquivo.close();
                _arquivo.open(_nomeArquivo, ios_base::in | ios_base::out | ios_base::binary | ios_base::app);
                --_quantidade;
                _ultimoId = resgatarUltimo();
                _primeiroId = resgatarPrimeiro();
                cout << "Empresa com o id " << id << " foi deleteda com sucesso." << endl;
            } else {
                cout << "Nao existe empresa com o id " << id << " no arquivo." << endl;
            }
            arquivoAux.close();
            remove(_nomeArquivoAux);
        } else {
            cout << "Nao existe nenhuma empresa inserido." << endl;
        }
    }
}

void EmpresasParceiras::deletarEmpresa(char nome[50]) {
    if(_estaAberto()) {
        if(_quantidade > 0){
            fstream arquivoAux(_nomeArquivoAux, ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
            Empresas empresaAux;

            bool exists = false;

            _arquivo.clear();
            _arquivo.seekg(0, _arquivo.beg);

            arquivoAux.clear();
            arquivoAux.seekg(0, arquivoAux.beg);

            while(_arquivo.read((char *) &empresaAux, sizeof(Empresas))) {
                if(strcmp(empresaAux.nome, nome) != 0 || exists) {
                    arquivoAux.write((char *) &empresaAux, sizeof(Empresas));
                } else {
                    exists = true;
                }
            }
            if(exists) {
                _arquivo.close();
                _arquivo.open(_nomeArquivo, ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
                arquivoAux.clear();
                arquivoAux.seekg(0, arquivoAux.beg);
                while(arquivoAux.read((char *) &empresaAux, sizeof(Empresas))) {
                    _arquivo.write((char *) &empresaAux, sizeof(Empresas));
                }
                _arquivo.close();
                _arquivo.open(_nomeArquivo, ios_base::in | ios_base::out | ios_base::binary | ios_base::app);
                --_quantidade;
                _ultimoId = resgatarUltimo();
                _primeiroId = resgatarPrimeiro();
                cout << "Empresa com o nome " << nome << " foi deleteda com sucesso." << endl;
            } else {
                cout << "Nao existe empresa com o nome " << nome << " no arquivo." << endl;
            }
            arquivoAux.close();
            remove(_nomeArquivoAux);
        } else {
            cout << "Nao existe nenhuma empresa inserida." << endl;
        }
    }
}

int EmpresasParceiras::resgatarQuantidade() {
    int counter = 0;
    if(_estaAberto()) {
         Empresas empresa;
        _arquivo.clear();
        _arquivo.seekg(0, _arquivo.beg);
        while(_arquivo.read((char *) &empresa, sizeof(Empresas))) {
            ++counter;
        }
    }
    return counter;
}

void EmpresasParceiras::exportarParaTxt() {
    if(_estaAberto()) {
        ofstream txtFile("empresas.txt");
        Empresas empresaAux;
        _arquivo.clear();
        _arquivo.seekg(0, _arquivo.beg);
        while(_arquivo.read((char *) &empresaAux, sizeof(Empresas))) {
            txtFile << "id: "        << empresaAux.id        << endl;
            txtFile << "nome: "      << empresaAux.nome      << endl;
			txtFile << "categoria: "   << empresaAux.categoria   << endl;
			txtFile << "telefone: " << empresaAux.telefone << endl;
			txtFile << "email: " << empresaAux.email << endl;
            txtFile << "---------------------------------------" << endl;
        }
        cout << "EmpresasParceiras exportadas com sucesso para o arquivo \"empresas.txt\"." << endl;
        txtFile.close();
    }
}
