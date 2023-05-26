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

class Graph {
public:
    Graph(const string &input_edge_name, const string &input_node_name = "");
    void print_edges();
    void print_nodes();
    void write_to_file(const std::string& text);
    void Task1(bool print_path = true);
    void Task2(bool print_path = true);
    void Task3(bool print_path = true);
    void Task4(bool print_path = true);
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
    int id(int a) const;
    double getDistance(int from, int to);
    double getValue(vector <int>& v, bool out = false);
    vector <int> ACO(std::vector<std::vector<float>>& distance_matrix, int max_iter = 100, int num_ants = 10, double alpha = 1.0, double beta = 2.0, double rho = 0.1);
    void getSample(double t, vector <int>& v, double& curValue);
    vector <int> simulatedAnnealing(int n);
    vector<vector<Edge>> primMST();
    void tspBackTracking(vector<bool> &v, int currPos, size_t n, int count, float cost, float &ans, vector<int> &path, vector<int> &bestPath);
    int input_vertex(const string &input_name);
    int input_edge(const string &input_name, bool have_nodes);
};

#endif //PROJECT_GRAPH_H
