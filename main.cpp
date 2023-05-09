#include <iostream>
#include "Graph.h"


int main() {
    Graph g("shipping.csv");
    vector<pair<int, float>> p = g.primMST();

    vector<vector<Edge>> mst (p.size());

    for(int i = 0; i < p.size(); i ++){
        if(p[i].first != -1){
            mst[p[i].first].push_back({i, (p[i].second)});
        }
    }

    for(int i = 0 ; i < mst.size(); i++){
        cout << '[' << i << "] :" << endl;
        for(auto e: mst[i]){
            cout << "---" << e << endl;
        }
    }

    //g.print_edges();
    //g.Task1();

    return 0;
}
