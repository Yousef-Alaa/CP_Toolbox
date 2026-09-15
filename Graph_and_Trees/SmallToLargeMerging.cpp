#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()

typedef vector<int> vint;

// ============================================================================
// Small-to-Large Merging (Subtree Data Structure Merging)
//
// Description:
//   Merges subtree data structures (e.g. std::set, std::map) from child to parent.
//   By always merging the smaller structure into the larger one (using std::swap),
//   each element is moved at most O(log N) times.
//
// Complexity:
//   Time:  O(N log^2 N) for std::set / std::map, or O(N log N) for arrays.
//   Space: O(N log N) total elements across active sets/maps.
// ============================================================================

// Set Variant: Counting distinct elements in u's subtree
struct SmallToLarge {
    int n;
    vector<int> color;
    vector<vector<int>> adj;
    vector<int> ans; // Stores number of distinct colors in u's subtree

    SmallToLarge(int n_, const vector<int>& c) : n(n_), color(c), adj(n_), ans(n_, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    set<int> dfs(int u, int p) {
        set<int> st{ color[u] };
        for (int v : adj[u]) {
            if (v == p) continue;
            set<int> child_st = dfs(v, u);
            // Small-to-Large merge
            if (child_st.size() > st.size()) swap(st, child_st);
            
            st.insert(all(child_st));
        }
        ans[u] = st.size();
        return st;
    }

    vector<int> solve(int root = 0) {
        dfs(root, -1);
        return ans;
    }
};

// Map Variant: Tracking color frequencies & maximum frequency in u's subtree
struct SmallToLargeMap {
    int n;
    vector<int> color;
    vector<vector<int>> adj;
    vector<int> max_freq; // Stores maximum color frequency in u's subtree

    SmallToLargeMap(int n_, const vector<int>& c) : n(n_), color(c), adj(n_), max_freq(n_, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    struct SubtreeData {
        map<int, int> freq;
        int max_f = 0;
    };

    SubtreeData dfs(int u, int p) {
        SubtreeData cur;
        cur.freq[color[u]] = 1;
        cur.max_f = 1;

        for (int v : adj[u]) {
            if (v == p) continue;
            SubtreeData child_data = dfs(v, u);
            if (child_data.freq.size() > cur.freq.size()) {
                swap(cur, child_data);
            }
            for (auto& [col, cnt] : child_data.freq) {
                cur.freq[col] += cnt;
                cur.max_f = max(cur.max_f, cur.freq[col]);
            }
        }
        max_freq[u] = cur.max_f;
        return cur;
    }

    vector<int> solve(int root = 0) {
        dfs(root, -1);
        return max_freq;
    }
};