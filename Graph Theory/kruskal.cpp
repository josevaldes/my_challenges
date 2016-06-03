#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N;
int E;

struct edge
{
    unsigned int v1;
    unsigned int v2;
    unsigned int cost;
};

struct cmp
{
    bool operator()(edge* e1, edge* e2)
    {
        if(e1->cost == e2->cost)
        {
            return (e1->v1 + e1->v2) < (e2->v1 + e2->v2);
        }
        else
        {
           return e1->cost < e2->cost;
        }
    }
} edgeCompare;

vector<edge*> edges;

void initialization()
{
    edges.resize(E);
    for(unsigned int i = 0; i < E; ++i)
    {
        unsigned int v1, v2, cost;
        cin >> v1;
        --v1;
        cin >> v2;
        --v2;
        cin >> cost;
        edge* curr = new edge();
        if(v1 < v2)
        {
            curr->v1 = v1;
            curr->v2 = v2;
        }
        else
        {
            curr->v1 = v2;
            curr->v2 = v1;
        }
        curr->cost = cost;
        edges[i]   = curr;
        
    }
    
    sort(edges.begin(), edges.end(), edgeCompare);
}

bool union_find(vector<unsigned int>& nodes, const edge & currEdge)
{
    unsigned int parent1  = nodes[currEdge.v1];
    unsigned int parent2  = nodes[currEdge.v2];
    
    while(parent1 != nodes[parent1])
    {
        parent1 = nodes[parent1];
    }
    
    while(parent2 != nodes[parent2])
    {
        parent2 = nodes[parent2];
    }
    
    bool flag = (parent1 == parent2);
    
    if(!flag)
    {
        nodes[parent2] = nodes[parent1];
    }
    return flag;
   
}

unsigned int kruskal()
{
    unsigned int mst_weight = 0;
    vector<unsigned int> nodeSet(N);
    for(unsigned int i = 0; i < N; ++i)
    {
        nodeSet[i] = i;
    }
    
    for(unsigned int j = 0; j < E; ++j)
    {
        edge* ite = edges[j];
        if(!union_find(nodeSet, *ite))
        {
            mst_weight += ite->cost;
        }
    }
    
    return mst_weight;
}

void removePtrs()
{
    for(unsigned int i = 0; i < E; ++i)
    {
        delete edges[i];
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    cin >> N;
    cin >> E;
    initialization();
    unsigned int mst_weight = kruskal();
    cout << mst_weight << endl;
    removePtrs();
    return 0;
    
}
