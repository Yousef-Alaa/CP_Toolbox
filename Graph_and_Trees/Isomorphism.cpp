#include <bits/stdc++.h>

using namespace std;


#define all(v) v.begin(),v.end()
#define f(fr, end) for (int i = fr; i < end; i++)
#define fj(fr, end) for (int j = fr; j < end; j++)


vector<vector<int>> adj;

// First snippet (Rooted Tree Canonical Form)
string treeCanoincalForm(int i, int par) {
    
    vector<string> childern;

    for (int ch : adj[i]) 
        if(ch != par) childern.push_back(treeCanoincalForm(ch, i));

    string nodeRep = "(";
    sort(all(childern));
    for (auto s : childern) nodeRep += s;
    nodeRep += ")";

    return nodeRep;
}

// we could use hashing for a better performance
string nodeForm(int v, vector<vector<string>> &subCan) {
    
    string nodeRep = "(";
    sort(all(subCan[v]));
    f(0, subCan[v].size()) nodeRep += subCan[v][i];
    nodeRep += ")";

    return nodeRep;
}

/*
 * Tree shrinking algorithm. Each time leaves shrink toward their parents.
 * assumes tree not forest
 */

string treeCanoincal() {
    
    int n = adj.size();

    // Prepare level one nodes: the leaves
    int remNodes = n;
    queue<int> LeafNodes;
    vector<int> deg(n, -1);

    f(0, n) {
        if(adj[i].size() <= 1) LeafNodes.push(i);
        else deg[i] = adj[i].size();
    }

    vector<vector<string>> subCan(n);

    while(remNodes > 2) { // bfs-like
    
        int sz = LeafNodes.size();
        while(sz--) { // level by level
        
            int v = LeafNodes.front();
            LeafNodes.pop();

            string nodeRep = nodeForm(v, subCan);

            for (int to : adj[v]) {
                subCan[to].push_back(nodeRep);
                if(--deg[to] == 1) LeafNodes.push(to);
            }
            
            remNodes--;
        }
    }

    // what remains are tree centers
    int v1 = LeafNodes.front();
    LeafNodes.pop();
    int v2 = LeafNodes.empty() ? -1 : LeafNodes.front();

    string str1 = nodeForm(v1, subCan);
    string str2 = v2 == -1 ? "" : nodeForm(v2, subCan);

    // only 1 node
    if(v2 == -1) return str1;

    // 2 nodes. try 2nd as child of first and reverse
    subCan[v1].push_back(str2);
    subCan[v2].push_back(str1);

    return min(nodeForm(v1, subCan), nodeForm(v2, subCan));
}

