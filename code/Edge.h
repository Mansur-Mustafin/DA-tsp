//
// Created by mansur on 02-05-2023.
//

#ifndef PROJECT_EDGE_H
#define PROJECT_EDGE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * @brief Class representing an edge of a graph
 *
 * This class represents the edge of a graph, with its attributes "to" and "dist". "to" represents the index of
 * the starting point of a next edge and "dist" represents the distance to said starting point
 */
class Edge {
public:
    int to = -1;
    double dist = 1e9;

    /**
     * This operator specifies how an object of the class Edge should be read into an input stream
     *
     * @param in - Input stream
     * @param edge - Edge to be read
     * @return Input stream with the Edge given by parameter edge
     */
    friend istream &operator>>(istream &in, Edge &edge);

    /**
     * This operator specifies how an object of the class Edge should be written to an output stream
     *
     * @param out - Output stream
     * @param edge - Edge to be written
     * @return Output stream with the Edge given by parameter edge
     */
    friend ostream &operator<<(ostream &out, const Edge &edge);
};

#endif //PROJECT_EDGE_H
