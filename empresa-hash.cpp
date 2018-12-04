#include <iostream>
#include <string>
#include <limits>

using namespace std;

int funcaoHash(string chave) 
{
    return chave.size() % 23;
}

class Empresa
{
	public:
		Empresa(int _id, string _nome, string _categoria, string _telefone, string _email);
		~Empresa();
	private:
		int mId;
		string mNome;
		string mCategoria;
		string mTelefone;
		string mEmail;
};

Empresa::Empresa(int _id, string _nome, string _categoria, string _telefone, string _email)
{
	mId = _id;
	mNome = _nome;
	mCategoria = _categoria;
	mTelefone = _telefone;
	mEmail = _email;
}

class noh 
{
    friend class tabelaHash;
    private:
        string mChave;
        string mId;
        noh* mProximo = NULL;
    public:
        noh(string chave, int id) 
        {
            mChave = chave;
            mId = id;
        }
};

class tabelaHash 
{
    private:
        // vetor de ponteiros de nós
        noh** mElementos;
        int mCapacidade;
    public:
        tabelaHash(int cap = 23);
        ~tabelaHash();
        void insere(string chave, int id, string nome, string categoria, string telefone, string email);
        string recupera(string c);
};

// construtor padrão
tabelaHash::tabelaHash(int cap) 
{
    mElementos = new noh*[cap];
    mCapacidade = cap;
    for (int i = 0; i < cap; i++)
        mElementos[i] = NULL;
}

// destrutor
tabelaHash::~tabelaHash() 
{
    for (int i=0; i < mCapacidade; i++) 
    {
        noh* iter = mElementos[i];
        // percorre a lista removendo todos os nós
        while (iter != NULL) 
        {
            noh* aux = iter;
            iter = iter-> mProximo;
            delete aux;
        }
    }
    delete[] mElementos;
}

// Insere um valor v com chave c.
void tabelaHash::insere(string chave, int id, string nome, string categoria, string telefone, string email) 
{
    int numeroHash = funcaoHash(chave);
    Empresa novaEmpresa = new Empresa(id, nome, categoria, telefone, email);

    if (mElementos[numeroHash] == NULL) 
    {
        noh* novoNoh = new noh(chave, id);
        mElementos[numeroHash] = novoNoh;
    } 
    else 
    {
        if(recupera(chave) == "NULL")
        {
            noh* iter = mElementos[numeroHash];
            while (iter->mProximo != NULL)
            {
                iter = iter->mProximo;
            }
            noh* novoNoh = new noh(chave, id);
            iter->mProximo = novoNoh;
        }
    }
}

// recupera um valor associado a uma dada chave
string tabelaHash::recupera(string c) 
{
    int h;
    h = funcaoHash(c);

    if ((mElementos[h] != NULL) and (mElementos[h]->mChave == c)) 
    {
        return mElementos[h]->mId;
    } 
    else 
    {
        noh* iter = mElementos[h];

        while ((iter != NULL) and (iter->mChave != c)) 
        {
            iter = iter->mProximo;
        }

        if ((iter != NULL) and (iter->mChave == c)) 
        {
            return iter->mId;
        } 
        else 
        {
            return "NULL";
        }
    }
}

int main() 
{
    tabelaHash th;
    int id;
    string nome;
    string categoria;
    string telefone;
    string email;
    string chave;
    
    char operacao;
   
	do
	{
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
                cout << "ID: ";
                cin >> id;
                while(cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Por favor, digite um NUMERO referente ao ID: ";
                    cin >> id;
                }
                cout << endl << "Chave do Hash: ";
                getline(cin, chave);
                cin.ignore();
                cout << endl << "Nome: ";
                getline(cin, nome);
                cout << endl << "Dominio: ";
                getline(cin, categoria);
                cout << endl << "Telefone: ";
                getline(cin, telefone);
                cout << endl << "Email: ";
                getline(cin, email);
                th.insere(chave, id, nome, categoria, telefone, email);
                break;
				/*case 'e': // Escrever nÃ³s nÃ­vel a nÃ­vel
                arvore.EscreverNivelANivel(cout);
                break;*/
            case 'f': // Finalizar o programa
                // vai verificar depois
                break;
            default:
                cerr << "Opção Inválida\n";
        }
    } while (operacao != 'f');
    return 0;
}

/*int main( ) 
{
    tabelaHash th;
    int qtdade;
    string chave;
    string valor;

    // insercao na tabela
    cin >> qtdade;
    for (int i=0; i < qtdade; i++) 
    {
        cin >> chave;
        cin.ignore();
        getline(cin, valor);
        th.insere(chave,valor);
    }

    // recupera valores
    cin >> chave;
    while (chave != "-1")
    {
        cout << "[" << chave << "] " << "=> " << th.recupera(chave) << endl;
        cin >> chave;
    }

    return 0;
}*/
