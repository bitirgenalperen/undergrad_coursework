#include "Graph.h"

/*Do not add new libraries or files*/


Graph::Graph() {

}

Graph::Graph(const Graph& rhs) {
    adjList = rhs.adjList;
}

Graph& Graph::operator=(const Graph& rhs) {
    adjList = rhs.adjList;
    return *this;
}

Graph::~Graph() {

}


void Graph::addNode(const Node &node) {
    list<Edge> add;
    adjList.Insert(node.getCountry(),add);
}

void Graph::addConnection(const Node& headNode, const Node& tailNode, int import) {
    Edge add(tailNode,import);
    adjList.Get(headNode.getCountry()).push_back(add);
}

list<Node> Graph::getAdjacentNodes(const Node& node) {
    list<Node> result;
    list<Edge> edges = adjList.Get(node.getCountry());
    for(list<Edge>::iterator it=edges.begin() ; it!=edges.end() ; ++it){
        result.push_back(it->getTailNode());
    }
    return result;
}

long Graph::getTotalImports(const Node& node) {
    long result = 0;
    list<Edge> edges = adjList.Get(node.getCountry());
    for(list<Edge>::iterator it=edges.begin() ; it!=edges.end() ; ++it){
        result += it->getImport();
    }
    return result;
}

void Graph::deleteNode(const Node& node) {
    string* keys;
    keys = new string[adjList.Size()];
    adjList.getKeys(keys);
    list<Edge> edges;
    for(int i=0 ; i<adjList.Size() ; ++i){
        edges = adjList.Get(keys[i]);
        for(list<Edge>::iterator it=edges.begin() ; it!=edges.end() ; ++it){
            if(it->getTailNode().getCountry() == node.getCountry()){
                edges.erase(it);
            }
        }
    }
    delete[] keys;
    adjList.Delete(node.getCountry());
}

list<string> Graph::findLeastCostPath(const Node& srcNode, const Node& destNode) {
    // TODO: IMPLEMENT THIS FUNCTION.

}


bool Graph::isCyclic() {
    // TODO: IMPLEMENT THIS FUNCTION.

}


list<string> Graph::getBFSPath(const Node& srcNode, const Node& destNode) {
    // TODO: IMPLEMENT THIS FUNCTION.

}
