//
// Created by mansur on 02-05-2023.
//

#ifndef PROJECT_EDGE_H
#define PROJECT_EDGE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Edge {
public:
    //int s;
    int to;
    float dist;
    //int prev_pos = 0;
    friend istream &operator>>(istream &in, Edge &edge);
    friend ostream &operator<<(ostream &out, const Edge &edge);
};

#endif //PROJECT_EDGE_H
