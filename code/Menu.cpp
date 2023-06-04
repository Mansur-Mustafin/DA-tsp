#include <climits>
#include "Menu.h"

using namespace std;

//function and variables names are temporary

int check_files(const string& file_name){
    ifstream fin(file_name);
    if(!fin.is_open()) return -1;
    return 0;
}

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
    int check_files_flag = 0;
    switch (n) {
        case 1:
            cout<<"Please enter the name of the edges file without extension:\n";
            getline(cin>>ws,edges);
            cout<<endl;

            check_files_flag = check_files(edges + ".csv");
            if(check_files_flag < 0){
                change_file();
            }

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

            check_files_flag = check_files(edges + ".csv") + check_files(nodes + ".csv");
            if(check_files_flag < 0){
                change_file();
            }

            g = Graph(edges + ".csv", nodes + ".csv");
            main_menu();
            break;
        default:
           break;
    }
}

void Menu::choose_network(){
    string nodes,edges;
    cout<<"          Do you want to change the files?\n"
          "|==================================================| \n"
          "|       Yes [1]                   No  [2]          | \n"
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
            break;
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

void printFileContent() {
    ifstream file("output.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << '\n';
        }
        file.close();
    } else {
        cout << "Unable to open output.txt\n";
    }
}

void Menu::Backtracking() {
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]          | \n"
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
            break;
    }
}

void Menu::Triangular_Approximation(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]          | \n"
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
            break;
    }
}

void Menu::Triangular_Approximation_using_matrix(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]          | \n"
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
           break;
    }
}

void Menu::ACO(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]          | \n"
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
            break;
    }
}

void Menu::Annealing(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]          | \n"
            "|==================================================| " << endl;
    int answer;
    cin >> answer;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        Annealing();
    }

    switch (answer) {
        case 1:
            g.Task3_2(true);
            break;
        case 2:
            g.Task3_2(false);
            break;
        default:
            break;
    }
}

void Menu::Christofides(){
    cout << "          Do you want to print the path ?\n"
            "|==================================================| \n"
            "|       Yes [1]                   No  [2]          | \n"
            "|==================================================| " << endl;
    int answer;
    cin >> answer;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cerr << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        Christofides();
    }

    switch (answer) {
        case 1:
            g.Task2_3(true);
            break;
        case 2:
            g.Task2_3(false);
            break;
        default:
            break;
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
                   "| Annealing                                             [25] |\n"
                   "| Christofides Algorithm                                [26] |\n"
                   "|============================================================|\n"
                   "|                      Other operations                      |\n"
                   "|============================================================|\n"
                   "| Run all algorithms                                    [11] |\n"
                   "| Show all edges                                        [12] |\n"
                   "| Show all nodes                                        [13] |\n"
                   "| Show output                                           [14] |\n"
                   "| Change files                                          [15] |\n"
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
                Annealing();
                break;

            case 26:
                Christofides();
                break;

            case 11:
                runAllAlgorithms();
                break;

            case 12:
                g.print_edges();
                break;

            case 13:
                g.print_nodes();
                break;

            case 14:
                printFileContent();
                break;

            case 15:
                change_file();
                break;

            default:
                cerr << "Invalid input" << endl;
        }
    }
}