//
// Created by mansur on 02-05-2023.
//

#include "Node.h"

istream &operator>>(istream &in, Node &node) {
    string s;
    getline(in, s, ',');
    if(s.empty()) return in;
    node.id = stoi(s);
    getline(in, s, ',');
    node.log = stod(s);
    getline(in, s);
    node.lat = stod(s);
    return in;
}

ostream &operator<<(ostream &out, const Node &node) {
    out << '[' << node.id << ']';
    return out;
}
