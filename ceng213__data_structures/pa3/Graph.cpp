#include "Graph.h"
/*Do not add new libraries or files*/
Graph::Graph() {
}

Graph::Graph(const Graph& rhs) {
    this->adjList = rhs.adjList;
}

Graph& Graph::operator=(const Graph& rhs) {
    this->adjList = rhs.adjList;
    return *this;
}

Graph::~Graph() {
}

void Graph::addNode(const Node &node) {
    adjList.Insert(node.getCountry(), {});
}

void Graph::addConnection(const Node& headNode, const Node& tailNode, int import) {
    adjList.Get(headNode.getCountry()).push_back({tailNode, import});
}

list<Node> Graph::getAdjacentNodes(const Node& node) {
    list<Node> holder;
    for(list<Edge>::iterator iter = (adjList.Get(node.getCountry())).begin(),last = (adjList.Get(node.getCountry())).end();iter != last;){holder.push_back((iter++)->getTailNode());}
    return holder;
}

long Graph::getTotalImports(const Node& node) {
    long holder = 0;
    for (list<Edge>::iterator iter = adjList.Get(node.getCountry()).begin(); iter != adjList.Get(node.getCountry()).end(); ++iter){holder += iter->getImport();}
    return holder;
}

void Graph::deleteNode(const Node& node) {
    string *holder = new string[adjList.Size()],delete_node = node.getCountry();
    adjList.getKeys(holder);
    for (int i=0 ; i<adjList.Size() ; ++i){
        list<Edge>* tut = &(adjList.Get(holder[i]));
        for (list<Edge>::iterator it = tut->begin() ; it != tut->end() ;){(delete_node == it->getTailNode().getCountry()) ? it = tut->erase(it) : ++it;}  
    }
    delete[] holder;
    adjList.Delete(delete_node);
}

list<string> Graph::findLeastCostPath(const Node& srcNode, const Node& destNode) {
    priority_queue<Vertex,vector<Vertex>, CompareCost> travers;
    vector<Vertex> total_costs;
    list<Edge> connections;
    int i = 0, limit = adjList.Size();
    string src_name = srcNode.getCountry(), dest_name = destNode.getCountry(), *holder = new string[limit];
    adjList.getKeys(holder);
    Vertex str;
    for (int t = 0; t < limit; t++){total_costs.push_back({holder[t],"NULL",(holder[t] != src_name) ? 999999999 : 0});}
    travers.push({src_name, "NULL", 0});
    while (!travers.empty()){
        str = travers.top();
        connections = adjList.Get(str.name);
        travers.pop();
        for(list<Edge>::iterator iter = connections.begin();iter != connections.end();iter++){
            for (i = 0; i < total_costs.size(), (total_costs[i].name != iter->getTailNode().getCountry()); i++){}
                long current_cost = str.cost + iter->getImport();
                if(current_cost < total_costs[i].cost){
                    total_costs[i] = {total_costs[i].name,str.name,current_cost};
                    travers.push(total_costs[i]);
                }
        }    
    }
    for (i = 0; i < total_costs.size(),(total_costs[i].name != dest_name); i++){}
    str = total_costs[i];
    list<string> deneme;
    while (str.via != "NULL"){
        deneme.push_front(str.name);
        for(i = 0;i < total_costs.size(), (total_costs[i].name != str.via) ;i++){}
        str = {total_costs[i].name, total_costs[i].via, total_costs[i].cost};
    }
    deneme.push_front(src_name);
    delete[] holder;
    return deneme;
}

bool Graph::isCyclic() {
    string* keys = new string[adjList.Size()];
    adjList.getKeys(keys);
    for(int i=0 ; i<adjList.Size() ; ++i){
        list<string> current_path = getBFSPath({0,keys[i],"",0},{0,keys[i],"",0});
        if(current_path.back() == current_path.front() && current_path.size() > 2){
            delete[] keys;
            return true;
        }
    }
    delete[] keys;
    return false;
}

list<string> Graph::getBFSPath(const Node& srcNode, const Node& destNode) {
    string src_name = srcNode.getCountry(), dest_name = destNode.getCountry(),*keys = new string[adjList.Size()],current;
    adjList.getKeys(keys);
    vector<Travers> holder;
    int i,lim = adjList.Size();
    for(i=0 ; i < lim ; ++i){holder.push_back({keys[i],(keys[i] == src_name) ? true : false});}
    list<string> path_taken;
    queue<string> heap_memory;
    path_taken.push_back(src_name);
    heap_memory.push(src_name);
    while(!heap_memory.empty()){
        current = heap_memory.front();
        heap_memory.pop();
        for(list<Edge>::iterator it=adjList.Get(current).begin() ; it!=adjList.Get(current).end() ; ++it){
            if(dest_name == it->getTailNode().getCountry()){
                path_taken.push_back(dest_name);
                delete[] keys;
                vector<Travers>().swap(holder);
                return path_taken;
            }
            for(i=0 ; i<adjList.Size() , (keys[i] != it->getTailNode().getCountry()) ; ++i){}
            if(!holder[i].isVisited){
                holder[i].isVisited = true;
                heap_memory.push(it->getTailNode().getCountry());
                path_taken.push_back(it->getTailNode().getCountry());
            }
        }
    }
    delete[] keys;
    vector<Travers>().swap(holder);
    return path_taken;
}