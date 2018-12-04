/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Cadastro de EmpresasParceiras e Promoções
 * Copyright 2018 - Dian de Grazia, Letícia Sena e Mateus Tudéia
 * main.cpp - Arquivo gerencia as operações base do sistema,
 * funciona como um CRUD para inserir, consultar, editar e excluir dados
*/

#include "EmpresasParceiras.h"

int main(int argc, char *argv[]) {
    const char *NOME = argc >= 2 ? argv[1] : "empresas.bin";
    const char *NOMEAUX = (argc >= 2 && strcmp(NOME, "empresasAux.bin") == 0) ? "empresasAux2.bin" : "empresasAux.bin";
    EmpresasParceiras empresa(NOME, NOMEAUX);

    bool flag = true;

    char operacao;
    while(flag) {
        cout << endl
             << "Digite (i) para inserir uma Empresa Parceiras;"
             << endl
             << "Digite (p) para imprimir todas as EmpresasParceiras Parceiras;"
             << endl
             << "Digite (d) para deletar uma Empresa Parceiras;"
             << endl
             << "Digite (s) para procurar uma Empresa Parceiras;"
             << endl
             << "Digite (v) para verificar se o arquivo esta aberto;"
             << endl
             << "Digite (e) para exportar todas as EmpresasParceiras Parceiras salvas para um arquivo .txt;"
             << endl
             << "Digite (q) para sair."
             << "---------------------------------------------------------------------------------------------------"
             << endl << endl;
        cin >> operacao;

        switch(operacao) {
            case 'i':
                Empresas emp;
                cout << "ID: ";
                cin >> emp.id;
                while(cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Por favor, digite um NUMERO referente ao ID: ";
                    cin >> emp.id;
                }
                cin.ignore();
                cout << endl << "Nome: ";
                cin.getline(emp.nome, 50);
                cout << endl << "Dominio: ";
                cin.getline(emp.categoria, 50);
                cout << endl << "Telefone: ";
                cin.getline(emp.telefone, 200);
                cout << endl << "Email: ";
                cin.getline(emp.email, 200);
                empresa.inserirEmpresa(emp);
                break;
            case 'p':
                empresa.resgatarDadosEmpresa();
                break;
            case 'd':
                char opcao;
                cout 
                << "Digite (i) para deletar por ID" 
                << endl 
                << "Digite (n) para deletar por Nome"
                << endl;
                cin >> opcao;
                switch(opcao) {
                    case 'i':
                        int id;
                        cout << "Digite o id a ser deletado: ";
                        cin >> id;
                        while(cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Por favor, digite um NUMERO referente ao ID: ";
                            cin >> id;
                        }
                        empresa.deletarEmpresa(id);
                        break;
                    case 'n':
                        char nome[50];
                        cout << "Digite o nome a ser deletado: ";
                        cin.ignore();
                        cin.getline(nome, 50);
                        empresa.deletarEmpresa(nome);
                        break;
                    default:
                        break;
                }
                break;
            case 's':
                int search;
                cout << "Digite o ID a ser procurado: ";
                cin >> search;
                while(cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Por favor, digite um NUMERO referente ao ID: ";
                    cin >> search;
                }
                empresa.resgatarDadosEmpresa(search);
                break;
            case 'v':
                empresa.checarArquivoAberto();
                break;
            case 'e':
                empresa.exportarParaTxt();
                break;
            case 'q':
            default:
                flag = false;
                cout << "Saindo..." << endl;
                break;
        }
    }
}
