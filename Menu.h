

#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H


#include "Graph.h"

class Menu {
public:
    void main_menu();
    void change_file();
    void choose_network();
    void add_edge();
    void add_node();
    void Task2_1();
    void Task2_2();
    void Task2_3_1();
    void Task2_3_2();
private:
    Graph g = Graph ("edges_25.csv");

};


#endif //PROJECT_MENU_H
