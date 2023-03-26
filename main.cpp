#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>


using namespace std;


void ciclo(){


}

void gestao(){

    int options;

    cout << "***** Bem vindo gestor *****\n";
    cout << "(1).Reparação Manual\n";
    cout << "(2).Atualizar tempo de reparação\n";
    cout << "(3).Adicionar Prioridade\n";
    cout << "(4).Remover Mecânico\n";
    cout << "(5).Gravar Oficina\n";
    cout << "(6).Carregar Oficina\n";
    cout << "(7).Imprimir Oficina\n";
    cout << "Seleccione a sua opção:\n";
    cin >> options;

    switch (options)
    {
    case 1:
        
        break;

    case 2:

        break;

    case 3:

        break;

    case 4:

        break;

    case 5:

        break;

    case 6:

        break;

    case 7:

        break;
    
    default:

        cout << "Não selecionou uma opção válida\n";
    
        break;
    }

}

void lerFicheiros(){


}

int main(){

    char option;

    srand (time(NULL));


    cout << "Dia (s)eguinte ********* (g)estão\n";
    cout << "Selecione a sua opção:\n";
    cin >> option;

    switch (tolower(option))
    {
    case 's':

        ciclo();
        
        break;

    case 'g':

        gestao();

        break;
    
    default:

        cout << "Não selecionou uma opção valida\n";

        break;
    }
 

    return 0;
}

/* #include <iostream>
#include <fstream>
#include <list>

int main() {
    std::ifstream file("example.txt"); // Open the file
    std::list<std::string> lines; // Create a list of strings

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) { // Read the file line by line
            lines.push_back(line); // Add each line to the list
        }
        file.close(); // Close the file
    } else {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    // Print the contents of the list
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }

    return 0;
}
*/