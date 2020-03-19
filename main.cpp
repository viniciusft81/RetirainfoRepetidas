#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

// Tipo Estudante: representa um aluno com sua matricula e nome completo
struct Estudante {
    string AlunoMatricula;
    string NomeAluno;

    Estudante() {
    }

    //Recebendo como parametro a matricula com oito caracteres e nome do aluno
    Estudante(const string & mat, const string & umNome) {
        NomeAluno = umNome;
        AlunoMatricula = mat;
    }
};

// sobrecarga do operador< para o tipo Estudante
bool operator<(const Estudante & este, const Estudante & outro) {
    if (este.NomeAluno == outro.NomeAluno) {
        return este.AlunoMatricula < outro.AlunoMatricula;
    }
    return este.NomeAluno < outro.NomeAluno;
}

//Função removendo alunos com nomes e matículas repetidas
void remove_repetidos(string & nome, string & mat, list<Estudante> & lista){
    for(auto it = lista.begin(); it != lista.end(); it++){
        if(nome == it->NomeAluno){ // Verificando o nome se for igual e matricula diferente não apaga
            if(mat != it->AlunoMatricula) //Se for nome igual e matricula igual irá apagar info repetida
                continue;
            it = lista.erase(it); //Apagando da lista o nome repetido
        }
    }
}


int main(int argc, char *argv[]) {

    list <Estudante> li;
    string linha, arquivo;

    //Verifica se o usuário passou o caminho e o arquivo como argumento
    if(argc < 2){
        cout << argv[0] << " -> Deve ser passado o arquivo da seguinte maneira ../Alunos/arquivo.txt" << endl;
        return 0;
    }

    // Laço com base no número de arquivos, faz a leitura de todos os arquivos informado como argumento
    for(int i = 1; i < argc; i++) {
        arquivo = argv[i];

        //Abertura do arquivo para leitura
        ifstream arq(arquivo);

        //Verifica se o arquivo foi de fato aberto
        if (!arq.is_open()) {
            cout << "Erro ao abrir o arquivo";
            return 0;
        }

        //Loop lendo linha por linha do arquivo
        while (getline(arq, linha)) {
            //Pegando o comprimento da linha com o nome do aluno e a matricula
            int compLinha = linha.size();
            string ma, al;

            //Armazenando em variáveis string a matrícula e o nome do aluno
            ma = linha.substr(0, 8);
            al = linha.substr(9, compLinha);

            //Chamada a função para remover os nomes repetidos e matriculas repetidas
            //Parâmetros: nome do aluno, matrícula e a lista como referência
            remove_repetidos(al, ma, li);

            //Adcionando itens a lista que não são repetidos
            li.push_back(Estudante(ma, al));
        }

        //Fechando o arquivo para ir ao próximo se houver
        arq.close();

        //Ordena a lista por ordem alfabética, por conta da função bool com sobrecarga do operador
        li.sort();
    }

    //Mostrando em tela a lista com os nomes e matricula dos alunos de n arquivos
    for(auto & printaLi: li){
        cout << printaLi.AlunoMatricula << " "<< printaLi.NomeAluno << endl;
    }



    return 0;
}
