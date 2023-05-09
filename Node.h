//
// Created by mansur on 02-05-2023.
//

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
    int id;
    double lat;
    double log;
    friend istream &operator>>(istream &in, Node &node);
    friend ostream &operator<<(ostream &out, const Node &node);
};


#endif //PROJECT_NODE_H
