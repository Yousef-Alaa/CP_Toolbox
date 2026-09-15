#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vint;
typedef pair<int, int> pint;

class BCC {
private:
    int n, timer;
    stack<pint> st;
    vector<vint> adj;
    vector<bool> isArt;
    vector<pint> bridges;
    vint disc, low, parent;
    vector<vector<pint>> bcc;

    void tarjan(int u, int par = -1) {
        
        int ch = 0;
        disc[u] = low[u] = ++timer;

        for (int v : adj[u]) {
            if (v == par) continue;
            if (disc[v] == -1) {
                ch++;
                st.push({u, v});
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if ((par != -1 && low[v] >= disc[u]) || (par == -1 && ch > 1)) isArt[u] = 1;
                if (low[v] > disc[u]) bridges.push_back({u, v});
                if (low[v] >= disc[u]) {
                    vector<pint> comp;
                    while (1) {
                        auto e = st.top();
                        st.pop();
                        comp.push_back(e);
                        if (e.first == u && e.second == v) break;
                    }
                    bcc.push_back(comp);
                }
            } else if (disc[v] < disc[u]) {
                low[u] = min(low[u], disc[v]);
                st.push({u, v});
            }
        }
    }

public:
    BCC(vector<vint>& adj_, int n_) {
        
        n = n_;
        timer = 0;
        adj = adj_;
        low.assign(n + 1, 0);
        disc.assign(n + 1, -1);
        isArt.assign(n + 1, 0);
        parent.assign(n + 1, -1);
        
        for (int i = 1; i <= n; i++) {
            if (disc[i] == -1) {
                tarjan(i);
                if (!st.empty()) {
                    vector<pint> comp;
                    while (!st.empty()) {
                        comp.push_back(st.top());
                        st.pop();
                    }
                    bcc.push_back(comp);
                }
            }
        }

        for (auto &[a, b] : bridges) if (a >= b) swap(a, b);
    }

    vint getArtPoints() {
        vint res;
        for (int i = 1; i <= n; i++) if (isArt[i]) res.push_back(i);
        return res;
    }

    vector<vint> getTree() {
        
        int cnt = 1;
        vint id(n + 1);
        vector<bool> vis(n + 1);
        map<pint, bool> isBridge;

        for (auto it : bridges) isBridge[it] = 1;

        function<void(ll, ll)> dfs = [&](ll i, ll cnt) -> void {
            
            vis[i] = 1;
            id[i] = cnt;

            for (auto it : adj[i]) {
                int a = i, b = it;
                if (a >= b) swap(a, b);
                if (!vis[it] && !isBridge[{a, b}]) {
                    dfs(it, cnt);
                }
            }
        };

        for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i, cnt++);
        
        vector<vint> mat(cnt);
        for (auto [a, b] : bridges) {
            mat[id[a]].push_back(id[b]);
            mat[id[b]].push_back(id[a]);
        }
        
        return mat;
    }

    bool isA(int u) { return isArt[u]; }
    vector<pint> getBridges() { return bridges; }
    vector<vector<pint>> getEdgeBCC() { return bcc; }
};