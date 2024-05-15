#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Agendar - Desmarcar e ver agenda do médico


//class Paciente armazenar informaçoes do paciente
class Paciente {
private:
	string nome;
	string telefone;
public:
	string getNome() {
		return nome;
	}
	void setNome(string valor) {
		nome = valor;
	}
	string getTelefone() {
		return telefone;
	}
	void setTelefone(string valor) {
		telefone = valor;
	}
};

//marcar/desmarcar as consultas salvando uma data e hora da consulta
class Consulta: public Paciente {
private:
    string data;
    string hora;
public:
    string getData(){
        return data;
    }
    void setData(string valor){
        data = valor;
    }
    string getHora(){
        return hora;
    }
    void setHora(string valor){
        hora = valor;
    }
    
};

//manter todos os pacientes marcados em um vector para imprimir em um arquivo
class RepositorioPacientes {
private:
    vector <Consulta*> marcados;

    //imprimir o paciente no arquivo
    void SalvarUmPaciente(Consulta* a , ofstream& out){
        out << a->getNome() << "\n";
        out << a->getTelefone() << "\n";
        out << a->getData() << " " << a->getHora() << "\n";
    }

    //ler um paciente no arquivo
     void LerUmPaciente(Consulta* a , ifstream& in){
        string aux;
        getline(in,aux);
        a->setNome(aux);

        getline(in,aux);
        a->setTelefone(aux);

        getline(in,aux , ' ');
        a->setData(aux);

        getline(in,aux);
        a->setHora(aux);
    }

    void LerAgenda(ifstream& in){
        string aux;
        getline(in,aux);
        cout << "Nome: " << aux << "\n";
        getline(in,aux);
        cout << "Telefone: " << aux << "\n";
        getline(in,aux, ' ');
        cout << "Data e hora: " << aux << " ";
        getline(in,aux);
        cout << aux << "\n";
        cout << "================================\n";

    }   

public: 
    
    //adicionar um paciente no vector
    void adicionar(Consulta* a){
        marcados.push_back(a);
    };


    void remover(int desmarcar){
        marcados.erase(marcados.begin()+desmarcar);
        marcados.pop_back();
    } 

    //salvar a consulta marcada em um arquivo
    void salvar(){
        ofstream arquivo("agenda.txt", std::ios::app);
        for (Consulta* a: marcados){
            SalvarUmPaciente(a,arquivo);
        }
        arquivo.close();
    }
    //reescreve o arquivo sem o paciente desmarcado
    void salvarDesmarcados(){
        ofstream arquivo("agenda.txt", std::ios::out);
        for (Consulta* a: marcados){
            SalvarUmPaciente(a,arquivo);
        }
        arquivo.close();
    }

    //carregar as consultas do arquivo em um vector
    void carregar(){
        ifstream arquivo("agenda.txt");
        while (!arquivo.eof()) {
            Consulta* a = new Consulta();
            LerUmPaciente(a,arquivo);
            marcados.push_back(a);
        }
        arquivo.close();        
    }

    void limparvector(){
        while(!marcados.empty()){
            marcados.pop_back();
        }
    }
    //buscar o nome do paciente nas consultas marcadas e retorna a posição no vector
    int DesmarcarBusca(string nome){
        int i = 0;
        for(Consulta* a: marcados){
            if(a->getNome() == nome){
                cout << "Encontrado \n";
                return i;
            }
            i++;

        }
        cout << "Nao Encontrado \n";
        return -1;
    }

    void Marcar(){
        Consulta* nova = new Consulta();

        cout <<"Marcar um paciente \n";
        
        string aux;
        
        cout << "\n";
        cout <<"Nome do paciente \n";
        getline(cin.ignore(), aux);
        nova->setNome(aux);

        cout <<"Telefone \n";
        getline(cin, aux);
        nova->setTelefone(aux);

        cout <<"Data da consulta \n";
        getline(cin, aux);
        nova->setData(aux);

        cout <<"Hora da consulta \n";
        getline(cin, aux);
        nova->setHora(aux);

        limparvector();
        adicionar(nova);
        salvar();
        limparvector();
        cout <<"Marcado com sucesso \n";
    }
    
    void Desmarcar(){
        cout << "Desmarcar: ";
        string aux;
        getline(cin.ignore(),aux);
    
        int rem = DesmarcarBusca(aux);
        if(rem == -1){
            cout << "Erro ao remover\n";
        } else {
            remover(rem);
            salvarDesmarcados();
            cout << "Desmarcado com sucesso\n";
        }
    }

    void abrirAgenda(){
        ifstream arquivo("agenda.txt");
        while (!arquivo.eof()) {
            //Marcar* a = new Marcar();
            LerAgenda(arquivo);
        }
        arquivo.close();        
    }


};

int main(){
    RepositorioPacientes* repositorio = new RepositorioPacientes();
 
    int menu;

    while(1)
    {

    cout << "Consultorio \n";
    cout << "1 - Marcar Consulta \n";
    cout << "2 - Desmarcar Consulta \n";
    cout << "3 - Mostrar Agenda \n";
    cout << "0 - Sair \n";
    cin >> menu;

    if (menu == 1){
        repositorio->Marcar();
    }
    else if(menu == 2){
        repositorio->carregar();
        repositorio->Desmarcar();
        repositorio->limparvector();
    }
    else if(menu == 3){
        repositorio->abrirAgenda();
    }
    else if(menu == 0){
        break;
    }
    }

    return 0;
}