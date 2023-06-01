//
// Created by mansur on 02-05-2023.
//

#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include "Node.h"
#include "Edge.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

/**
 * @brief Class representing a Graph
 *
 * This class represents a Graph with a vector of its nodes and a vector of vectors of its edges, as well as the name of
 * the files from which the nodes and edges are loaded.
 */
class Graph {
public:
    /**
     * @brief Constructor of the class Graph
     *
     * @param input_edge_name - Name of the file from which the edges are loaded
     * @param input_node_name - Name of the file from which the nodes are loaded
     */
    Graph(const string &input_edge_name, const string &input_node_name = "");

    /**
     * @brief Prints the edges of the Graph
     */
    void print_edges();

    /**
     * @brief Prints the nodes of the Graph
     */
    void print_nodes();

    /**
     * @brief Writes text into a file
     *
     * @param text
     */
<<<<<<< HEAD
    void write_to_file(const std::string& text);

    /**
     * @brief Asks the user for the data necessary to accomplish Task 1, using a Backtracking Algorithm
     *
     * This function is responsible for asking for the necessary data to the user to accomplish Task 1, utilising the
     * function tspBackTracking().
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal.
     */
=======
    //void write_to_file(const std::string& text);
>>>>>>> e24d46b9b82b028c90cc9aa1e1fd4c0dca646d47
    void Task1(bool print_path = true);

    /**
     * @brief
     *
     *
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal.
     */
    void Task2(bool print_path = true);

    /**
     * @brief Asks the user for the data necessary to accomplish Task 3, using an Ant Colony Optimization Algorithm
     *
     * This function is responsible for asking for the necessary data to the user to accomplish Task 3, utilising the
     * function ACO(), which stands for "Ant Colony Optimization".
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal.
     */
    void Task3(bool print_path = true);

    /**
     * @brief
     *
     * @param print_path
     */
    void Task4(bool print_path = true);

    /**
     * @brief
     */
    void test();

    // fields
    vector<vector<Edge>> adj;
    vector<Node> nodes;
    string file_edge_name = "tourism.csv";
    string file_nodes_name = "";

private:
    //ACO fields
    float UP_EPS = 1e9;


    int V = 0;

    /**
     * @brief Verifies if the integer given is a valid id of a node in the Graph
     *
     * @param a - Integer representing the id of the pretended node
     * @return 0 if the given integer is invalid (bigger than the number of nodes in the Graph), the given integer otherwise
     *
     * @note This function's time complexity is O(1).
     */
    int id(int a) const;

    /**
     * @brief This function returns the distance between two nodes
     *
     * This function calculates the distance between two given nodes. This distance is calculated by calling the Node::getDistance
     * function defined in the file Node.h if the two given nodes are not adjacent. If they are adjacent, then the function
     * returns the distance between them given by the edge that connects them.
     *
     * @param from - Integer representing the starting Node
     * @param to - Integer representing the target Node
     * @return the distance between the two given nodes
     *
     * @note This function has a time complexity of O(N) where N is the number of adjacent nodes of the "from" node.
     */
    double getDistance(int from, int to);

    /**
     * @brief Calculates the value of a given path in the graph.
     *
     * This function calculates the value of a given path represented by a vector of integers in the graph. The value is
     * calculated by adding up the distances between consecutive nodes in the path using the Graph::getDistance function.
     * Optionally, it can also print the intermediate sums if the `out` parameter is set to `true`.
     *
     * @param v - vector of integers representing a path on the Graph
     * @param out - boolean flag that determines if the result should be printed. Default is "false"
     * @return the value of the given path.
     *
     * @note This function's time complexity is O(N * A) where N is the number of nodes in the given path and A is the
     * number of adjacent nodes of each node present in the given path.
     */
    double getValue(vector <int>& v, bool out = false);

    /**
     * @brief Uses the Ant Colony Optimization (ACO) on a distance matrix to find the best path
     *
     * This functions uses the Ant Colony Optimization algorithm to find the best path in a given distance matrix. It does
     * this by initializing a pheromone matrix, creating ant paths, updating the pheromone levels and then iterates for
     * a given amount of maximum iterations. Once finished, returns the best path found.
     *
     * @param distance_matrix - The distance matrix representing the distance between nodes
     * @param max_iter - Maximum number of iterations
     * @param num_ants - Number of ants (or paths) to be created in each iteration
     * @param alpha - Pheromone factor that determines the influence of pheromone levels
     * @param beta - Distance factor that determines the influence of distance values
     * @param rho - Evaporation rate of a pheromone
     * @return a vector of integers representing the best path found
     *
     * @note This function's time complexity can be given as O(max_iter * num_ants * n^2) where max_iter is the maximum
     * number of iterations, num_ants is the number of ants given and n is the size of the distance matrix.
     */
    vector <int> ACO(std::vector<std::vector<float>>& distance_matrix, int max_iter = 100, int num_ants = 10, double alpha = 1.0, double beta = 2.0, double rho = 0.1);

    /**
     * @brief
     *
     * @param t
     * @param v
     * @param curValue
     *
     * @note
     */
    void getSample(double t, vector <int>& v, double& curValue);

    /**
     * @brief
     *
     * @param n
     * @return
     *
     * @note
     */
    vector <int> simulatedAnnealing(int n);

    /**
     * @brief
     *
     * @return
     *
     * @note
     */
    vector<vector<Edge>> primMST(vector<vector<Edge>> adj);

    /**
     * 
     * @param node
     * @param mst
     * @param visited
     * @param path
     */
    void preorderWalk(int node, const vector<vector<Edge>> &mst, vector<bool> &visited, vector<int> &path);

    /**
     * @brief Solves the Traveling Salesman Problem using a Backtracking Algorithm
     *
     * This functions uses a Backtracking algorithm to solve the Traveling Salesman Problem (TSP). It does this by initializing
     * a vector "v" that is used to keep track the visited nodes where "v[i]" is true if the node represented by "i" has been visited.
     * The functions uses recursion to explore all the possible paths from the "currPos" and updates the "bestPath" and its
     * respective cost "ans" if a shorter path is found. The algorithms uses pruning techniques to optimize the search, avoiding
     * unnecessary exploration of paths with a higher cost than the current best path.
     *
     * @param v - Vector of boolean that indicates which nodes have been visited and which havent
     * @param currPos - The current position (in this case the current node) being visited.
     * @param n - Total number of nodes in the Graph
     * @param count - Number of nodes that have been visited
     * @param cost - Total cost of the current path
     * @param ans - Reference to the best cost found so far
     * @param path - Vector of integers representing the path being explored
     * @param bestPath - A reference to the vector of integers representing the best path found so far
     *
     * @note This function's time complexity is O(n!) where n is the number of nodes of the Graph
     */
    void tspBackTracking(vector<bool> &v, int currPos, size_t n, int count, float cost, float &ans, vector<int> &path, vector<int> &bestPath);

    /**
     * @brief Adds a vertex (or vertices) to the Graph
     *
     * This function creates an object of the class Node and inputs it into the nodes vector of the Graph.
     *
     * @param input_name - Name of the file containing the information about the vertex (or vertices)
     * @return 0 if successful, -1 otherwise
     */
    int input_vertex(const string &input_name);

    /**
     * @brief Adds an edge (or edges) to the Graph and the respective nodes that correspond to said edge(s) if desired
     *
     * This function creates an object of the class Edge and inputs it into the vectors of vectors of edges, corresponding
     * to the nodes it connects.
     *
     * @param input_name - Name of the file containing the information about the edge (or edges)
     * @param have_nodes - Boolean flag that determines if the edges have associated nodes to be inserted as well
     * @return  0 if successful, -1 otherwise
     */
    int input_edge(const string &input_name, bool have_nodes);
};

#endif //PROJECT_GRAPH_H
