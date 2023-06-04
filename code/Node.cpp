//
// Created by mansur on 02-05-2023.
//

#include <cmath>
#include "Node.h"

istream &operator>>(istream &in, Node &node) {
    string s;
    getline(in, s, ',');
    if(s.empty()) return in;
    node.id = stoi(s);
    getline(in, s, ',');
    node.longitude = stod(s);
    getline(in, s);
    node.latitude = stod(s);
    return in;
}

ostream &operator<<(ostream &out, const Node &node) {
    out << '[' << node.id << "] (" << node.latitude << ';' << node.longitude << ')';
    return out;
}

double Node::getDistance(const Node& toNode) {
    double lat1 = latitude;
    double lon1 = longitude;
    double lat2 = toNode.latitude;
    double lon2 = toNode.longitude;

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371000;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}
