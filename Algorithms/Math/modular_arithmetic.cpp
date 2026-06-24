#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long

int MOD = 1e9 + 7;
const int N = 1e7;

/*
    Binary exponentiation
    calc x^y
    Takes O(log y) instead of O(y)
*/
ll powMod(ll x, ll y, ll mod = MOD) {
    ll res = 1;
    x %= mod;
    while (y > 0) {
        if (y & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        y >>= 1;
    }
    return res;
}

// Recursive Version
ll powerMod(ll a , ll b, ll mod = MOD) {
    if (b == 0) return 1;
    ll res = powerMod(a, b>>1);
    res = ((res*res)%mod * (b&1 ? a : 1))%mod; 
    return res;
}


ll add(ll a, ll b, ll mod = MOD) { return ((a % mod) + (b % mod)) % mod; }
ll mul(ll a, ll b, ll mod = MOD) { return ((a % mod) * (b % mod)) % mod; }
ll sub(ll a, ll b, ll mod = MOD) { return (((a % mod) - (b % mod)) % mod + mod) % mod; }
ll divide(ll a, ll b, ll mod = MOD) { return mul(a, powMod(b, mod - 2, mod)); }


int inverse(int a, int mod = MOD) {
    return a <= 1 ? a : mod - (int)(mod / a) * inverse(mod % a) % mod;
}


// solve ax + by = gcd(a, b)
ll extended_gcd(ll a, ll b, ll& x, ll& y) {

    if (a < 0) {
        ll r = extended_gcd(-a, b, x, y);
        x *= -1;
        return r;
    }
    
    if (b < 0) {
        ll r = extended_gcd(a, -b, x, y);
        y *= -1;
        return r;
    }

    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll g = extended_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

/*
    Note:
    exactly two pairs satisfy |x| < |b/gcd| and |y| < |a/gcd|
    one of them already produced by extended_gcd()
*/
pair<int, int> generateSol(int x1, int y1, int a, int b, int g, int k) {
    int x2 = x1 + k*b/g;
    int y2 = y1 - k*a/g;
    return {x2, y2};
}


// Linear Diophantine Equation
// Solve ax + by = c if c % gcd(a, b) == 0 in otherwords (c divisble by gcd(a, b))
ll LDE(ll a, ll b, ll c, ll& x, ll& y, bool& found) {
    
    ll g = extended_gcd(a, b, x, y);
    found = c % g == 0;

    if (found) {
        x *= c / g;
        y *= c / g;
    }

    return g;
}

// Linear Modular Equation
// Solve ax ≡ b (mod m)
// Explain: ax-b = qm -> ax+qm = b Now it's a LDE !!
vector<ll> LME(ll a, ll b, ll m) {
    
    vector<ll> sols;
    
    ll x, y, g;
    g = extended_gcd(a, m, x, y);
    if (b % g != 0) return sols; // No Solution

    for (int i = 0;i < g;i++) { // Generate g Solutions
        sols.push_back((x + i * m / g) % m);
    }

    sort(sols.begin(), sols.end());
    return sols;
}

// Solve ax ≡ 1 (mod m) IFF a, m are coprimes
// Explain: ax-1 = qm -> ax+qm = 1 Now it's a LDE !!
ll modInverse(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd(a, m, x, y);
    if (g != 1) return -1; // No Solution
    return (x + m) % m;
}