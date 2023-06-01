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

    //vector<string> files = {"edges_25.csv", "edges_50.csv", "edges_75.csv", "edges_100.csv", "edges_200.csv", "edges_300.csv", "edges_400.csv", "edges_500.csv", "edges_600.csv", "edges_700.csv", "edges_800.csv", "edges_900.csv"};
    vector<pair<string, string>> files = {{"edges_1.csv", "nodes_1.csv"},};
                                          //{"edges_2.csv", "nodes_2.csv"},};

    Graph g("edges_500.csv");
    for(const auto& file: files){
        //Graph g(file.first, file.second);
        cout << "Graph was constructed: " << file.first << endl;
        //g.Task1(false); // isso so para tou graphs.
        //g.Task2(false);
        g.test();
        //g.Task3(false);
        g.Task4(false);
        g.Task4_2();
    }

    return 0;
}
