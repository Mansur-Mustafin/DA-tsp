#include <climits>
#include "Menu.h"

using namespace std;

//function and variables names are temporary

void Menu::change_file() {
    string nodes,edges;
    cout<<"Please enter the name of the edges file without extension:\n";
    getline(cin>>ws,nodes);
    cout<<endl;
    cout<<"Please enter the name of the nodes file without extension:\n";
    getline(cin,edges);
    cout<<endl;
    g = Graph(edges + ".csv", nodes + ".csv");
    main_menu();
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
            cout<<"Please enter the name of the nodes file without extension:\n";
            getline(cin>>ws,nodes);
            cout<<endl;
            cout<<"Please enter the name of the edges file without extension:\n";
            getline(cin,edges);
            cout<<endl;
            g = Graph(edges + ".csv", nodes + ".csv");
            main_menu();
            break;
        case 2:
            main_menu();
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            choose_network();
    }
}

void Menu::add_node(){
    //to be done
}

void Menu::add_edge(){
   //to be done
}

void Menu::Task2_1() {
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
        Task2_1();
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
            Task2_1();
    }
}

void Menu::Task2_2(){
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
        Task2_1();
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
            Task2_2();
    }
}

void Menu::Task2_3_1(){
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
        Task2_1();
    }

    switch (answer) {
        case 1:
            g.Task3(true);
            break;
        case 2:
            g.Task3(false);
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            Task2_3_1();
    }
}

void Menu::Task2_3_2(){
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
        Task2_1();
    }

    switch (answer) {
        case 1:
            g.Task4(true);
            break;
        case 2:
            g.Task4(false);
            break;
        default:
            cerr << "Invalid input" << endl << endl;
            Task2_3_2();
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
                   "| Triangular Approximation Heuristic                    [22] |\n"
                   "| Other Heuristics v1                                   [23] |\n"
                   "| Other Heuristics v2                                   [24] |\n"
                   "|============================================================|\n"
                   "|                      Other operations                      |\n"
                   "|============================================================|\n"
                   "| Add nodes to the network                            [11]  |\n"
                   "| Add edges to the network                            [12]  |\n"
                   "| Change files                                        [13]  |\n"
                   "| Exit                                                [0]   |\n"
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
                Task2_1();
                break;

            case 22:
                Task2_2();
                break;

            case 23:
                Task2_3_1();
                break;

            case 24:
                Task2_3_2();
                break;

            case 11:
                add_node();
                break;

            case 12:
                add_edge();
                break;

            case 13:
                change_file();
                break;

            default:
                cerr << "Invalid input" << endl;
        }
    }
}