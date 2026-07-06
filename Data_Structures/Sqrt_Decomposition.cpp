#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()


class Sqrt_Decomp {
private:
    int n, len;
    vector<int> A;
    vector<ll> blocks;
    vector<vector<int>> table;

    void build(){
        for(int i = 0; i < n; i++) {
            table[i / len].push_back(A[i]);
            blocks[i / len] += A[i];
        }
    }

public:
    Sqrt_Decomp(int n_, vector<int>& vec){
        n = n_;
        len = sqrt(n) + 1;
        A = vec;
        table.resize(len);
        blocks.resize(len);
        build();
    }

    void update(int idx, int val){
        blocks[idx / len] -= A[idx];
        blocks[idx / len] += val;
        table[idx / len][idx % len] = A[idx] = val;
    }

    ll query(int l, int r){
        ll res = 0;
        while(l <= r) {
            if (l % len == 0 && l + len <= r) res += blocks[l / len], l += len; 
            else res += A[l++];
        }
        
        return res;
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

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0;i < n;i++) cin >> arr[i];

    Sqrt_Decomp sq(n, arr);

    int t, x, y;
    while (q--) {
        cin >> t >> x >> y;
        if (t == 1) sq.update(x - 1, y);
        else cout << sq.query(x - 1, y - 1) << '\n';
    }
    

    return 0;
}