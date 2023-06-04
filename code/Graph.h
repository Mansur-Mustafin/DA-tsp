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
     * @brief Writes a text into a file
     *
     * @param text - string to be written into a file
     */
    static void write_to_file(const string& text);

    /**
     * @brief Solves the Traveling Salesman Problem, using a Backtracking Algorithm
     *
     * This function is responsible for solving the Traveling Salesman Problem, utilising the Backtracking algorithm
     * represented by function tspBackTracking().
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal.
     */
    void Task1(bool print_path = true);   // backtracking

    /**
     * @brief Solves the Traveling Salesman Problem using a Triangular Aproximation Algorithm
     *
     * This function is responsible for solving the Traveling Salesman Problem, utilising Prim's
     * algorithm, represented by the function primMST() and the function preorderWalk().
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal.
     */
    void Task2(bool print_path = true);  // triangular approximation (slides)

    /**
     * @brief Solves the Traveling Salesman Problem with a Triangular Approximation using a Distance Matrix
     *
     * This function solves the Traveling Salesman Problem by applying the Triangular Approximation Algorithm using a
     * Distance Matrix. It uses Prim's algorithm represented in the function primMST() and the function preorderWalk().
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal.
     */
    void Task2_2(bool print_path = true); // triangular approximation (slides) MST by matrix

    /**
     * @brief Solves the Traveling Salesman Problem with a Triangular Approximation using Christofides Algorithm
     *
     * This function solves the Traveling Salesman Problem with a Triangular Approximation Algorithm using Christofides
     * Algorithm.
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal
     */
    void Task2_3(bool print_path = true); // Christofides Algorithm (used triangular inequality)

    /**
     * @brief Solves the Traveling Salesman Problem, using an Ant Colony Optimization Algorithm
     *
     * This function is responsible for solving the Traveling Salesman Problem, utilising the function ACO(), which
     * stands for "Ant Colony Optimization".
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal
     */
    void Task3_1(bool print_path = true); // ACO

    /**
     * @brief Solves the Traveling Salesman Problem, using a Simulated Annealing Algorithm
     *
     * This function is responsible for solving the Traveling Salesman Problem, utilising a Simulated Annealing Algorithm
     * represented by the function simulatedAnnealing().
     *
     * @param print_path - Boolean flag that determines if the calculated path should be printed in the terminal
     */
    void Task3_2(bool print_path = true); // Temperature

    // fields
    vector<vector<Edge>> adj;
    vector<Node> nodes;
    string file_edge_name = "tourism.csv";
    string file_nodes_name;

private:
    std::ofstream out;

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
    double getValue(vector <int>& v);

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
    vector <int> ACO(std::vector<std::vector<double>>& distance_matrix, int max_iter = 100, int num_ants = 10, double alpha = 1.0, double beta = 2.0, double rho = 0.1);

    /**
     * @brief Generate a sample by modifying a vector of integers
     *
     * This function generates a sample by modifying the order of elements in the given vector "v".
     * The sample modification follows the Simulated Annealing algorithm, where the swapping of elements is influenced
     * by the given temperature "t" and the current value "curValue".
     *
     * @param t - The temperature parameter used in the Simulated Annealing algorithm.
     * @param v - A vector of integers representing the order of nodes to be modified.
     * @param curValue A reference to the current value associated with the input vector "v".
     *
     * @note This function's time complexity is O(1) since it performs a fixed number of operations with no regard to
     * the size of the given input vector.
     */
    void getSample(double t, vector <int>& v, double& curValue);

    /**
     * @brief Solves the Traveling Salesman Problem using the Simulated Annealing algorithm
     *
     * This function applies the Simulated Annealing algorithm to solve the Traveling Salesman Problem.
     * It does this by initializing the temperature "t" to a high value and generating a random initial permutation of
     * size "n" using the generateRandomPermutation() function.
     * After this, the function calculates the initial cost of the permutation using the getValue() function. It then
     * iteratively performs the simulated annealing process until the temperature "t" reaches zero.
     * In each iteration, the function applies the getSample() function to generate a neighbouring solution and updates
     * the cost "value".
     * After this, the function returns the best solution (represented by "ans") that it found.
     *
     * @param n - number of nodes in the Permutation.
     * @return a vector representing the best path found by the algorithm.
     *
     * @note This functions time complexity is O(n * A) where n is the size of the permutation, and A is the number of
     * adjacent edges of each node of the permutation.
     */
    vector <int> simulatedAnnealing(int n);

    /**
     * @brief Calculates the Minimum Spanning Tree (MST) of a graph using Prim's Algorithm
     *
     * This function calculates the Minimum Spanning Tree (MST) of a given graph using Prim's Algorithm.
     * To begin, the function initializes necessary data structures such as "parent", "dist", "visitied" and a priority
     * queue named "pq".
     *
     * The vector "parent" stores the parent node and the corresponding edge weight for each node in the MST.
     * The vector "dist" stores the minimum distance from the MST to each node.
     * The vector "visited" keeps track of the nodes that have been visited.
     * The priority queue "pq" is used to select the next node with the minimum distance.
     *
     * The functions starts constructing the MST from node 0 by setting its parent as -1 and the respective distance to 0.
     * and adds this initial node to the priority queue.
     * While the priority queue is not empty, the function extracts the node with the minimum distance from the queue. If it
     * has been visited then it skips it, otherwise it marks the node as visited and iterates over its adjacent edges.
     * For each unvisited adjacent node, it updates the minimum distance and parent if a shorter edge is found.
     * After that, the updated nodes are added to the priority queue.
     *
     * After the MST is constructed, the function creates a new adjacency list "mst" for the edges belonging to the MST.
     * Then the function iterates over the "parent" vector and adds the edges to the adjacency list "mst". Note that "mst"
     * is a bidirectional graph, so both ends of an edge are added to their respective nodes.
     *
     * After this, the functions returns the adjacency list "mst" representing the MST of the Graph.
     *
     * @param tree - Adjacency list representing a weighted Graph.
     * @return Adjacency list representing the Minimum Spanning Tree of the graph.
     *
     * @note This function has a time complexity of O(E * log(V)) where E is the number of edges and V is the number of
     * vertices in the Graph
     */
     vector<vector<Edge>> primMST(vector<vector<Edge>> tree);;

    /**
     * @brief Performs a preorder walk on the Minimum Spanning Tree (MST) starting from a given node
     *
     * This function performs a preorder walk on the Minimum Spanning Tree (MST) starting from the specified node.
     * It visits each node in the MST in a preorder traversal manner, where the current node is visited before its
     * children nodes.
     *
     * This function performs a preorder walk on the Minimum Spanning Tree (MST( starting from the given node.
     * It does this by visiting each node in the MST in a preorder path, where the current node is visited before its
     * children are.
     * 
     * @param node - The starting node.
     * @param mst - The Minimum Spanning Tree (MST) represented as an adjacency list.
     * @param visited - A vector of boolean values representing the nodes that have been visited and those who have not.
     * @param path - The vector that stores the nodes visited during the preorder walk.
     *
     * @note This function's time complexity is O(E * log(E) + N * E) where E is the number of edges of the Minimum
     * Spanning Tree (MST) and N is the number of adjacent nodes of each node of the "children" vector.
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
    void tspBackTracking(vector<bool> &v, int currPos, size_t n, int count, double cost, double &ans, vector<int> &path, vector<int> &bestPath);

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
