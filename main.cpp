#include <iostream>
#include "Graph.h"

int main() {
    Graph g("stadiums.csv");

    cout << endl;
    g.Task1(false);
    cout << endl;
    g.Task2(false);
    cout << endl;
    g.Task3(false);
    cout << endl;
    g.Task4(false);

    return 0;
}
