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
     *
     * @param text
     */
    void write_to_file(const std::string& text);
    void Task1(bool print_path = true);
    void Task2(bool print_path = true);
    void Task3(bool print_path = true);
    void Task4(bool print_path = true);
    void Task2_2(bool print_path = true);

    // fields
    vector<vector<Edge>> adj;
    vector<Node> nodes;
    string file_edge_name = "tourism.csv";
    string file_nodes_name = "";

private:
    //ACO fields
    float UP_EPS = 1e9;

    int V = 0;
    int id(int a) const;
    double getDistance(int from, int to);
    double getValue(vector <int>& v, bool out = false);
    vector <int> ACO(std::vector<std::vector<float>>& distance_matrix, int max_iter = 100, int num_ants = 10, double alpha = 1.0, double beta = 2.0, double rho = 0.1);
    void getSample(double t, vector <int>& v, double& curValue);
    vector <int> simulatedAnnealing(int n);
    vector<vector<Edge>> primMST(vector<vector<Edge>> tree);
    void preorderWalk(int node, const vector<vector<Edge>> &mst, vector<bool> &visited, vector<int> &path);
    void tspBackTracking(vector<bool> &v, int currPos, size_t n, int count, float cost, float &ans, vector<int> &path, vector<int> &bestPath);

    /**
     * @brief Adds a vertex (or vertices) to the Graph
     *
     * @param input_name - Name of the file containing the information about the vertex (or vertices)
     * @return 0 if successful, -1 otherwise
     */
    int input_vertex(const string &input_name);

    /**
     * @brief Adds an edge (or edges) to the Graph and the respective nodes that correspond to said edge(s)
     *
     * @param input_name - Name of the file containing the information about the vertex (or vertices)
     * @param have_nodes - Boolean parameter that determines if the edges have associated nodes to be inserted as well
     * @return  0 if successful, -1 otherwise
     */
    int input_edge(const string &input_name, bool have_nodes);
};

#endif //PROJECT_GRAPH_H
