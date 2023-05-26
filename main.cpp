#include <iostream>
#include "Graph.h"

int main() {
    Graph g("edges.csv", "nodes.csv");
    //Graph g ("stadiums.csv");
    cout << "Graph was constructed" << endl;

    //cout << endl;
    //g.Task1(false);
    cout << endl;
    g.Task2(false);
    cout << endl;
    g.Task3(false);
    cout << endl;
    g.Task4(false);

    return 0;
}
