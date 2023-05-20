#include <iostream>
#include "Graph.h"

int main() {
    Graph g("stadiums.csv");
    cout << "----------------------------------" << endl;
    g.Task1();
    cout << "----------------------------------" << endl;
    g.Task2();
    cout << "----------------------------------" << endl;
    g.Task3();
    cout << "----------------------------------" << endl;
    g.Task4();

    return 0;
}
