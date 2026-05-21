#include<bits/stdc++.h>

using namespace std;

class DSU {
private:
    int sz;
    int sets;
    vector<int> parent, rank, parity; // parity[x] = color[x] XOR color[parent[x]]
    
public:
    DSU(int n) {
        sz = sets = n;
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        parity.resize(n + 1, 0);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int find_root(int node) {
        if (node == parent[node]) return node;
        
        int root = find_root(parent[node]);
        parity[node] ^= parity[parent[node]];
        
        return parent[node] = root;
    }
    
    int getColor(int node) {
        find_root(node);  // This compresses path and updates parity
        return parity[node];
    }
    
    bool unite(int u, int v) {
        
        int ru = find_root(u);
        int rv = find_root(v);
        int cu = parity[u];
        int cv = parity[v];
        
        if (ru == rv) return (cu != cv);
        
        
        // We need cu XOR new_parity == cv XOR 1 (to make them different after edge)
        // So new_parity = cu XOR cv XOR 1
        int new_parity = cu ^ cv ^ 1;
        
        // Union by rank
        if (rank[ru] < rank[rv]) {
            parent[ru] = rv;
            parity[ru] = new_parity;
        } else if (rank[ru] > rank[rv]) {
            parent[rv] = ru;
            parity[rv] = new_parity;
        } else {
            parent[rv] = ru;
            parity[rv] = new_parity;
            rank[ru]++;
        }
        
        sets--;
        return true;
    }
    
    bool same(int u, int v) {
        return find_root(u) == find_root(v);
    }
    
};