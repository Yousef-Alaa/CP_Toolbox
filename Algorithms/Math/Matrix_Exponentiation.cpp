#include <bits/stdc++.h>

using namespace std;

#define ll long long

template <typename T> using Row = vector<T>;
template <typename T> using Matrix = vector<Row<T>>;

int MOD = 1e9 + 7;

template <typename T>
Matrix<T> mul(Matrix<T> &a, Matrix<T> &b) {
    
    int n = a.size();
    int m = a[0].size();
    int k = b[0].size();
    Matrix<T> res(n, Row<T>(k));
    
    for (int i = 0;i < n;i++) 
        for (int j = 0;j < k;j++) 
            for (int o = 0;o < m;o++) {
                // res[i][j] += 1LL * a[i][o] * b[o][j];
                ll x = (1LL * a[i][o] * b[o][j]) % MOD;
                res[i][j] = (res[i][j] + x) % MOD;
            } 

    return res;
}

template <typename T>
Matrix<T> Power(Matrix<T> a, ll b) {
    int n = a.size();
    Matrix<T> res(n, Row<T>(n));
    for (int i = 0;i < n;i++) res[i][i] = 1;

    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }

    return res;
    
}

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../../input.txt", "r", stdin);
        freopen("../../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll n;
    cin >> n;

    Matrix<ll> a = {{1, 0}};
    Matrix<ll> b = {
        {19, 7},
        {6, 20}
    };

    Matrix<ll> T = Power(b, n);
    Matrix<ll> ans = mul(a, T);

    cout << ans[0][0];

}