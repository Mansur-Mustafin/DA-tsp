#include <iostream>
#include "Graph.h"
#include "Menu.h"

int main() {

    try {
        //Menu menu;
        //menu.main_menu();
    }
    catch (exception& e) {
        cout << e.what() << '\n';
    }

    //Graph g("edges.csv", "nodes.csv");
    Graph g("edges_25.csv");
    cout << endl;
    cout << "Graph was constructed" << endl;
    //g.Task1(false);
    //cout << endl;
    g.Task2(false);
    //cout << endl;
    g.test();
    //cout << endl;
    g.Task3(false);
    //cout << endl;
    g.Task4(false);

    //return 0;
}
