#include<bits/stdc++.h>

using namespace std;

class DSU {
private:
    int sets; // Num of Components
    int maxSize; // max elements connected together
    vector<int> rank, parent, size;

public:
    DSU(int n) {
        sets = n;
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int find_root(int node) {
        if (node == parent[node]) return node;
        return parent[node] = find_root(parent[node]);
    }

    bool same(int u, int v) {
        return find_root(u) == find_root(v);
    }
    
    int getSize(int u) {
        return size[find_root(u)];
    }

    int unite(int u, int v) {
        return unionByRank(u, v);
    }

private:
    int unionByRank(int u, int v) {
        
        int root_u = find_root(u);
        int root_v = find_root(v);
        if (root_u == root_v) return sets;

        sets--;
        if (rank[root_u] < rank[root_v]) parent[root_u] = root_v;
        else if (rank[root_u] > rank[root_v]) parent[root_v] = root_u;
        else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }

        return sets;
    }

    int unionBySize(int u, int v) {

        int root_u = find_root(u);
        int root_v = find_root(v);
        if (root_u == root_v) return sets;

        if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
            size[root_v] += size[root_u];
        } else {
            parent[root_v] = root_u;
            size[root_u] += size[root_v];
        }
        
        sets--;
        maxSize = max({maxSize, size[root_u], size[root_u]});
        return sets;
    }

};

int main() {

    DSU ds(7);
    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.unite(4, 5);
    ds.unite(6, 7);
    ds.unite(5, 6);
}