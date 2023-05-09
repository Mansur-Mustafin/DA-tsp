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

using namespace std;

class Graph {
public:
    Graph(const string &input_edge_name, const string &input_node_name = "");
    void print_edges();
    void print_nodes();
    void Task1();
    vector<vector<Edge>> primMST();

    // fields
    vector<vector<Edge>> adj;
    vector<Node> nodes;
    string file_edge_name = "tourism.csv";
    string file_nodes_name = "";

private:

    void tspBackTracking(vector<bool> &v, int currPos, int n, int count, float cost, float &ans, vector<int> &path, vector<int> &bestPath);
    int input_vertex(const string &input_name);
    int input_edge(const string &input_name, bool have_nodes);
};

#endif //PROJECT_GRAPH_H
