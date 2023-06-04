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

    void runAllAlgorithms();

    /**
     * @brief Displays the Menu that allows to use the Backtracking Algorithm
     */
    void Backtracking();

    /**
     * @brief Displays the Menu that allows to use the Triangular Approximation Algorithm
     */
    void Triangular_Approximation();

    /**
     * @brief Displays the Menu that allows to use the Triangular Approximation Algorithm using a a Distance Matrix
     */
    void Triangular_Approximation_using_matrix();

    /**
     * @brief Displays the Menu that allows to use the Ant Colony Optimization Algorithm
     */
    void ACO();

    /**
     * @brief Displays the Menu that allows to use the Simulated Annealing Algorithm
     */
    void Temp();

    /**
     * @brief Displays the Menu that allows to use Triangular Approximation, using Christofides Algorithm
     */
    void Triangular_approximation_using_Christofides();
private:
    Graph g = Graph ("edges_25.csv");

};


#endif //PROJECT_MENU_H