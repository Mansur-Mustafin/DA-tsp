//
// Created by mansur on 02-05-2023.
//

#include <fstream>
#include "Graph.h"
#include <chrono>
#include <limits>
#include <queue>
#include <iomanip>

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
    Edge e{};
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

float Graph::getDistance(int from, int to) {
    for(auto el : adj[from]){
        if(el.to == to){
            return el.dist;
        }
    }
    cout << "not found: " << from << " " << to << endl;
    return nodes[from].getDistance(nodes[to]);
}

// TODO Task1 ----------------------------------------------------------------------------------------------------------

void Graph::tspBackTracking(vector<bool> &v, int currPos, size_t n, int count, float cost, float &ans, vector<int> &path, vector<int> &bestPath) {

    if (cost >= ans) return;

    if (count == n && findStart(adj[currPos])) {
        if (cost + findStart(adj[currPos]) < ans) {
            ans = cost + findStart(adj[currPos]);
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
    size_t n = adj.size();
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

    cout << "Backtracking Minimum cost: " << fixed << setprecision(2) << ans << endl;
    cout << "Path: ";
    for (int i : bestPath) {
        cout << i << " -> ";
    }
    cout << "0" << endl;
    cout << "Execution time: " << backtracking_duration.count() << " seconds" << endl;
}

// TODO Task2 ----------------------------------------------------------------------------------------------------------

vector<vector<Edge>> Graph::primMST() {
    int n = adj.size();
    vector<pair<int, float>>  parent (n, {-2, 0.0});
    vector<float> dist(n, numeric_limits<float>::max());
    vector<bool> visited(n, false);
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;

    parent[0] = {-1, 0.0};
    dist[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge &e : adj[u]) {
            if (!visited[e.to] && e.dist < dist[e.to]) {
                dist[e.to] = e.dist;
                parent[e.to] = {u, e.dist};
                pq.emplace(e.dist, e.to);
            }
        }
    }

    vector<vector<Edge>> mst (parent.size());

    for(int i = 0; i < parent.size(); i ++){
        if(parent[i].first != -1){
            mst[parent[i].first].push_back({i, (parent[i].second)});
            mst[i].push_back({parent[i].first, parent[i].second}); // TODO check if is needed. (make mst bidirectional)
        }
    }

    return mst;
}

void preorderWalk(int node, const vector<vector<Edge>> &adj, vector<bool> &visited, vector<int> &path) {
    visited[node] = true;
    path.push_back(node);

    for (const Edge &edge : adj[node]) {
        if (!visited[edge.to]) {
            preorderWalk(edge.to, adj, visited, path);
        }
    }
}

void Graph::Task2(){
    auto start = chrono::high_resolution_clock::now();
    vector<vector<Edge>> p = primMST();

    int startNode = 0;
    vector<bool> visited(p.size(), false);
    vector<int> path;

    preorderWalk(startNode, p, visited, path);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> backtracking_duration = end - start;

    double ans = 0.0;
    for(int s = 0; s < path.size() - 1; s++){
        ans += getDistance(path[s], path[s + 1]);
    }
    ans += getDistance(path[path.size() - 1], 0);

    cout << "Triangular approximation Minimum cost: " << fixed << setprecision(2) << ans << endl;
    cout << "Path: ";
    for (int node : path) {
        cout << node << " -> ";
    }
    cout << "0" << endl;
    cout << "Execution time: " << backtracking_duration.count() << " seconds" << endl;
}

// TODO Task3 ----------------------------------------------------------------------------------------------------------

double Graph::ACO(std::vector<std::vector<float>>& distance_matrix, int max_iter,
                  int num_ants, double alpha, double beta, double rho) {
    int n = distance_matrix.size();
    std::vector<int> best_path(n);
    double best_distance = std::numeric_limits<double>::max();

    std::vector<std::vector<float>> pheromone(n, std::vector<float>(n, 1.0));

    for (int iter = 0; iter < max_iter; iter++) {
        std::vector<std::vector<int>> ant_paths(num_ants, std::vector<int>(n));

        for (int ant = 0; ant < num_ants; ant++) {
            std::vector<int> visited(n, 0);
            ant_paths[ant][0] = 0;  // Начальная точка всегда 0
            visited[0] = 1;

            for (int i = 1; i < n; i++) {
                int current = ant_paths[ant][i - 1];
                double total_pheromone = 0.0;
                for (int j = 0; j < n; j++) {
                    if (visited[j] == 0) {
                        total_pheromone += pow(pheromone[current][j], alpha) * pow(1.0 / distance_matrix[current][j], beta);
                    }
                }

                double rnd = (double)std::rand() / RAND_MAX;
                double selection_prob = 0.0;
                int next = -1;
                for (int j = 0; j < n; j++) {
                    if (visited[j] == 0) {
                        selection_prob += pow(pheromone[current][j], alpha) * pow(1.0 / distance_matrix[current][j], beta) / total_pheromone;
                        if (rnd <= selection_prob) {
                            next = j;
                            break;
                        }
                    }
                }

                if(next != -1){
                    ant_paths[ant][i] = next;
                    visited[next] = 1;
                }

            }
        }

        for (int ant = 0; ant < num_ants; ant++) {
            double distance = 0.0;
            for (int i = 0; i < n - 1; i++) {
                distance += distance_matrix[ant_paths[ant][i]][ant_paths[ant][i + 1]];
            }
            distance += distance_matrix[ant_paths[ant][n - 1]][0];  // Конечная точка - 0

            if (distance < best_distance) {
                best_distance = distance;
                best_path = ant_paths[ant];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                pheromone[i][j] *= (1.0 - rho);
            }
        }
        for (int ant = 0; ant < num_ants; ant++) {
            for (int i = 0; i < n - 1; i++) {
                int from = ant_paths[ant][i];
                int to = ant_paths[ant][i + 1];
                pheromone[from][to] += 1.0 / best_distance;
            }
            pheromone[ant_paths[ant][n - 1]][0] += 1.0 / best_distance;  // Ребро от последней точки к 0
        }
    }
    std::cout << "ACO Path: ";
    for (int i = 0; i < best_path.size(); ++i) {
        std::cout << best_path[i] << " -> ";
    }
    cout << "0\n";
    return best_distance;
}


void Graph::Task3(){
    auto start = chrono::high_resolution_clock::now();
    int n = adj.size();
    std::vector<std::vector<float>> distance_matrix(n, std::vector<float>(n, UP_EPS));
    for(int i=0; i < adj.size(); ++i){
        for(int j=0; j < adj[i].size(); ++j){
            if( adj[i][j].to != -1 )
                distance_matrix[i][adj[i][j].to] = adj[i][j].dist;
        }
    }
    double shortest_distance = ACO(distance_matrix, max_iter, num_ants, alpha, beta, rho);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> aco_duration = end - start;
    std::cout << "ACO. Minimum cost: " << fixed << setprecision(2) << shortest_distance << std::endl;
    std::cout << "Execution time: " << aco_duration.count() << " seconds" << std::endl;
}

// TODO TASK4 ----------------------------------------------------------------------------------------------------------

vector<int> generateRandomPermutation(int n) {
    vector<int> permutation(n);
    for (int i = 0; i < n; ++i)
        permutation[i] = i;
    random_device rd;
    mt19937 gen(rd());
    shuffle(permutation.begin(), permutation.end(), gen);

    return permutation;
}

int getRand(int l, int r) {

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distribution(l, r);
    int randomNum = distribution(gen);

    return randomNum;

}

double Graph::getValue(vector <int>& v) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++)
        sum += getDistance(v[i], v[(i + 1) % v.size()]);
    return sum;
}

vector <int> regenerate(vector <int> v, int l, int r) {

    vector <int> permut = generateRandomPermutation(r - l + 1); // example generateRandomPermutation(5) ~ {4, 1, 3, 2, 0}


    vector <int> temp (v.size());
    copy(v.begin(), v.end(), temp.begin());

    for (int i = l; i <= r; i++)
        temp[i] = v[permut[i - l] + l];

    return temp;
}

vector <int> Graph::getSample(int t, vector <int>& v) {  // 1 градус ~ (v.size() + 99) / 100

    int length = min((t * v.size() + 99) / 100, v.size() - 1), l = getRand(1, max((int) v.size() - length, 1)), r = l + length - 1, cnt = 0;
    double originValue = getValue(v), curValue = originValue + 1;

    vector <int> temp;
    while (curValue > originValue && cnt++ < 5) {
        temp = regenerate(v, l, r);

        double tempValue = getValue(temp);
        if (tempValue < curValue) {
            v = temp;
            curValue = tempValue;
        }
    }

    return v;
}

vector <int> Graph::simulatedAnnealing(int n) {

    int t = 100;

    vector <int> ans = generateRandomPermutation(n);

    for(size_t i = 0; i < ans.size(); i++){
        if(!ans[i]){
            swap(ans[i], ans[0]);
        }
    }

    while (t--)
        for(int i = 0; i < 10; i++){
            //cout << "hello" << endl;
            ans = getSample(t, ans);
        }

    return ans;
}

void Graph::Task4(){
    auto start = chrono::high_resolution_clock::now();

    vector <int> path = simulatedAnnealing(adj.size());

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> aco_duration = end - start;
    std::cout << "Simulated Annealing Minimum cost: " << fixed << setprecision(2) << getValue(path) << std::endl;
    cout << "Path: ";
    for (int node : path) {
        cout << node << " -> ";
    }
    cout << "0" << endl;
    std::cout << "Execution time: " << aco_duration.count() << " seconds" << std::endl;
}
