#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()


int sqrtN;
class MoAlgorithm {
public:
    struct query {
        int l, r, q_idx, blk_idx;

        query(int L = 0, int R = 0, int qi = 0) {
            blk_idx = L / sqrtN;
            l = L, r = R, q_idx = qi;
        }

        bool operator < (const query& rhs) const {
            if (blk_idx != rhs.blk_idx) return blk_idx < rhs.blk_idx;
            return (blk_idx & 1) ? (r < rhs.r) : (r > rhs.r);
        }
    };

    MoAlgorithm(int n_, int m_, vector<int> &v) {
        n = n_;
        m = m_;
        arr = v;
        ans = 0;
        currL = 1;
        currR = 0;
        sqrtN = n / sqrt(m) + 1;
        freq.resize(n + 5);
        answers.resize(m);
        queries.reserve(m);
    }

private:
    int ans;
    int n, m, currL, currR;
    vector<int> freq;
    vector<int> arr;
    vector<int> answers;
    vector<query> queries;

    void add(int idx) {
        if (freq[arr[idx]] == 0) ans++;
        freq[arr[idx]]++;
    }
    
    void remove(int idx) {
        freq[arr[idx]]--;
        if (freq[arr[idx]] == 0) ans--;
    }

    void setRange(query& q) {
        while (currL > q.l) add(--currL);
        while (currR < q.r) add(++currR);
        while (currL < q.l) remove(currL++);
        while (currR > q.r) remove(currR--);
    }

public:
    void addQuery(int l, int r){
        queries.push_back(query(l, r, queries.size()));
    }

    void process() {
        sort(all(queries));
        for (auto& q : queries) {
            setRange(q);
            answers[q.q_idx] = ans;
        }
    }

    vector<int> getAnswers() {
        return answers;
    }
};


int main(){
    
    #ifndef ONLINE_JUDGE
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q, l, r;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0;i < n;i++) cin >> arr[i];
    
    vector<int> comp = arr;
    sort(all(comp));
    comp.erase(unique(all(comp)), comp.end());
    
    for (int i = 0;i < n;i++) arr[i] = lower_bound(all(comp), arr[i]) - comp.begin();
    
    MoAlgorithm mo(n, q, arr);
    
    for (int i = 0;i < q;i++) {
        cin >> l >> r;
        mo.addQuery(l - 1, r - 1);
    }
    
    mo.process();
    
    vector<int> ans = mo.getAnswers();
    
    for (int i = 0;i < q;i++) cout << ans[i] << '\n';

    return 0;
}