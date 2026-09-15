#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()

const int N = 1e6;

vint freq(N + 1);
vector<vector<int>> adj;
vector<int> dep, S, E, FT, nodeFreq;

ll hilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    ll subSquareSize = 1LL << (2 * pow - 2);
    ll ordd = seg * subSquareSize;
    ll add = hilbertOrder(nx, ny, pow - 1, nrot);
    ordd += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ordd;
}

int calcHilbertPow(int max_n) {
    int pow = 0;
    while ((1 << pow) < max_n) pow++;
    return pow;
}

// ================================================
// NOTE:
// if the values ON_EDGE we put it in lowest node
// ================================================


class MoTree {
public:
    struct Query {
        
        ll ord;
        int l, r, lca, qi;

        Query(int L, int R, int idx, int LCA, int HPower, bool onEdge = false) {
            
            if (S[L] > S[R]) swap(L, R);
            
            if (LCA == L) l = S[L] + onEdge, r = S[R], lca = -1, qi = idx;
            else l = E[L], r = S[R], lca = LCA, qi = idx;
            
            ord = hilbertOrder(l, r, HPower, 0);
        }

        bool operator < (const Query& rhs) const {
            return ord < rhs.ord;
        }
    };

    MoTree(int N, int M, vector<int> &v, bool onEdge = false) {
        n = N;
        m = M;
        ans = 0;
        timer = 1;
        values = v;
        ON_EDGE = onEdge;
        LOG = __lg(N) + 1;
        helbertPow = calcHilbertPow(2 * N + 1);
        
        answers.resize(M);
        queries.reserve(M);
        FT.resize(2 * n + 5);
        anc.resize(n + 5, vector<int>(LOG));
        nodeFreq = S = E = dep = vector<int>(n + 5);

        preDfs(0); // root of tree
    }

    void addQuery(int u, int v) {
        queries.emplace_back(u, v, queries.size(), getLCA(u, v), helbertPow, ON_EDGE);
    }

    void process() {
        
        sort(queries.begin(), queries.end());
        currL = queries[0].l, currR = queries[0].l - 1;

        for (auto& q : queries) {
            setRange(q);
            // if lca is -1 then the two nodes are in the same subtree
            if (q.lca != -1 && !ON_EDGE) add(q.lca);
            answers[q.qi] = ans;
            if (q.lca != -1 && !ON_EDGE) remove(q.lca);
        }
    }

    vector<int> getAnswers() const {
        return answers;
    }

private:
    ll ans;
    bool ON_EDGE;
    int n, m, currL, currR, timer, LOG, helbertPow;
    vector<Query> queries;
    vector<int> answers, values;
    vector<vector<int>> anc;

    void preDfs(int u, int p = -1) {
        S[u] = timer;
        FT[timer++] = u;
        for (auto& v : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            anc[v][0] = u;
            for (int bit = 1; bit < LOG; bit++)
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
            preDfs(v, u);
        }
        E[u] = timer;
        FT[timer++] = u;
    }

    int kthAnc(int u, int k) {
        if (dep[u] < k) return -1;
        for (int bit = LOG - 1; bit >= 0; bit--) {
            if (k & (1 << bit)) u = anc[u][bit];
        }
        return u;
    }

    int getLCA(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        u = kthAnc(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int bit = LOG - 1; bit >= 0; bit--)
            if (anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        return anc[u][0];
    }

    void setRange(Query& q) {
        while (currL > q.l) operation(--currL);
        while (currR < q.r) operation(++currR);
        while (currL < q.l) operation(currL++);
        while (currR > q.r) operation(currR--);
    }

    void add(int u) {
        if (freq[values[u]] == 0) ans++;
        freq[values[u]]++;
    }
    
    void remove(int u) {
        freq[values[u]]--;
        if (freq[values[u]] == 0) ans--;
    }

    void operation(int idx) {
        int u = FT[idx];
        nodeFreq[u] ^= 1;
        if (nodeFreq[u] == 1) add(u);
        else remove(u);
    }
};


int main(){

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    

    

    return 0;
}