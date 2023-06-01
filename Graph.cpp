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
    V = adj.size();
    if(V < 2){
        cout << "Go home" << endl;
        exit(-1);
    }
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

void Graph::write_to_file(const std::string& text) {
    std::ofstream outputFile("output.txt", std::ios::app);

    if (outputFile.is_open()) {
        int textLength = text.length();
        int startPos = 0;
        int maxCharsPerLine = 80; // Maximum number of characters per line

        while (textLength > maxCharsPerLine) {
            int writeLength = maxCharsPerLine;
            std::string line = text.substr(startPos, writeLength);

            // Trim the line to end at the last arrow separator
            size_t lastArrowPos = line.find_last_of("->");
            if (lastArrowPos != std::string::npos) {
                line = line.substr(0, lastArrowPos + 2);
            }

            outputFile << line << '\n';

            startPos += line.length();
            textLength -= writeLength;
        }

        if (textLength > 0) {
            std::string remainingText = text.substr(startPos);
            outputFile << remainingText;
        }

        outputFile.close();
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

double Graph::getDistance(int from, int to) {
    for(auto el : adj[from]){
        if(el.to == to){
            return el.dist;
        }
    }
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

void Graph::Task1(bool print_path) {
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

    //cout << "--** Backtracking **--" << endl;
    //cout << "Minimum cost: " << fixed << setprecision(2) << ans << endl;

    //limpa o ficheiro antes de escrever
    std::ofstream outputFile("output.txt", std::ios::trunc);
    outputFile.close();

    write_to_file("--** Backtracking **--\n");
    write_to_file("Minimum cost: ");
    write_to_file(std::to_string(ans));

    write_to_file("Execution time: ");
    write_to_file(std::to_string(backtracking_duration.count()));
    write_to_file(" seconds\n");

    if(print_path){
        std::string pathString = "Path: ";
        for (int node : path) {
            pathString += std::to_string(node) + "->";
        }
        pathString += "0\n\n";
        write_to_file(pathString);
    }

}

// TODO Task2 ----------------------------------------------------------------------------------------------------------

vector<vector<Edge>> Graph::primMST() {
    size_t n = adj.size();
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

void Graph::Task2(bool print_path){
    auto start = chrono::high_resolution_clock::now();
    vector<vector<Edge>> p = primMST();

    int startNode = 0;
    vector<bool> visited(p.size(), false);
    vector<int> path;

    preorderWalk(startNode, p, visited, path);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> backtracking_duration = end - start;

    //cout << "--** Triangular approximation **--" << endl;
    //cout << "Minimum cost: " << fixed << setprecision(2) << getValue(path) << endl;

    std::ofstream outputFile("output.txt", std::ios::trunc);
    outputFile.close();

    write_to_file("--** Triangular approximation **--\n");
    write_to_file("Minimum cost: ");
    write_to_file(std::to_string(getValue(path)));
    write_to_file("\n");

    write_to_file("Execution time: ");
    write_to_file(std::to_string(backtracking_duration.count()));
    write_to_file(" seconds\n");

    if(print_path){
        std::string pathString = "Path: ";
        for (int node : path) {
            pathString += std::to_string(node) + "->";
        }
        pathString += "0\n\n";
        write_to_file(pathString);
    }
}

// TODO Task3 ----------------------------------------------------------------------------------------------------------

vector <int> Graph::ACO(vector<vector<float>>& distance_matrix, int max_iter,
                  int num_ants, double alpha, double beta, double rho) {
    int n = distance_matrix.size();
    vector<int> best_path(n);
    double best_distance = numeric_limits<double>::max();

    vector<vector<float>> pheromone(n, vector<float>(n, 1.0));

    for (int iter = 0; iter < max_iter; iter++) {
        vector<vector<int>> ant_paths(num_ants, vector<int>(n));

        for (int ant = 0; ant < num_ants; ant++) {
            vector<int> visited(n, 0);
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

                double rnd = (double)rand() / RAND_MAX;
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
            distance += distance_matrix[ant_paths[ant][n - 1]][0];  // stop in: 0

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

    return best_path;
}


void Graph::Task3(bool print_path){
    auto start = chrono::high_resolution_clock::now();
    int n = adj.size();
    vector<vector<float>> distance_matrix(n, vector<float>(n, UP_EPS));
    for(int i=0; i < adj.size(); ++i){
        for(int j=0; j < adj[i].size(); ++j){
            if( adj[i][j].to != -1 )
                distance_matrix[i][adj[i][j].to] = adj[i][j].dist;
        }
    }
    vector <int> path = ACO(distance_matrix, 100, 10, 1.0, 2.0, 0.1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> aco_duration = end - start;

    //cout << "--** ACO **--" << endl;
    //cout << "--** Test1 **--" << endl;
    //cout << "Minimum cost: " << fixed << setprecision(2) << getValue(path) << endl;

    std::ofstream outputFile("output.txt", std::ios::trunc);
    outputFile.close();

    write_to_file("--** Test1 **--\n");
    write_to_file("Minimum cost: ");
    write_to_file(std::to_string(getValue(path)));
    write_to_file("\n");

    write_to_file("Execution time: ");
    write_to_file(std::to_string(aco_duration.count()));
    write_to_file(" seconds\n");

    if(print_path){

        std::string pathString = "Path: ";
        for (int node : path) {
            pathString += std::to_string(node) + "->";
        }
        pathString += "0\n\n";
        write_to_file(pathString);
    }
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

bool randomBool(double p) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    double randomValue = dis(gen);
    return randomValue < p;
}

int getRand(int l, int r) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distribution(l, r);
    int randomNum = distribution(gen);

    return randomNum;

}

double Graph::getValue(vector <int>& v, bool out) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++){
        sum += getDistance(v[i], v[(i + 1) % v.size()]);
        if(out) cout << sum << endl;
    }
    return sum;
}

int Graph::id(int a) const {
    return a >= V ? 0: a;
}

void Graph::getSample(double t, vector <int>& v, double& curValue) {

    int l = getRand(1, v.size() - 1);
    int r = getRand(1, v.size() - 1);

    if(l > r) swap(l, r);

    if(l == r) return;

    double tmpValue = curValue - getDistance(v[l], v[id(l + 1)])
                                - getDistance(v[l - 1], v[l])
                                - getDistance(v[r - 1], v[r])
                                - getDistance(v[r], v[id(r + 1)])
                                + getDistance(v[l - 1], v[r])
                                + getDistance(v[r], v[id(l + 1)])
                                + getDistance(v[r - 1], v[l])
                                + getDistance(v[l], v[id(r + 1)]);

    if(r - l == 1){
        tmpValue = curValue + getDistance(v[l], v[id(r + 1)])
                            + getDistance(v[r], v[l - 1])
                            - getDistance(v[l],v[l - 1])
                            - getDistance(v[r],v[id(r + 1)]);
    }


    bool p = randomBool(exp((curValue - tmpValue) / t));

    if(p){
        swap(v[l], v[r]);
        curValue = tmpValue;
    }

}

vector <int> Graph::simulatedAnnealing(int n) {

    double t = 1e4;

    vector <int> ans = generateRandomPermutation(n);
    for(size_t i = 0; i < ans.size(); i++){
        if(!ans[i]){
            swap(ans[i], ans[0]);
        }
    }
    double value = getValue(ans);

    while(t > 0){
        getSample(t, ans, value);
        t -= 0.022;
    }

    return ans;
}

void Graph::Task4(bool print_path){
    auto start = chrono::high_resolution_clock::now();

    vector <int> path = simulatedAnnealing((int) adj.size());

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> aco_duration = end - start;

    //cout << "--** Simulated Annealing **--" << endl;
    //cout << "--** Test2 **--" << endl;
    //cout << "Minimum cost: " << fixed << setprecision(2) << getValue(path) << endl;

    std::ofstream outputFile("output.txt", std::ios::trunc);
    outputFile.close();

    write_to_file("--** Test2 **--\n");
    write_to_file("Minimum cost: ");
    write_to_file(std::to_string(getValue(path)));
    write_to_file("\n");

    write_to_file("Execution time: ");
    write_to_file(std::to_string(aco_duration.count()));
    write_to_file(" seconds\n");

    if(print_path){

        std::string pathString = "Path: ";
        for (int node : path) {
            pathString += std::to_string(node) + "->";
        }
        pathString += "0\n\n";
        write_to_file(pathString);
    }
}

// TODO TEST -----------------------------------------------------------------------------------------------------------

void Graph::test(){
    vector<vector<Edge>> p = primMST();

    for(int i = 0; i < p.size(); i++){
        cout << i << " -> { ";
        for(auto el : p[i]){
            cout << el.to << ", ";
        }
        cout << "} \n";
    }

}