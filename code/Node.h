//
// Created by mansur on 02-05-2023.
//

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * @brief Class representing a node of a Graph
 *
 * This class represents the node of a Graph and has attributes, id, latitude and longitude. This class represents real
 * global positions, represented by the attributes latitude and longitude. The attribute id allows the node to be easily
 * identified.
 */
class Node {
public:
    int id;
    double latitude;
    double longitude;

    /**
     * This operator specifies how an object of the class Node should be read into an input stream
     *
     * @param in - Input stream
     * @param node - Node to be read
     * @return Input stream with the Node given by parameter node
     */
    friend istream &operator>>(istream &in, Node &node);

    /**
     * This operator specifies how an object of the class Node should be written to an output stream
     *
     * @param out - Output stream
     * @param node - Node to be written
     * @return Output stream with the Node given by parameter node
     */
    friend ostream &operator<<(ostream &out, const Node &node);

    /**
     * @brief Calculates the distance between current node and another node
     * This functions calculates the distance between the current Node and the other Node given in parameter toNode
     *
     * @param toNode - Destination Node
     * @return double with the calculated distance between the nodes
     */
    double getDistance(const Node& toNode);
};


#endif //PROJECT_NODE_H
