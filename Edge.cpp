//
// Created by mansur on 02-05-2023.
//

#include "Edge.h"

bool is_number(const string &s) {
    for (char x : s) {
        if (x < '0' || x > '9') {
            return false;
        }
    }
    return !s.empty();
}

istream &operator>>(istream &in, Edge &edge) {
    string s;
    getline(in, s, ',');
    if(is_number((s))){
        edge.to = stoi(s);
    }else return in;
    getline(in, s);
    edge.dist = stod(s);
    return in;
}

ostream &operator<<(ostream &out, const Edge &edge) {
    out << edge.to << " (" << edge.dist << ')';
    return out;
}