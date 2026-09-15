#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vint;

#define all(v) v.begin(),v.end()


class SCC {
private:
    int n, timer = 0;
    stack<int> st;
    vector<bool> inSt;
    vint disc, low, id;
    vector<vint> adj, comps;

    void tarjan(int u) {
        disc[u] = low[u] = ++timer;
        st.push(u);
        inSt[u] = 1;
        for (int v : adj[u]) {
            if (disc[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (inSt[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }
        if (low[u] == disc[u]) {
            vint comp;
            while (1) {
                int x = st.top();
                st.pop();
                inSt[x] = 0;
                id[x] = comps.size() + 1;
                comp.push_back(x);
                if (x == u) break;
            }
            comps.push_back(comp);
        }
    }
public:
    SCC(const vector<vint>& a, int n_) {
        n = n_;
        adj = a;
        disc.assign(n + 1, -1);
        low.assign(n + 1, 0);
        id.assign(n + 1, -1);
        inSt.assign(n + 1, 0);
        timer = 0;
        for (int i = 1; i <= n; i++) if (disc[i] == -1) tarjan(i);
    }
    
    vector<vint> getDag() {
        int k = (int) comps.size();
        vector<vector<int>> dag(k + 1);
        for (int u = 1; u <= n; ++u) {
            int cu = id[u];
            if (cu <= 0) continue;
            for (int v : adj[u]) {
                int cv = id[v];
                if (cv <= 0) continue;
                if (cu != cv) dag[cu].push_back(cv);
            }
        }
        for (int i = 1; i <= k; ++i) {
            sort(all(dag[i]));
            dag[i].erase(unique(all(dag[i])), dag[i].end());
        }
        return dag;
    }

    int getId(int u) const {
        if (u < 1 || u > n) return -1;
        return id[u];
    }

    vector<vint> getComp() { return comps; }
    int componentsCount() { return comps.size(); }
    
};