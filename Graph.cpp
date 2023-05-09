//
// Created by mansur on 02-05-2023.
//

#include <fstream>
#include <climits>
#include "Graph.h"
#include <chrono>
#include <limits>
#include <queue>

using namespace std;

Graph::Graph(const string &input_edge_name, const string &input_node_name) {
    if(input_node_name.empty()) {
        if (input_edge(input_edge_name, false)) exit(-1);
    }else{
        if (input_edge(input_edge_name, true)) exit(-1);
        if( input_vertex(input_node_name)) exit(-1);
    }
    file_edge_name = input_edge_name;
    file_nodes_name = input_node_name;
}

int Graph::input_edge(const string &input_name, bool have_nodes) {
    Edge e;
    string s;
    string from;
    int m = -1;
    ifstream fin(input_name);
    if(fin.is_open()){
        getline(fin, s); // header line
        while(getline(fin, from, ',')){
            fin >> e;
            int f = stoi(from);
            int maxNode = max(e.to, f);
            while(adj.size() <= maxNode){
                adj.emplace_back();
            }
            adj[f].push_back(e);
            adj[e.to].push_back({f, e.dist});
            m = m > e.to ? m : e.to;
        }
    }else{
        cerr << "File: " << input_name << " unable to open." << endl;
        return -1;
    }
    if(!have_nodes){
        for(int i = 0; i <= m; i++){
            nodes.push_back({i,0,0});
        }
    }
    return 0;
}

int Graph::input_vertex(const string &input_name) {
    Node n{};
    string s;
    ifstream fin(input_name);
    if(fin.is_open()){
        getline(fin, s);
        while (fin >> n) {
            nodes.push_back(n);
        }
        fin.close();
    }else{
        cerr << "File: " << input_name << " unable to open." << endl;
        return -1;
    }
    return 0;
}

void Graph::print_edges() {
    cout << "Edges file name: " << file_edge_name << endl << endl;
    for(int i = 0 ; i < adj.size(); i++){
        cout << '[' << i << "] :" << endl;
        for(auto e: adj[i]){
            cout << "---" << e << endl;
        }
    }
}

void Graph::print_nodes() {
    if(file_nodes_name.empty()){
        cout << "There is no nodes file" << endl;
    }else{
        cout << "Nodes file name: " << file_nodes_name << endl << endl;
        for(auto n: nodes){
            cout << n << endl;
        }
    }

}

float findStart(const vector<Edge>& v){
    for(auto el : v){
        if(el.to == 0){
            return el.dist;
        }
    }
    return 0.0;
}

void Graph::tspBackTracking(vector<bool> &v, int currPos, int n, int count, float cost, float &ans, vector<int> &path, vector<int> &bestPath) {
    if (count == n && findStart(adj[currPos])) {
        if (cost + findStart(adj[currPos]) < ans) {
            ans = cost + adj[currPos][0].dist;
            bestPath = path;
        }
        return;
    }

    for (Edge el : adj[currPos]) {
        if (!v[el.to]) {
            v[el.to] = true;
            path.push_back(el.to);
            tspBackTracking(v, el.to, n, count + 1, cost + el.dist, ans, path, bestPath);
            path.pop_back();
            v[el.to] = false;
        }
    }
}

void Graph::Task1() {
    int n = adj.size();
    vector<bool> v(n);
    for (int i = 0; i < n; i++)
        v[i] = false;

    v[0] = true;
    float ans = 1e9;
    vector<int> path = {0};
    vector<int> bestPath;

    auto start = chrono::high_resolution_clock::now();
    tspBackTracking(v, 0, n, 1, 0, ans, path, bestPath);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> backtracking_duration = end - start;

    cout << "Minimum cost: " << ans << endl;
    cout << "Path: ";
    for (int i : bestPath) {
        cout << i << " -> ";
    }
    cout << "0" << endl;
    cout << "Execution time: " << backtracking_duration.count() << " seconds" << endl;
}





vector<vector<Edge>> Graph::primMST() {

    int n = adj.size();
    vector<pair<int, float>>  parent (n, {-2, 0.0});
    vector<float> dist(n, numeric_limits<float>::max());
    vector<bool> visited(n, false);
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;

    parent[0] = {-1, 0.0};
    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge &e : adj[u]) {
            if (!visited[e.to] && e.dist < dist[e.to]) {
                dist[e.to] = e.dist;
                parent[e.to] = {u, e.dist};
                pq.push({e.dist, e.to});
            }
        }
    }

    vector<vector<Edge>> mst (parent.size());

    for(int i = 0; i < parent.size(); i ++){
        if(parent[i].first != -1){
            mst[parent[i].first].push_back({i, (parent[i].second)});
        }
    }

    return mst;
}

