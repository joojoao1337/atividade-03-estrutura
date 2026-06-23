#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Estrutura para armazenar os dados do Aluno
struct Aluno {
    int matricula;
    string nome;
    string curso;
};

// Estrutura do Nó da Árvore
struct No {
    Aluno aluno;
    No* esquerda;
    No* direita;

    No(Aluno a) {
        aluno = a;
        esquerda = nullptr;
        direita = nullptr;
    }
};

// Classe da Árvore Binária de Busca (ABB)
class ArvoreAlunos {
private:
    No* raiz;

    // Função auxiliar recursiva para inserção (Ordenada pelo Nome)
    No* inserirRecursivo(No* no, Aluno aluno) {
        if (no == nullptr) {
            return new No(aluno);
        }

        // Comparação alfabética (case-sensitive padrão do C++)
        if (aluno.nome < no->aluno.nome) {
            no->esquerda = inserirRecursivo(no->esquerda, aluno);
        } else {
            no->direita = inserirRecursivo(no->direita, aluno);
        }

        return no;
    }

    // Função auxiliar recursiva para busca por nome
    No* buscarRecursivo(No* no, string nome) {
        if (no == nullptr || no->aluno.nome == nome) {
            return no;
        }

        if (nome < no->aluno.nome) {
            return buscarRecursivo(no->esquerda, nome);
        }
        return buscarRecursivo(no->direita, nome);
    }

    // Função auxiliar para percurso Em-Ordem (Exibe em ordem alfabética)
    void exibirEmOrdemRecursivo(No* no) {
        if (no != nullptr) {
            exibirEmOrdemRecursivo(no->esquerda);
            cout << no->aluno.nome << " - Matrícula: " << no->aluno.matricula 
                 << " - Curso: " << no->aluno.curso << endl;
            exibirEmOrdemRecursivo(no->direita);
        }
    }

    // Função auxiliar para contar o total de alunos
    int contarAlunosRecursivo(No* no) {
        if (no == nullptr) return 0;
        return 1 + contarAlunosRecursivo(no->esquerda) + contarAlunosRecursivo(no->direita);
    }

    // Função auxiliar para calcular a altura da árvore
    int calcularAlturaRecursivo(No* no) {
        if (no == nullptr) return -1; // Árvore vazia tem altura -1 (ou 0 dependendo da convenção)
        int altEsquerda = calcularAlturaRecursivo(no->esquerda);
        int altDireita = calcularAlturaRecursivo(no->direita);
        return 1 + max(altEsquerda, altDireita);
    }

public:
    ArvoreAlunos() {
        raiz = nullptr;
    }

    void inserir(Aluno aluno) {
        raiz = inserirRecursivo(raiz, aluno);
    }

    void buscar(string nome) {
        No* resultado = buscarRecursivo(raiz, nome);
        if (resultado != nullptr) {
            cout << "\n--- Aluno Encontrado ---" << endl;
            cout << "Matrícula: " << resultado->aluno.matricula << endl;
            cout << "Nome: " << resultado->aluno.nome << endl;
            cout << "Curso: " << resultado->aluno.curso << endl;
        } else {
            cout << "\nAluno '" << nome << "' não encontrado." << endl;
        }
    }

    void exibirAlfabetico() {
        if (raiz == nullptr) {
            cout << "Árvore vazia." << endl;
            return;
        }
        exibirEmOrdemRecursivo(raiz);
    }

    int getTotalAlunos() {
        return contarAlunosRecursivo(raiz);
    }

    int getAltura() {
        return calcularAlturaRecursivo(raiz);
    }
};

// Menu interativo para testar o sistema
int main() {
    ArvoreAlunos arvore;
    int opcao;

    // Massa de testes baseada no exemplo do PDF
    arvore.inserir({101, "John Smith", "Engenharia de Software"});
    arvore.inserir({102, "Alice Johnson", "Sistemas de Informação"});
    arvore.inserir({103, "Michael Brown", "Ciência da Computação"});
    arvore.inserir({104, "Emily Davis", "Engenharia de Software"});

    do {
        cout << "\n================ MENU ================" << endl;
        cout << "1. Inserir Aluno" << endl;
        cout << "2. Buscar Aluno por Nome" << endl;
        cout << "3. Exibir Alunos (Ordem Alfabética)" << endl;
        cout << "4. Exibir Informações da Árvore" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore(); // Limpar o buffer do teclado

        if (opcao == 1) {
            Aluno novoAluno;
            cout << "Digite a matrícula (número): ";
            cin >> novoAluno.matricula;
            cin.ignore();
            cout << "Digite o nome completo: ";
            getline(cin, novoAluno.nome);
            cout << "Digite o curso: ";
            getline(cin, novoAluno.curso);

            arvore.inserir(novoAluno);
            cout << "Aluno cadastrado com sucesso!" << endl;

        } else if (opcao == 2) {
            string nomeBusca;
            cout << "Digite o nome completo do aluno para buscar: ";
            getline(cin, nomeBusca);
            arvore.buscar(nomeBusca);

        } else if (opcao == 3) {
            cout << "\n--- Listagem de Alunos em Ordem Alfabética ---" << endl;
            arvore.exibirAlfabetico();

        } else if (opcao == 4) {
            cout << "\n--- Informações da Árvore ---" << endl;
            cout << "Quantidade total de alunos: " << arvore.getTotalAlunos() << endl;
            cout << "Altura da árvore: " << arvore.getAltura() << endl;
        }

    } while (opcao != 0);

    return 0;
};