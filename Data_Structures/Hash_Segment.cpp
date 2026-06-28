#include <bits/stdc++.h>

using namespace std;

#define ll long long
typedef pair<int, int> pint;

int inv1 = 0;
const int N = 1e6;
const int base1 = 31;
const int mod1 = 1e9 + 7;
vector<int> pow1, powPref;

ll powMod(ll x, ll y, ll mod) {
    ll res = 1;
    x %= mod;
    while (y > 0) {
        if (y & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        y >>= 1;
    }
    return res;
}

void init() {

    if (pow1.size() > 0) return;

    inv1 = powMod(base1, mod1 - 2, mod1);

    pow1.resize(N + 1);
    powPref.resize(N + 1);
    pow1[0] = powPref[0] = 1;
    for (int i = 1;i <= N;i++) {
        pow1[i] = (1LL * pow1[i - 1] * base1) % mod1;
        powPref[i] = (pow1[i] + powPref[i - 1]) % mod1;
    }
}


class HashSeg {
    #define Left (node*2+1)
    #define Right (node*2+2)
    #define mid (l+r>>1)
    
    private:
    
    int sz;
    string str;
    const char fv = '0'; // First Value
    const int iden = 0;
    const int skip_lazy = 0;
    vector<int> tree;
    
    
    int merge(int a, int b, int lenR) {
        return (1LL * a * pow1[lenR] + b) % mod1;
    }

    void build(int l, int r, int node) {

        if (l == r) {
            if (l < str.size()) tree[node] = str[l] - fv + 1;
            return;
        }

        build(l, mid, Left);
        build(mid + 1, r, Right);
        tree[node] = merge(tree[Left], tree[Right], r - mid);
        
    }
    
    void update(int l, int r, int node, int idx, int val) {

        if (l == r) {
            tree[node] = val;
            return;
        }

        if (idx <= mid) update(l, mid, Left, idx, val);
        else update(mid + 1, r, Right, idx, val);

        tree[node] = merge(tree[Left], tree[Right], r - mid);

    }

    // Returns {hash, length_of_segment}
    pint query(int l, int r, int node, int lq, int rq) {

        if (rq < l || lq > r) return {0, 0};
        if (l >= lq && r <= rq) return {tree[node], r - l + 1};

        pint p1 = query(l, mid, Left, lq, rq);
        pint p2 = query(mid + 1, r, Right, lq, rq);
        int H = merge(p1.first, p2.first, p2.second);
        int len = p1.second + p2.second;

        return {H, len};
    }
    
    public:
    
    HashSeg(const string & s) {

        sz = 1;
        str = s;
        init();
        while (sz < str.size()) sz *= 2;
        
        tree.resize(2*sz, iden);
        build(0, sz - 1, 0);
    }

    void update(int idx, char val) {
        update(0, sz - 1, 0, idx, val - fv + 1);
    }
    
    int query(int l, int r) {
        return query(0, sz - 1, 0, l, r).first;
    }
    
    
    #undef Left
    #undef Right
    #undef mid
};