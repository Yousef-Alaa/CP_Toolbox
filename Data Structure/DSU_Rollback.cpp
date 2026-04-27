#include<bits/stdc++.h>

using namespace std;

class DSU_Roll {
private:
    int sets;
    stack<int> checkpoints;
    vector<int> parent, rank, size;
    stack<tuple<int, int, int>> history;

public:
    DSU_Roll(int n) {
        sets = n;
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find_root(int x) {
        if (x == parent[x]) return x;
        return find_root(parent[x]);
    }

    bool same(int u, int v) {
        return find_root(u) == find_root(v);
    }

    int getSize(int u) {
        return size[find_root(u)];
    }

    int unite(int u, int v) {
        return unite_by_size(u, v);
    }

    void persist() {
        checkpoints.push(history.size());
    }
    
    int rollback() {

        if (checkpoints.empty()) return sets;
        
        int cp_size = checkpoints.top();
        checkpoints.pop();

        while (history.size() > cp_size) {
            
            auto [op_type, node, old_value] = history.top();
            history.pop();
            
            if (op_type == 0) {
                if (parent[node] != node) sets++;
                parent[node] = old_value;
            }
            else if (op_type == 1) rank[node] = old_value;
            else if (op_type == 2) size[node] = old_value;
        
        }
        return sets;
    }

private:
    int unite_by_rank(int u, int v) {
        int root_u = find_root(u);
        int root_v = find_root(v);
        if (root_u == root_v) return sets;
        
        sets--;
        if (rank[root_u] < rank[root_v]) {
            history.push({0, root_u, parent[root_u]});
            parent[root_u] = root_v;
        } else {
            history.push({0, root_v, parent[root_v]});
            parent[root_v] = root_u;
            if (rank[root_u] == rank[root_v]) {
                history.push({1, root_u, rank[root_u]});
                rank[root_u]++;
            }
        }
        return sets;
    }

    int unite_by_size(int u, int v) {
        int root_u = find_root(u);
        int root_v = find_root(v);
        if (root_u == root_v) return sets;
        
        sets--;
        if (size[root_u] < size[root_v]) {
            history.push({0, root_u, parent[root_u]});
            history.push({2, root_v, size[root_v]});
            parent[root_u] = root_v;
            size[root_v] += size[root_u];
        } else {
            history.push({0, root_v, parent[root_v]});
            history.push({2, root_u, size[root_u]});
            parent[root_v] = root_u;
            size[root_u] += size[root_v];
        }
        return sets;
    }

};