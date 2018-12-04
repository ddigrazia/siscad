#include <iostream>
#include <stdexcept>
#include <queue>
#include <limits>
#include <string>

typedef unsigned TChave;
enum Cor {PRETO, VERMELHO};
using namespace std;

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

class Noh 
{
    friend class ArvoreRN;
    friend class Empresa;
    //friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    public:
        Noh(TChave chave, Empresa empresa);
        void InverterCor();
        bool FilhoEsquerda();
    private:
        Noh* Tio();
        void DesalocarRecursivo();
        Empresa mEmpresa;
        TChave mChave;
        Cor mCor;
        Noh* mEsq;
        Noh* mDir;
        Noh* mPai;
};

class ArvoreRN 
{
    public:
        ArvoreRN();
        ~ArvoreRN();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(TChave chave, Empresa empresa);
    private:
        void ArrumarInsercao(Noh* umNoh);
        void RotacionarDireita(Noh* umNoh);
        void RotacionarEsquerda(Noh* umNoh);
        Noh* mRaiz;
};

// === classe Noh ==============================================================
Noh::Noh(TChave chave, Empresa empresa)
    : mEmpresa(empresa), mChave(chave), mCor(VERMELHO), mEsq(NULL), mDir(NULL), mPai(NULL) {
}

// Desaloca as subÃ¡rvores e depois a si prÃ³prio.
void Noh::DesalocarRecursivo() 
{
	while(mEsq!=NULL){
	delete mEsq; 
	}
	while(mDir!=NULL){
		delete mDir; 
	}
	delete this;
}

// Retorna o tio do nÃ³, ou NULL se nÃ£o houver tio
Noh* Noh::Tio() 
{
	if(mPai != NULL and mPai->mPai != NULL) 
	{
		if (mPai->mPai->mEsq == mPai) 
		{
			return mPai->mPai->mDir;
		}
		return mPai->mPai->mEsq;
	}
	return NULL;
}

void Noh::InverterCor() 
{
	if (mCor == VERMELHO) 
		mCor = PRETO;
	else
		mCor = VERMELHO;
}

bool Noh::FilhoEsquerda() 
{
	if (mPai->mEsq == this)
		return true;
	else
		return false;
}
// === classe ArvoreRN =========================================================
ArvoreRN::ArvoreRN() : mRaiz(NULL) {
}

ArvoreRN::~ArvoreRN() {
	delete mRaiz;
}

// insere uma chave/valor na Ã¡rvore,
// chama ArrumarInsercao para corrigir eventuais problemas
void ArvoreRN::Inserir(TChave chave, Empresa empresa) 
{	
	Noh *novo = new Noh (chave, empresa);
	Noh *aux = mRaiz;
	if (aux == NULL) 
	{
		mRaiz = novo;
		mRaiz->mCor = PRETO;
	}
	else 
	{
		bool inseriu = false;
		while (!inseriu) {
			if (aux->mChave > chave) {
				if (aux->mEsq == NULL) {
					aux->mEsq = novo;
					inseriu = true;
				}
				else {
					aux = aux->mEsq;
				}
			}
			else {
				if (aux->mDir == NULL) {
					aux->mDir = novo;
					inseriu = true;
				}
				else {
					aux = aux->mDir;
				}
					
			}
		}
		novo->mPai = aux;
	}
	if (novo != mRaiz) {
		ArrumarInsercao(novo);
	}
		
}

// procedimento para manter balanceamento apÃ³s inserÃ§Ã£o
void ArvoreRN::ArrumarInsercao(Noh* umNoh) 
{
	Noh *Tio = umNoh->Tio();
	Noh *Avo = umNoh->mPai->mPai;
	Noh *Pai = umNoh->mPai;
	
	if (Avo != NULL) {
		 if (Pai->mCor == VERMELHO and Avo->mCor == PRETO and (Tio != NULL and Tio->mCor == VERMELHO)) {
			Tio->InverterCor();
			Pai->InverterCor();
			Avo->InverterCor();
		}
		else if (Pai->mCor == VERMELHO and Avo->mCor == PRETO and (Tio == NULL or Tio->mCor == PRETO)) {
			if (umNoh->FilhoEsquerda() and Pai->FilhoEsquerda()) {
				RotacionarDireita(Avo);
				Pai->InverterCor();
			}
			else if (!umNoh->FilhoEsquerda() and !Pai->FilhoEsquerda()) {
				RotacionarEsquerda(Avo);
				Pai->InverterCor();
			}
			else if (!umNoh->FilhoEsquerda() and Pai->FilhoEsquerda()) {
				RotacionarEsquerda(Pai);
				RotacionarDireita(Avo);
				umNoh->InverterCor();
			}
			 else if (umNoh->FilhoEsquerda() and !Pai->FilhoEsquerda()) {
				RotacionarDireita(Pai);
				RotacionarEsquerda(Avo);
				umNoh->InverterCor();
			}
			Avo->InverterCor();
		}
		if (mRaiz->mCor == VERMELHO) {
			mRaiz->InverterCor();
		}
	}
}

// rotaÃ§Ã£o Ã  mEsq, muda a mRaiz se necessÃ¡rio
void ArvoreRN::RotacionarEsquerda(Noh* umNoh) 
{
    //salvar quem era o filho a mDir do umNoh
    Noh* aux = umNoh->mDir;
    //umNoh ganha novo filho a mDir, o filho a mEsq do aux
    umNoh->mDir = aux->mEsq;
    //se esse filho a mEsq existir, ele reconhece a paternidade
    if (aux->mEsq != NULL) 
        aux->mEsq->mPai = umNoh;
    //o mPai do umNoh se torna mPai do aux
    if (umNoh->mPai != NULL) 
    {
        if (umNoh->mPai->mEsq == umNoh) {
            umNoh->mPai->mEsq = aux;
        } else {
            umNoh->mPai->mDir = aux;
        }
    } else {//mPai do noh eh a mRaiz, entao aux eha  nova mRaiz
        mRaiz = aux;
    }
    //aux reconhece o novo mPai
    aux->mPai = umNoh->mPai;
    //o mPai do umNoh agora vai ser o aux
    umNoh->mPai = aux;
    //aux reconhece umNoh como seu filho
    aux->mEsq = umNoh;
}

// rotaÃ§Ã£o Ã  mDir, muda a mRaiz se necessÃ¡rio
void ArvoreRN::RotacionarDireita(Noh* umNoh) 
{
    //salvar quem era o filho a mEsq do umNoh
    Noh* antigoFilhoAEsquerda = umNoh->mEsq;
    //umNoh ganha novo filho a mEsq, o filho a mDir do antigoFilhoAEsquerda
    umNoh->mEsq = antigoFilhoAEsquerda->mDir;
    //se esse filho a mDir existir, ele reconhece a nova paternidade
    if (antigoFilhoAEsquerda->mDir != NULL) {
        antigoFilhoAEsquerda->mDir->mPai = umNoh;
    }
    //o mPai do umNoh se torna mPai do aux
    if (umNoh->mPai != NULL) {
        if (umNoh->mPai->mEsq == umNoh) {
            umNoh->mPai->mEsq = antigoFilhoAEsquerda;
        } else {
            umNoh->mPai->mDir = antigoFilhoAEsquerda;
        }
    } else {//mPai do noh eh a mRaiz, entao antigoFilhoAEsquerda eha  nova mRaiz
        mRaiz = antigoFilhoAEsquerda;
    }
    //antigoFilhoAEsquerda reconhece o novo mPai
    antigoFilhoAEsquerda->mPai = umNoh->mPai;
    //o mPai do umNoh agora vai ser o aux
    umNoh->mPai = antigoFilhoAEsquerda;
    //aux reconhece umNoh como seu filho
    antigoFilhoAEsquerda->mDir = umNoh;
}

// Escreve o conteÃºdo da Ã¡rvore nÃ­vel a nÃ­vel
void ArvoreRN::EscreverNivelANivel(ostream& saida) 
{
    queue<Noh*> filhos;
    filhos.push(mRaiz);
    while (not filhos.empty()) 
    {
        unsigned nroNohsNesteNivel = unsigned(filhos.size());
        for (unsigned i = 0; i < nroNohsNesteNivel; ++i) 
        {
            Noh* ptNoh = filhos.front();
            filhos.pop();
            saida << ptNoh << ' ';
            if (ptNoh != NULL) 
            {
                filhos.push(ptNoh->mEsq);
                filhos.push(ptNoh->mDir);
            }
        }
        cout << "\n";
    }
}

// Escreve um nÃ³ (ou NIL).
/*ostream& operator<<(ostream& saida, Noh* ptNoh) 
{
    static char vetLetrasCores[] = "PV";
    if (ptNoh == NULL)
        saida << "NIL";
    else
        saida << '[' << vetLetrasCores[ptNoh->mCor] << ':' << ptNoh->mChave << '/'
              << ptNoh->mEmpresa << ']';
    return saida;
}*/

int main() 
{
    ArvoreRN arvore;
    TChave chave;
    int id;
    string nome;
    string categoria;
    string telefone;
    string email;
    
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
                cin.ignore();
                cout << endl << "Nome: ";
                getline(cin, nome);
                cout << endl << "Dominio: ";
                getline(cin, categoria);
                cout << endl << "Telefone: ";
                getline(cin, telefone);
                cout << endl << "Email: ";
                getline(cin, email);
                cout << endl << "Chave da Árvore: ";
                cin >> chave;
                Empresa emp = new Empresa(id, nome, categoria, telefone, email);
                arvore.Inserir(chave, emp);
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

