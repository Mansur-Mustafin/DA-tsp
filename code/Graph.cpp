//
// Created by mansur on 02-05-2023.
//

#include <fstream>
#include "Graph.h"
#include <chrono>
#include <limits>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <climits>

using namespace std;

Graph::Graph(const string &input_edge_name, const string &input_node_name) : out("output.txt", ios::app){

    if(input_node_name.empty()) {
        if (input_edge(input_edge_name, false)) exit(-1);
    }else{
        if (input_edge(input_edge_name, true)) exit(-1);
        if( input_vertex(input_node_name)) exit(-1);
    }
    file_edge_name = input_edge_name;
    file_nodes_name = input_node_name;
    V = adj.size();

    out << "File: " << file_edge_name << " ________________________________________________________\n" << endl;

    if(V < 2){
        cout << "Bro..." << endl;
        exit(-1);
    }
    if(!out){
        cerr << "File: output.txt unable to open." << endl;
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
        if(s[0] >= '0' && s[0] <= '9'){ // if no header in a file
            stringstream ss(s);
            getline(ss, from, ',');
            string to_str, dist_str;
            getline(ss, to_str, ',');
            getline(ss, dist_str);
            e.to = stoi(to_str);
            e.dist = stod(dist_str);
            int f = stoi(from);
            int maxNode = max(e.to, f);
            while(adj.size() <= maxNode){
                adj.emplace_back();
            }
            adj[f].push_back(e);
            adj[e.to].push_back({f, e.dist});
        }
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

void Graph::write_to_file(const string& text) {
    ofstream outputFile("output.txt", ios::app);

    if (outputFile.is_open()) {
        size_t textLength = text.length();
        size_t startPos = 0;
        int maxCharsPerLine = 80; // Maximum number of characters per line

        while (textLength > maxCharsPerLine) {
            int writeLength = maxCharsPerLine;
            string line = text.substr(startPos, writeLength);

            // Trim the line to end at the last arrow separator
            size_t lastArrowPos = line.find_last_of("->");
            if (lastArrowPos != string::npos) {
                line = line.substr(0, lastArrowPos + 2);
            }

            outputFile << line << '\n';

            startPos += line.length();
            textLength -= writeLength;
        }

        if (textLength > 0) {
            string remainingText = text.substr(startPos);
            outputFile << remainingText;
        }

        outputFile.close();

    }
}

double findStart(const vector<Edge>& v){
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

void printPath(const vector<int>& v){
    string pathString = "Path: ";
    for (int node : v) {
        pathString += to_string(node) + "->";
    }
    pathString += "0\n\n";
    Graph::write_to_file(pathString);
}

// TODO Backtracking----------------------------------------------------------------------------------------------------

void Graph::tspBackTracking(vector<bool> &v, int currPos, size_t n, int count, double cost, double &ans, vector<int> &path, vector<int> &bestPath) {

    if (cost >= ans) return;

    if (count == n && findStart(adj[currPos])) {
        if (cost + findStart(adj[currPos]) < ans) {
            ans = cost + findStart(adj[currPos]);
            bestPath = path;
            cout << fixed << setprecision(2) << ans << endl;
            //out << "Find the best path: " << fixed << setprecision(2) << ans << endl;
            //for(auto el: path) out << el << " ";
            //out << endl << endl;
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

void Graph::Task1(bool show_path) {
    size_t n = adj.size();
    if(n > 15){
        cout << "Backtracking stop" << endl;
        out << "--** Backtracking **--\n";
        out << "This algorithm is inefficient for this size of graphs" << "\n";
        out << "I have one week left to complete the project, algorithm takes more.\n" << endl;
        return;
    }
    vector<bool> v(n);
    for (int i = 0; i < n; i++)
        v[i] = false;

    v[0] = true;
    double ans = 1e9;
    vector<int> path = {0};
    vector<int> bestPath;

    auto start = chrono::high_resolution_clock::now();
    tspBackTracking(v, 0, n, 1, 0, ans, path, bestPath);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> backtracking_duration = end - start;

    out << "--** Backtracking **--\n";
    out << "Minimum cost: " << fixed << setprecision(2) << ans << "\n";
    out << "Execution time: " << backtracking_duration.count() << " seconds\n" << endl;

    if(show_path)
        printPath(path);

}

// TODO Task2 ----------------------------------------------------------------------------------------------------------

vector<vector<Edge>> Graph::primMST(vector<vector<Edge>> tree) {
    size_t n = tree.size();
    vector<pair<int, float>>  parent (n, {-1, 0.0});
    vector<double> dist(n, numeric_limits<double>::max());
    vector<bool> visited(n, false);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    parent[0] = {-1, 0.0};
    dist[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge &e : tree[u]) {
            double edge_dist = e.dist;
            if (!visited[e.to] && edge_dist < dist[e.to]) {
                dist[e.to] = edge_dist;
                parent[e.to] = {u, edge_dist};
                pq.emplace(edge_dist, e.to);
            }
        }

    }

    vector<vector<Edge>> mst (n);

    for(int i = 0; i < n; i++){
        if(parent[i].first != -1){
            int w = parent[i].first;
            double distance = parent[i].second;
            mst[w].push_back({i, distance});
            mst[i].push_back({w, distance}); // mst bidirectional
        }
    }

    /*
    double cost = 0.0;
    for(int i = 0; i < mst.size(); i++){
        if(mst[i].empty()) continue;
        cout << '[' << i << "] -> ";
        for(auto el: mst[i]){
            cout << el.to << ' ';
            cost += el.dist;
        }
        cout << endl;
    }
    cout << "cost of mst: " << cost;
    */

    return mst;
}

void Graph::preorderWalk(int node, const vector<vector<Edge>> &mst, vector<bool> &visited, vector<int> &path) {
    visited[node] = true;
    path.push_back(node);

    vector<Edge> children = mst[node];

//    sort(children.begin(), children.end(), [&](const Edge &a, const Edge &b) {
//        if(nodes[a.to].latitude == nodes[b.to].latitude) return nodes[a.to].longitude < nodes[b.to].longitude;
//        return nodes[a.to].latitude < nodes[b.to].latitude;
//    });

    sort(children.begin(), children.end(), [&](const Edge &a, const Edge &b) {
        return nodes[a.to].getDistance(nodes[node]) < nodes[b.to].getDistance(nodes[node]);
    });

//     sort(children.begin(), children.end(), [&](const Edge &a, const Edge &b) {
//         return nodes[a.to].latitude < nodes[b.to].latitude;
//     });

    for (const Edge &edge : children) {
        if (!visited[edge.to]) {
            preorderWalk(edge.to, mst, visited, path);
        }
    }
}

void Graph::Task2(bool show_path){
    auto start = chrono::high_resolution_clock::now();
    vector<vector<Edge>> p = primMST(adj);

    int startNode = 0;
    vector<bool> visited(p.size(), false);
    vector<int> path;

    preorderWalk(startNode, p, visited, path);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> backtracking_duration = end - start;

    out << "--** Triangular approximation **--\n";
    out << "Minimum cost: " << fixed << setprecision(2) << getValue(path) << "\n";
    out << "Execution time: " << backtracking_duration.count() << " seconds\n" << endl;

    if(show_path)
        printPath(path);
}

// TODO Task3_1 ----------------------------------------------------------------------------------------------------------

vector <int> Graph::ACO(vector<vector<double>>& distance_matrix, int max_iter,
                        int num_ants, double alpha, double beta, double rho) {
    int n = distance_matrix.size();
    vector<int> best_path(n);
    double best_distance = numeric_limits<double>::max();

    vector<vector<float>> pheromone(n, vector<float>(n, 1.0));

    for (int iter = 0; iter < max_iter; iter++) {
        vector<vector<int>> ant_paths(num_ants, vector<int>(n));

        for (int ant = 0; ant < num_ants; ant++) {
            vector<int> visited(n, 0);
            ant_paths[ant][0] = 0;  // Start vertex is 0
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

void Graph::Task3_1(bool show_path){

    vector<vector<double>> distance_matrix(V, vector<double>(V, UP_EPS));
    for(int i=0; i < adj.size(); ++i){
        for(int j=0; j < adj[i].size(); ++j){
            if( adj[i][j].to != -1 )
                distance_matrix[i][adj[i][j].to] = adj[i][j].dist;
        }
    }

    /*
    vector<pair<int, int>> a = {{100, 10}, {300, 5}, {500, 3}, {800, 2}};

    for(auto el : a){
        out << el.first << '\t' << el.second << '\t';
        auto start = chrono::high_resolution_clock::now();
        vector <int> path = ACO(distance_matrix, el.first, el.second, 1.0, 2.0, 0.1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> aco_duration = end - start;
        out << fixed << setprecision(1) << getValue(path) << '\t' << aco_duration.count() << endl;
    }
     */


    auto start = chrono::high_resolution_clock::now();
    vector <int> path = ACO(distance_matrix, 500, 3, 1.0, 2.0, 0.1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> aco_duration = end - start;

    out << "--** ACO **--\n";
    out << "Minimum cost: " << fixed << setprecision(2) << getValue(path) << "\n";
    out << "Execution time: " << aco_duration.count() << " seconds\n" << endl;

    if(show_path)
        printPath(path);
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

double Graph::getValue(vector <int>& v) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++){
        sum += getDistance(v[i], v[(i + 1) % v.size()]);
    }
    return sum;
}

int Graph::id(int a) const {
    return a >= V ? 0: a;
}

void Graph::getSample(double t, vector <int>& v, double& curValue) {

    int l = getRand(1, (int) v.size() - 1);
    int r = getRand(1, (int) v.size() - 1);

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

void Graph::Task3_2(bool show_path){
    auto start = chrono::high_resolution_clock::now();

    vector <int> path = simulatedAnnealing((int) adj.size());

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> aco_duration = end - start;

    out << "--** Test2 **--\n";
    out << "Minimum cost: " << fixed << setprecision(2) << getValue(path) << "\n";
    out << "Execution time: " << aco_duration.count() << " seconds\n" << endl;

    if(show_path)
        printPath(path);
}

// TODO TASK 2 USING MATRIX---------------------------------------------------------------------------------------------

void Graph::Task2_2(bool show_path){

    vector<vector<Edge>> distance_matrix(V, vector<Edge>(V));

    for(int i = 0; i < adj.size(); ++i){
        for(int j = 0; j < adj[i].size(); ++j){
            if( adj[i][j].to != -1 )
                distance_matrix[i][adj[i][j].to] = adj[i][j];
        }
    }

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(distance_matrix[i][j].dist + 1 > UP_EPS && i != j){
                distance_matrix[i][j].dist = nodes[i].getDistance(nodes[j]);
                distance_matrix[i][j].to = j;
            }
        }
    }

    auto start = chrono::high_resolution_clock::now();

    vector<vector<Edge>> p = primMST(distance_matrix);

    int startNode = 0;
    vector<bool> visited(p.size(), false);
    vector<int> path;

    preorderWalk(startNode, p, visited, path);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> aco_duration = end - start;

    out << "--** Triangular approximation using matrix **--\n";
    out << "Minimum cost: " << fixed << setprecision(2) << getValue(path) << "\n";
    out << "Execution time: " << aco_duration.count() << " seconds\n" << endl;

    if(show_path)
        printPath(path);

}

//TODO Christofides Algorithm ------------------------------------------------------------------------------------------

// Находим mst для графа и затем находим минимальное весовое сочетание (minimum-weight perfect matching) среди вершин с нечетными степенями в mst.
vector<pair<int, int>> findMatching(const vector<vector<Edge>>& mst) {
    size_t n = mst.size();
    vector<pair<int, int>> matching;

    vector<int> oddDegreeVertices;
    for (int i = 0; i < n; i++) {
        if (mst[i].size() % 2 != 0) {
            oddDegreeVertices.push_back(i);
        }
    }

    vector<bool> visited(n, false);
    for (int u : oddDegreeVertices) {
        if (!visited[u]) {
            float minWeight = INT_MAX;
            int minV = -1;

            for (const Edge& e : mst[u]) {
                int v = e.to;
                float weight = e.dist;
                if (!visited[v] && weight < minWeight) {
                    minWeight = weight;
                    minV = v;
                }
            }

            if (minV != -1) {
                matching.push_back({ u, minV });
                visited[u] = true;
                visited[minV] = true;
            }
        }
    }

    return matching;
}

// Создаем Эйлеров цикл сочетанием edges из MST и matching edges
vector<int> createEulerianCircuit(const vector<vector<Edge>>& mst, const vector<pair<int, int>>& matching) {
    size_t n = mst.size();
    vector<int> circuit;

    // Добавляем edges из MST в цикл
    for (int u = 0; u < n; u++) {
        for (const Edge& e : mst[u]) {
            int v = e.to;
            circuit.push_back(u);
            circuit.push_back(v);
        }
    }

    // Добавляем matching edges в цикл
    for (const auto& match : matching) {
        int u = match.first;
        int v = match.second;
        circuit.push_back(u);
        circuit.push_back(v);
    }

    return circuit;
}

// Ищем Гамильтонов цикл, удаляя повторяющиеся вершины из йэлерова цикла
vector<int> createHamiltonianCircuit(const vector<int>& eulerianCircuit) {
    vector<int> hamiltonianCircuit;

    set<int> visited;
    for (int v : eulerianCircuit) {
        if (visited.find(v) == visited.end()) {
            hamiltonianCircuit.push_back(v);
            visited.insert(v);
        }
    }

    return hamiltonianCircuit;
}

// Локальная 2-Opt search оптимизация
vector<int> twoOptLocalSearch(const vector<int>& circuit, const vector<vector<double>>& distanceMatrix) {
    vector<int> bestPath = circuit;
    int n = bestPath.size();

    bool improvement = true;
    while (improvement) {
        improvement = false;

        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 2; j < n - 1; j++) {
                double d1 = distanceMatrix[bestPath[i]][bestPath[i + 1]] + distanceMatrix[bestPath[j]][bestPath[j + 1]];
                double d2 = distanceMatrix[bestPath[i]][bestPath[j]] + distanceMatrix[bestPath[i + 1]][bestPath[j + 1]];

                if (d2 < d1) {
                    reverse(bestPath.begin() + i + 1, bestPath.begin() + j + 1);
                    improvement = true;
                }
            }
        }
    }

    return bestPath;
}

// Christofides algorithm
void Graph::Task2_3(bool show_path) {

    auto start = chrono::high_resolution_clock::now();

    // Находим  MST графа
    vector<vector<Edge>> mst = primMST(adj);

    // Находим minimum-weight perfect matching в MST
    vector<pair<int, int>> matching = findMatching(mst);

    // Создаем Эйлеров цикл
    vector<int> eulerianCircuit = createEulerianCircuit(mst, matching);

    // Гамильтонов цикл
    vector<int> hamiltonianCircuit = createHamiltonianCircuit(eulerianCircuit);

    vector<vector<double>> distance_matrix(V, vector<double>(V, UP_EPS));
    for(int i=0; i < adj.size(); ++i){
        for(int j=0; j < adj[i].size(); ++j){
            if( adj[i][j].to != -1 )
                distance_matrix[i][adj[i][j].to] = adj[i][j].dist;
        }
    }

    // Используем 2-opt оптимизацию
    vector<int> bestPath = twoOptLocalSearch(hamiltonianCircuit, distance_matrix);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> aco_duration = end - start;

    out << "--** Triangular approximation using Christofides Algorithm **--\n";
    out << "Minimum cost: " << fixed << setprecision(2) << getValue(bestPath) << "\n";
    out << "Execution time: " << aco_duration.count() << " seconds\n" << endl;

    if(show_path)
        printPath(bestPath);

}

