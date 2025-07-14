#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long

int MOD = 1e9 + 7;



int inverse(int a) {
    return a <= 1 ? a : MOD - (int)(MOD / a) * inverse(MOD % a) % MOD;
}


/*
    Binary exponentiation
    calc a^b
    Takes O(log b) instead of (b)
*/
ll power(ll a, ll b) {
    ll result = 1;
    while (b) {
        if (b & 1) result *= a;
        a *= a;
        b /= 2;
    }
    return result;
}

// Similar to power() but return the answer % MOD
ll powMod(ll x, ll y) {
    ll res = 1;
    x %= MOD;
    while (y) {
        if (y & 1) res = (res * x) % MOD;
        x = (x * x) % MOD;
        y >>= 1;
    }
    return res;
}


inline ll add(ll a, ll b) { return ((a % MOD) + (b % MOD)) % MOD; }
inline ll mul(ll a, ll b) { return ((a % MOD) * (b % MOD)) % MOD; }
inline ll sub(ll a, ll b) { return (((a % MOD) - (b % MOD)) % MOD + MOD) % MOD; }
inline ll divide(ll a, ll b) { return mul(a, powmod(b, MOD - 2)); }


vector<ll> fact, inv, factInv;

void init(ll n, ll modVal) {

    MOD = modVal;
    inv.resize(n + 1);
    fact.resize(n + 1);
    factInv.resize(n + 1);

    fact[0] = factInv[0] = 1;
    if (n >= 1) inv[1] = 1;

    for (ll i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;

    for (ll i = 2; i <= n; i++) inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;

    for (ll i = 1; i <= n; i++) factInv[i] = factInv[i - 1] * inv[i] % MOD;
}

ll nCr(ll n, ll r) { // max `non-mod` result -> n = 32
    if (r < 0 || r > n) return 0;
    return fact[n] * factInv[r] % MOD * factInv[n - r] % MOD;
}

ll nPr(ll n, ll r) { // max `non-mod` result -> n = 20
    if (r < 0 || r > n) return 0;
    return fact[n] * factInv[n - r] % MOD;
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    init(33, MOD);


    cout << nCr(32, 16) << '\n';
    cout << nPr(21, 11) << '\n';

    // cout << 7219428434016265740ULL % MOD << '\n';

    return 0;
}