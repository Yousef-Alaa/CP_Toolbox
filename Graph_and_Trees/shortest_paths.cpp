#include <bits/stdc++.h>

using namespace std;
#define ll long long

typedef vector<int> vint;
typedef vector<long long> vll;

int N = 20;
vector<vint> adj;
vector<bool> vis;


ll bfs_shortest_path(int i, int j) {

    vll cost(N + 1, 1e18);
    queue<pair<int, int>> q;
    vis[i] = 1;
    q.push({i, 0});

    while (!q.empty()) {

        auto [nx, c] = q.front();
        q.pop();

        for (auto it : adj[nx]) {
            if (!vis[it]) {
                vis[it] = 1;
                q.push({it, c + 1});
                cost[it] = c + 1;
            }
        }
    }

    return cost[j];
}



void dijkstra(int start) {

    vint parent(N + 1, -1);
    vll cost(N + 1, 1e18);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq; // cost, node


    pq.push({0, start});
    cost[start] = 0;

    while (!pq.empty()) {
        
        auto [c, node] = pq.top();
        pq.pop();

        if (cost[node] < c) continue;

        for (auto [it, cs] : adj[node]) {
            if (c + cs < cost[it]) {
                parent[it] = node;
                cost[it] = c + cs;
                pq.push({c + cs, it});
            }
        }

    }

}

bool BellmanFord(int V, int E, int src) {
    
    vector<vint> edges(E, vint(3));// u, v, w

    vll cost(V, 1e18);
    cost[src] = 0;

    for (int i = 1;i <= V - 1;i++) {
        bool flag = true;
        for (int j = 0;j < E;j++) {
            
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];

            if (cost[u] != 1e18 && w + cost[u] < cost[v]) {
                flag = false;
                cost[v] = w + cost[u];
            }
        }

        if (flag) break;
    }
    
    for (int j = 0;j < E;j++) {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        if (cost[u] != 1e18 && w + cost[u] < cost[v]) {
            cout << "Negative Cycle Detected";
            return true;
        }
    }

    return false;

}

// Floyd:
// all to all shortest path in O(n^3) with memory of O(n^2)
// input is dist[i][j] for all i,j in (1:n) as weight between node i and node j
// initialize the matrix first with INF and zeros in the diagonal where (i == j)
// output :
// same matrix dist[i][j] will be shortest path between i, j
int n;
const int M = 500 + 5;
const int INF = 1e9;
int dist[M][M];
void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void solveFloyd() {
    cin >> n;
    int m, x;
    cin >> m >> x;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) dist[i][i] = 0;
            else dist[i][j] = INF;
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dist[a][b] = 1;
        dist[b][a] = 1;
    }
    floyd();
}

