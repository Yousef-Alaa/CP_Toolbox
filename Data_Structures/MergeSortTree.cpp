#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()

class MergeTree {
private:
    int sz;
    vector<vector<int>> tree;

    void merge(vector<int> &v1, vector<int> &v2, vector<int> &v3) {
        
        int p1 = 0;
        int p2 = 0;

        while (p1 < v1.size() && p2 < v2.size()) {
            if (v1[p1] < v2[p2]) v3.push_back(v1[p1++]);
            else v3.push_back(v2[p2++]);
        }

        while (p1 < v1.size()) v3.push_back(v1[p1++]);   
        while (p2 < v2.size()) v3.push_back(v2[p2++]);   
        
    }

    void build(int node, int l, int r, vector<int> &arr) {
        
        if(l == r) {
            if (l < arr.size()) tree[node].push_back(arr[l]);
            return;
        }

        int mid = l+(r-l)/2;
        build(2*node+1, l, mid, arr);
        build(2*node+2, mid+1, r, arr);
        merge(tree[2*node+1], tree[2*node+2], tree[node]);
    }
    
    int query(int node, int l, int r, int lq, int rq, int k) {
        if( r < lq || l > rq ) return 0;
        
        if(lq <= l && r <= rq) {
            //Binary search over the current sorted vector to find elements smaller than K
            return lower_bound(all(tree[node]), k) - tree[node].begin();
        }
        int mid=l+(r-l)/2;
        return query(2*node+1, l, mid, lq, rq, k) + 
                query(2*node+2, mid+1, r, lq, rq, k);
    }

public:

    MergeTree(vector<int> &arr) {
        sz = 1;
        while (sz < arr.size()) sz *= 2;
        tree.resize(2*sz);
        build(0, 0, sz - 1, arr);
    }

    int query(int l, int r, int k) {
        return query(0, 0, sz - 1, l, r, k);
    }
};

// Support updates
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
class MergeTree2 {
private:
    int sz;
    vector<int> arr;
    vector<ordered_set<pair<int, int>>> tree; 

    void build(int node, int l, int r) {
        
        if (l == r) {
            if (l < arr.size()) tree[node].insert({arr[l], l});
            return;
        }

        int mid = l + (r - l) / 2;
        build(2 * node + 1, l, mid);
        build(2 * node + 2, mid + 1, r);

        for (auto &x : tree[2 * node + 1]) tree[node].insert(x);
        for (auto &x : tree[2 * node + 2]) tree[node].insert(x);
    }
    
    int query(int node, int l, int r, int lq, int rq, int k) {
        
        if (r < lq || l > rq) return 0;
        if (lq <= l && r <= rq) {
            // order_of_key returns count of elements strictly smaller than {k, -1}
            // Using -1 ensures we don't accidentally count matches on the boundary
            return tree[node].order_of_key({k, -1});
        }
        
        int mid = l + (r - l) / 2;
        return query(2 * node + 1, l, mid, lq, rq, k) + 
               query(2 * node + 2, mid + 1, r, lq, rq, k);
    }

    void update(int node, int l, int r, int idx, int val) {

        tree[node].erase({arr[idx], idx});
        tree[node].insert({val, idx});

        if (l == r) return;

        int mid = l + (r - l) / 2;
        if (idx <= mid) update(2 * node + 1, l, mid, idx, val);
        else update(2 * node + 2, mid + 1, r, idx, val);
        
    }

public:
    MergeTree2(const vector<int> &v) {
        
        sz = 1;
        while (sz < v.size()) sz *= 2;
        
        arr = v;
        tree.resize(2 * sz);
        build(0, 0, sz - 1);
    }

    int query(int l, int r, int k) {
        return query(0, 0, sz - 1, l, r, k);
    }

    void update(int idx, int val) {
        if (val == arr[idx]) return;
        update(0, 0, sz - 1, idx, val);
        arr[idx] = val;
    }
};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    vector<int> v = {1, 8, 10, 150, 70, 13, 5, 9, 6};

    MergeTree mt(v);
    MergeTree2 mt2(v);

    cout << mt.query(1, 6, 71) << '\n';
    cout << mt2.query(1, 6, 71) << '\n';
    cout << "##########\n";
    mt2.update(3, 50);
    cout << mt.query(1, 6, 71) << '\n';
    cout << mt2.query(1, 6, 71) << '\n';


}