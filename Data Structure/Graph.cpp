#include <bits/stdc++.h>

using namespace std;
#define ll long long

typedef vector<int> vint;

int N = 20;
vector<vint> adj;
vector<bool> vis;

void bfs(int start) {

    queue<int> q; 
    
    q.push(start);
    vis[start] = true;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for(auto it : adj[node]) {
            if(!vis[it]) {
                vis[it] = true;
                q.push(it);
            }
        }
    }
}

void dfs(int node) {

    vis[node] = true;
    cout << node << " ";

    for(auto it : adj[node]) {
        if(!vis[it]) {
            dfs(adj, vis, it);
        }
    }
}

// Undirected
bool dfsCycle(int node, int parent) {
    
    vis[node] = true;

    for (auto it : adj[node]) {
        
        if (!vis[it]) {

            if (dfsCycle(it, node, adj, vis)) {
                return true;
            }
        }
        else if (it != parent) {
            return true;
        }
    }
    return false;
}



stack<int> topo_sort;
vector<bool> rec_stack(N);
// Return true if detect a cycle (Directed)
bool topoSort(int node) {

    vis[node] = rec_stack[node] = 1;
    bool cycle = 0;
    for (auto it : adj[node]) {
        if (!vis[it]) cycle |= dfs(adj, vis, it);
        else if(rec_stack[it]) return true;
    }

    topo_sort.push(node);
    rec_stack[node] = 0;
    return cycle;

}


// Topo Sort lexicographically smallest one
void topoSortLex() {


    vector<int> indeg(N+1, 0);
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i = 1; i <= N; i++) {
        if(indeg[i] == 0) pq.push(i);
    }

    vector<int> ans;

    while(!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ans.push_back(u);

        for(int it : adj[u]) {
            indeg[it]--;
            if(indeg[it] == 0) pq.push(it);
        }
    }

    if(ans.size() != N) {
        cout << "Cycle Detected";
        return;
    }

    for(int x : ans) cout << x << " ";

}



int main() {

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int n, m, x, y;
    cin >> n >> m;

    adj.resize(n + 1);
    vis.resize(n + 1);

    while (m--) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    cout << "Hello Graph\n";
    dfs(adj, vis, 0);
    cout << "\n";
    bfs(adj, 0);
    cout << "\n";

    for (int i = 0;i < n;i++) vis[i] = false;
    cout << (dfsCycle(0, -1, adj, vis) ? "Cycle\n" : "No Cycle\n");



}