#include <bits/stdc++.h>

using namespace std;
#define ll long long

typedef vector<int> vint;
typedef vector<long long> vll;

int N = 20;
vector<vint> adj;
vector<bool> vis;


stack<int> topo_sort;
vector<bool> rec_stack(N);
// Return true if detect a cycle (Directed)
bool topoSort(int node) {

    vis[node] = rec_stack[node] = 1;
    bool cycle = 0;
    for (auto it : adj[node]) {
        if (!vis[it]) cycle |= topoSort(it);
        else if(rec_stack[it]) return true;
    }

    topo_sort.push(node);
    rec_stack[node] = 0;
    return cycle;

}

// Kahn’s Algorithm
// Topo Sort lexicographically smallest one
void topoSortLex() {


    vector<int> indegree(N+1, 0);
    priority_queue<int, vector<int>, greater<int>> pq;

    int u, v, m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    for(int i = 1; i <= N; i++) {
        if(indegree[i] == 0) pq.push(i);
    }

    vector<int> ans;

    while(!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ans.push_back(u);

        for(int it : adj[u]) {
            indegree[it]--;
            if(indegree[it] == 0) pq.push(it);
        }
    }

    if(ans.size() != N) {
        cout << "Cycle Detected";
        return;
    }

    for(int x : ans) cout << x << " ";

}
