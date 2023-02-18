//======== Copyright (c) 2023, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Maksym Podhornyi <xpodho08@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"
#include "algorithm"


Graph::Graph(){

    m_nodes = std::vector<Node*>();
    m_edges = std::vector<Edge>();

}

Graph::~Graph(){

    for (auto node : m_nodes){
        delete node;
    }

}

std::vector<Node*> Graph::nodes() {

    return m_nodes;

}

std::vector<Edge> Graph::edges() const{

    return m_edges;

}

Node* Graph::addNode(size_t nodeId) {

    for (auto node : m_nodes){
        if (node->id == nodeId){
            return nullptr;
        }
    }

    Node* newNode = new Node(nodeId);
    m_nodes.push_back(newNode);
    return newNode;

}


bool Graph::addEdge(const Edge& edge) {

    if (edge.a == edge.b || containsEdge(edge)) {
        return false;
    }

    addNode(edge.a);
    addNode(edge.b);

    m_edges.push_back(edge);
    return true;

}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {

    for (const auto& edge : edges) {
        addEdge(edge);
    }

}

Node* Graph::getNode(size_t nodeId){

    for (auto node : m_nodes){
        if (node->id == nodeId){
            return node;
        }
    }

    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const {

    for (const auto& e : m_edges) {
        if (e == edge) {
            return true;
        }
    }

    return false;
}

void Graph::removeNode(size_t nodeId) {

    bool nodeFound = false;

    for (auto it = m_nodes.begin(); it != m_nodes.end(); it++) {
        if ((*it)->id == nodeId) {
            m_nodes.erase(it);
            nodeFound = true;
            break;
        }
    }

    if (!nodeFound) {
        throw std::out_of_range("Node with given id does not exist in the graph.");
    }

    for (auto it = m_edges.begin(); it != m_edges.end(); it++) {
        if ((*it).a == nodeId || (*it).b == nodeId) {
            m_edges.erase(it);
            it--;
        }
    }

}


void Graph::removeEdge(const Edge& edge){

    for (auto it = m_edges.begin(); it != m_edges.end(); it++){
        if ((*it).a == edge.a && (*it).b == edge.b){
            m_edges.erase(it);
            return;
        }
    }

    throw std::out_of_range("Edge does not exist");
}

size_t Graph::nodeCount() const{

    return m_nodes.size();

}

size_t Graph::edgeCount() const{

    return m_edges.size();

}

size_t Graph::nodeDegree(size_t nodeId) const {

    for (auto node : m_nodes) {
        if (node->id == nodeId) {
            size_t degree = 0;
            for (auto edge : m_edges){
                if (edge.a == nodeId || edge.b == nodeId){
                    degree++;
                }
            }
            return degree;
        }
    }

    throw std::out_of_range("Node not found in graph");
}


size_t Graph::graphDegree() const{

    size_t maxDegree = 0;

    for (auto node : m_nodes){
        size_t degree = nodeDegree(node->id);
        if (degree > maxDegree){
            maxDegree = degree;
        }
    }

    return maxDegree;

}

void Graph::coloring(){

    int maxDegree = graphDegree();
    std::vector<bool> usedColors(maxDegree + 1, false);

    for (auto node : m_nodes){
        for (auto edge : m_edges){
            if (edge.a == node->id || edge.b == node->id){
                if (edge.a == edge.b){
                    throw std::runtime_error("Self-loop detected");
                }
                if (getNode(edge.a)->color != 0){
                    usedColors[getNode(edge.a)->color] = true;
                }
                if (getNode(edge.b)->color != 0){
                    usedColors[getNode(edge.b)->color] = true;
                }
            }
        }

        for (int i = 1; i <= maxDegree + 1; i++){
            if (!usedColors[i]){
                node->color = i;
                break;
            }
        }

        std::fill(usedColors.begin(), usedColors.end(), false);

    }
}

void Graph::clear() {

    for (auto node : m_nodes){
        delete node;
    }

    m_nodes.clear();
    m_edges.clear();

}

/*** Konec souboru tdd_code.cpp ***/
