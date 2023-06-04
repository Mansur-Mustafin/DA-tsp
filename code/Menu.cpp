#include <climits>
#include "Menu.h"

using namespace std;

//function and variables names are temporary

void Menu::change_file() {
    string nodes,edges;
    int n;
    cout<<"How may files do you want to use?\n";
    cin>>n;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        change_file();
    }

    switch (n) {
        case 1:
            cout<<"Please enter the name of the edges file without extension:\n";
            getline(cin>>ws,edges);
            cout<<endl;
            g = Graph(edges + ".csv");
            main_menu();
            break;
        case 2:
            cout<<"Please enter the name of the edges file without extension:\n";
            getline(cin>>ws,edges);
            cout<<endl;
            cout<<"Please enter the name of the nodes file without extension:\n";
            getline(cin,nodes);
            cout<<endl;
            g = Graph(edges + ".csv", nodes + ".csv");
            main_menu();
            break;
        default:
            cerr<<"So e possivel usar 1 ou 2 ficheiros"<<endl;
            change_file();
    }
}

void Menu::choose_network(){
    string nodes,edges;
    cout<<"          Do you want to change the network?\n"
          "|==================================================| \n"
          "|       Yes [1]                   No  [2]         | \n"
          "|==================================================| " << endl;
    int answer;
    cin>>answer;
    cout<<endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        choose_network();
    }

    switch (answer) {
        case 1:
            change_file();
            break;
        case 2:
            main_menu();
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            choose_network();
    }
}

void Menu::runAllAlgorithms(){
    g.Task1(false);
    g.Task2(false);
    g.Task2_2(false);
    g.Task3_1(false);
    g.Task3_2(false);
    g.Task2_3(false);
}

void Menu::Backtracking() {
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]         | \n"
            "|==================================================| " << endl;
    int answer;
    cin >> answer;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        Backtracking();
    }

    switch (answer) {
        case 1:
            g.Task1(true);
            break;

        case 2:
            g.Task1(false);
            break;

        default:
            cerr << "Invalid input" << endl << endl;
            Backtracking();
    }
}

void Menu::Triangular_Approximation(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]         | \n"
            "|==================================================| " << endl;
    int answer;
    cin >> answer;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        Triangular_Approximation();
    }

    switch (answer) {
        case 1:
            g.Task2(true);
            break;
        case 2:
            g.Task2(false);
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            Triangular_Approximation();
    }
}

void Menu::Triangular_Approximation_using_matrix(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]         | \n"
            "|==================================================| " << endl;
    int answer;
    cin >> answer;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        Triangular_Approximation_using_matrix();
    }

    switch (answer) {
        case 1:
            g.Task2_2(true);
            break;
        case 2:
            g.Task2_2(false);
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            Triangular_Approximation_using_matrix();
    }
}

void Menu::ACO(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]         | \n"
            "|==================================================| " << endl;
    int answer;
    cin >> answer;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        ACO();
    }

    switch (answer) {
        case 1:
            g.Task3_1(true);
            break;
        case 2:
            g.Task3_1(false);
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            ACO();
    }
}

void Menu::Temp(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]         | \n"
            "|==================================================| " << endl;
    int answer;
    cin >> answer;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        Temp();
    }

    switch (answer) {
        case 1:
            g.Task3_2(true);
            break;
        case 2:
            g.Task3_2(false);
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            Temp();
    }
}

void Menu::Triangular_approximation_using_Christofides(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]         | \n"
            "|==================================================| " << endl;
    int answer;
    cin >> answer;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        ACO();
    }

    switch (answer) {
        case 1:
            g.Task2_3(true);
            break;
        case 2:
            g.Task2_3(false);
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            ACO();
    }
}

void Menu::main_menu() {
    while (true) {
        cout << endl;
        cout
                << "|============================================================|\n"
                   "|                       TSP Algorithms                       |\n"
                   "|=========================================================== |\n"
                   "| Backtracking Algorithm                                [21] |\n"
                   "| Triangular Approximation                              [22] |\n"
                   "| Triangular Approximation using matrix                 [23] |\n"
                   "| ACO                                                   [24] |\n"
                   "| Temp                                                  [25] |\n"
                   "| Triangular approximation using Christofides Algorithm [26] |\n"
                   "|============================================================|\n"
                   "|                      Other operations                      |\n"
                   "|============================================================|\n"
                   "| Run all agorithms                                     [11] |\n"
                   "| Change files                                          [12] |\n"
                   "| Exit                                                  [0]  |\n"
                   "|============================================================|\n";

        cout << endl;
        cout << "Please choose an option:";
        int option;
        cin >> option;
        cout << endl;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cerr << "Invalid input" << endl;
            continue;
        }

        switch (option) {
            case 0:
                exit(0);

            case 21:
                Backtracking();
                break;

            case 22:
                Triangular_Approximation();
                break;

            case 23:
                Triangular_Approximation_using_matrix();
                break;

            case 24:
                ACO();
                break;

            case 25:
                Temp();
                break;

            case 26:
                Triangular_approximation_using_Christofides();
                break;

            case 11:
                runAllAlgorithms();
                break;

            case 12:
                change_file();
                break;

            default:
                cerr << "Invalid input" << endl;
        }
    }
}