#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
#include <map>

using namespace std;

struct Node
{
    unsigned int label;
    list<unsigned int> neighbors;
    map<unsigned int, unsigned int> costs;
};

struct heapNode
{
    unsigned int vertex;
    unsigned int cost;
};

struct cmp
{
    bool operator() (heapNode* a, heapNode* b)
    {
        return a->cost > b->cost;
    }
};

vector<Node> nodes;
unsigned int N;
unsigned int E;

void initialize()
{
    cin >> N;
    cin >> E;
    nodes.resize(N);
    for(unsigned int i = 0; i < nodes.size(); ++i)
    {
        Node curr;
        curr.label = i;
        nodes[i] = curr;
    }
    
    for(unsigned int i = 0; i < E; ++i)
    {
        unsigned int v1, v2, cost;
        cin >> v1;
        --v1;
        cin >> v2;
        --v2;
        
        cin >> cost;
        
        nodes[v1].neighbors.push_back(v2);
        nodes[v2].neighbors.push_back(v1);
        
        if(nodes[v1].costs[v2] == 0 || cost < nodes[v1].costs[v2] )
        {
           nodes[v1].costs[v2] = cost;
           nodes[v2].costs[v1] = cost;
        }
    }
}

unsigned int Prims()
{
    vector<bool> visited(N);
    unsigned int start;
    unsigned int mst_weight = 0;
    cin >> start;
    --start;
    
    priority_queue<heapNode*, vector<heapNode*>, cmp> heap;
    heapNode* first = new heapNode;
    first->vertex = start;
    first->cost   = 0;
    heap.push(first);
    
    while(!heap.empty())
    {
       heapNode* ite = heap.top();
       heap.pop();
       if(!visited[ite->vertex])
       {
           mst_weight += ite->cost;
       }
       visited[ite->vertex] = true;
       
       //cerr << "Vertex: " << ite->vertex + 1 << " Cost: " << ite->cost << endl;
        
       for(list<unsigned int>::iterator it = nodes[ite->vertex].neighbors.begin(); it != nodes[ite->vertex].neighbors.end(); ++it)
       {
          if(!visited[*it])
          {
              heapNode* other = new heapNode;
              other->vertex   = *it;
              other->cost     = nodes[ite->vertex].costs[*it];
              heap.push(other);
          }
       }
    }
    
    return mst_weight;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    initialize();
    unsigned int mst_weight = Prims();
    cout << mst_weight << endl;
    return 0;
}
