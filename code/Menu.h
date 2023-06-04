

#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H


#include "Graph.h"

class Menu {
public:
    void main_menu();
    void change_file();
    void choose_network();
    void Backtracking();
    void Triangular_Approximation();
    void Triangular_Approximation_using_matrix();
    void ACO();
    void Temp();
    void Triangular_approximation_using_Christofides();
private:
    Graph g = Graph ("edges_25.csv");

};


#endif //PROJECT_MENU_H
