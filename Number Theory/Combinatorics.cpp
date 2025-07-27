#include <bits/stdc++.h>

using namespace std;

#define bigInt __int128

#define ll long long
#define ull unsigned long long
#define vll vector<ll>

int MOD = 1e9 + 7;

/*
    Stars & Bars
    ============
    if we need to disribute 8 balls on 4 boxes
    then stars = 8 and bars = 3
    answer = (stars+bars)C(stars) OR (stars+bars)C(bars)


    Pigeonhole Principle
    ====================
    if we need to disribute 5 balls on 3 boxes
    at least one box must contain more than one ball.
    
    then at least one box must contain ⌈ 5 / 3 ⌉ = 2 balls
*/



ll C(int n, int k) { // max n is 20 (non-mod)
    ll res = 1; 
    for (int i = n - k + 1; i <= n; ++i)  // n! / (n - k)!
        res *= i; 
    for (int i = 2; i <= k; ++i) // / k!
        res /= i; 
    return res; 
}

ll NCR(int n, int k) { // Avoid Overflow
    long double res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return (ll)(res + 0.01);
}

ll P(int n, int k) { // max n is 20 (non-mod)
    ll res = 1; 
    for (int i = n - k + 1; i <= n; ++i) 
        res *= i; 
    return res; 
}



//? nCr Using Pascal Triangle
//? Great for problems with n, r ≤ 1000

int N = 1e3 + 1;
vector<vll> cash(N, vll(N, -1));
ll nCr_rec(ll n, ll r) { // O(n*r)

    if (r > n || r < 0) return 0;
    if (n == r || r == 0) return 1;

    if (r > n - r) r = n - r;
    if (cash[n][r] != -1) return cash[n][r];

    cash[n][r] = nCr_rec(n - 1, r - 1) + nCr_rec(n - 1, r);
    cash[n][n - r] = cash[n][r];

    return cash[n][r];
}


vector<vll> memo(N, vll(N, -1));
ll nCr_iter(ll n, ll r) { // O(n*r)

    if (r > n || r < 0) return 0;
    if (n == r || r == 0) return 1;

    if (r > n - r) r = n - r;
    if (memo[n][r] != -1) return memo[n][r];

    vector<ll> dp(r + 1, 0);
    dp[0] = 1;
    for (ll i = 1; i <= n; ++i) {
        for (ll j = min(i, r); j > 0; --j) {
            dp[j] += dp[j - 1];
        }
    }

    memo[n][r] = memo[n][n - r] = dp[r];

    return dp[r];

}


//? NCR With Prime MOD

vector<ll> fact, inv, factInv;

void pre_process(ll n) {

    inv.resize(n + 1);
    fact.resize(n + 1);
    factInv.resize(n + 1);

    fact[0] = factInv[0] = 1;
    if (n >= 1) inv[1] = 1;

    // Compute Factorial
    for (ll i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    
    // Compute Inverse
    for (ll i = 2; i <= n; i++) inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    
    // Compute Inverse of Factorial (Option 1)
    for (ll i = 1; i <= n; i++) factInv[i] = factInv[i - 1] * inv[i] % MOD;

    // Compute Inverse of Factorial (Option 2)
    // factInv[n] = powMod(fact[n], MOD - 2, MOD);
    // for (int i = n; i >= 1; i--) { factInv[i - 1] = factInv[i] * i % MOD; }
}

ll nCr(ll n, ll r, ll mod = MOD) {
    if (r < 0 || r > n) return 0;
    return fact[n] * factInv[r] % mod * factInv[n - r] % mod;
}

ll nPr(ll n, ll r, ll mod = MOD) {
    if (r < 0 || r > n) return 0;
    return fact[n] * factInv[n - r] % mod;
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    srand(time(0));
    pre_process(1e6);

    int n = 60, r = rand() % 60;
    cout << n << "C" << r << '\n';
    cout << C(n, r) << '\n';
    cout << NCR(n, r) << '\n';
    cout << nCr_rec(n, r) << '\n';
    cout << nCr_iter(n, r) << '\n';
    cout << nCr(n, r) << '\n';
    cout << nPr(n, r) << '\n';
    // cout << P(20, 10) << '\n';

    return 0;
}