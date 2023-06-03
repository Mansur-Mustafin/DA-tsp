

#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H


#include "Graph.h"

class Menu {
public:
    /**
     * @brief Displays the Main Menu
     */
    void main_menu();

    /**
     * @brief Displays the Menu that allows to change the file from which the nodes and edges are loaded
     */
    void change_file();

    /**
     * @brief Displays the Menu that allows to choose a network to be used
     */
    void choose_network();

    /**
     * @brief Displays the Menu that allows to add an edge to the Graph being used
     */
    void add_edge();

    /**
     * @brief Displays the Menu that allows to add a node to the Graph being used
     */
    void add_node();

    /**
     * @brief Displays the Menu that allows to use the Backtracking Algorithm, corresponding to the Task 2.1
     */
    void Task2_1();

    /**
     * @brief Displays the Menu that allows to use the Triangular Approximation Heuristic, corresponding to the Task 2.2
     */
    void Task2_2();

    /**
     * @brief
     */
    void Task2_3_1();

    /**
     * @brief
     */
    void Task2_3_2();
private:
    Graph g = Graph ("edges_25.csv");

};


#endif //PROJECT_MENU_H
