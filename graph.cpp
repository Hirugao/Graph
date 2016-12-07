#include<iostream>
#include<vector>
#include<set>
#include<cstdlib>
#include<time.h>

using namespace std;

#define NODE 100

class Graph{
    vector<vector<int>>graph;
    //init used,unused and graph.
    void init_graph(vector<int>&,vector<int>&);
    //select node from unused.And return number of node.
    int select_connect(vector<int>&);
    //select node to be connected from used.
    //And store numbers of nodes to connected_node.
    void select_connected(vector<int>&,set<int>&);
    //Connect connect_node to connected_nodes in the graph.
    void connect_graph(int,set<int>&,vector<int>&,vector<int>&);
    //move node to used from unused.
    void move_node(vector<int>&,int);
    //Display a graph in the form of adjacency matrix.
    void print_graph();
    public:
    void create_graph();
}obj;

void Graph::init_graph(vector<int>&used,vector<int>&unused){
    graph.resize(NODE);
    for(int i=0;i<NODE;i++){
        unused.push_back(i);
    };
    int connect_node;
    //choose first two points.
    for(int i=0;i<2;i++){
        connect_node=select_connect(unused);
        if(i==1){
            graph[connect_node].push_back(used[0]);
            graph[used[0]].push_back(connect_node);
        }
        move_node(used,connect_node);
    }
}

int Graph::select_connect(vector<int>&unused){
    int suffix=rand()%unused.size();
    int number=unused[suffix];
    unused.erase(unused.begin()+suffix);
    return number;
}

//connectednodes:vector-->set
void Graph::select_connected(vector<int>&used,set<int>&connected_nodes){
    int numbers=rand()%used.size()+1;
    for(int i=0;i<numbers;i++){
        int suffix=rand()%used.size();
        if(connected_nodes.count(used[suffix])!=0){
            i--;
            continue;
        }else{
            connected_nodes.insert(used[suffix]);
        }
    }
}

void Graph::connect_graph(int connect_node,set<int>&connected_nodes,
                   vector<int>&used,vector<int>&unused){
    if(connect_node==-1||connected_nodes.size()==0){
        cout<<"Error!"<<endl;
        return;
    }
    for(auto itr=connected_nodes.begin();itr!=connected_nodes.end();++itr){
        graph[connect_node].push_back(*itr);
        graph[*itr].push_back(connect_node);
    }
    move_node(used,connect_node);
    connect_node=-1;
    connected_nodes.clear();
}


void Graph::move_node(vector<int>&used,int number){
    used.push_back(number);
}

void Graph::print_graph(){
    cout<<"---------------graph-------------"<<endl;
    cout<<'{'<<endl;
    for(int i=0;i<graph.size();i++){
        cout<<i<<"-->"<<'{';
        for(int j=0;j<graph[i].size();j++){
            cout<<graph[i][j]<<" ,";
        }
        cout<<'}'<<endl;
    }
    cout<<'}'<<endl;
}

void Graph::create_graph(){
    vector<int>used,unused;
    //from unused.
    int connect_node;
    //from used.
    set<int>connected_nodes;
    
    init_graph(used,unused);

    while(!unused.empty()){
       connect_node=select_connect(unused); 
       select_connected(used,connected_nodes);
       connect_graph(connect_node,connected_nodes,used,unused);
    }
    print_graph();
}



int main(){
    srand(time(NULL));
    obj.create_graph();
    return 0;
}
