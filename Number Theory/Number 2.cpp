#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long

int MOD = 1e9 + 7;

/*
    Binary exponentiation
    calc a^b
    Takes O(log b) instead of O(b)
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


// Good for n > 1e6
// O(k * log³ n) where k is the number of bases used
bool mayBePrime(ll n) {
    
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    ll d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (ll a : bases) {
        if (a >= n) break;
        ll x = powMod(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool ok = false;
        for (int i = 0; i < r - 1; i++) {
            x = mul(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }

    return true;
}

int inverse(int a, int mod = MOD) {
    return a <= 1 ? a : mod - (int)(mod / a) * inverse(mod % a) % mod;
}

// find φ(n) in O(sqrt(n))
int phi(int n) {
    
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }

    if (n > 1) result -= result / n;
    
    return result;
}

// Compute from φ(1) to φ(n) in O(n*loglog(n))
void compute_phi(int n) {
    
    vector<int> phi(n + 1);

    for (int i = 0; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
        }
    }
}

// find μ(n) in O(sqrt(n))
int mobius(int n) {

    int mebVal = -1;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            if (n % (i*i) == 0) return 0;
            n /= i, mebVal = -mebVal;
        }
    }

    if (n) mebVal = -mebVal;

    return mebVal;
}

// Compute from μ(1) to μ(n) in O(n*loglog(n))
const int MAX = 1e6;
vector<int> mob(MAX+1, -1);
void compute_mobius() {

    vector<bool> prime(MAX+1, true);

    mob[1] = 1;

    for (ll i = 2; i <= MAX; i++) {
        if (prime[i]) {
            mob[i] = 1;
            for (ll j = 2 * i; j <= MAX; j += i) {
                prime[j] = false;
                if (j % (i * i) == 0) mob[j] = 0;
                else mob[j] = -mob[j];
            }
        }
    }


}


int main() {

    #ifndef ONLINE_JUDGE
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    compute_mobius();

    for (int i = 0;i <= 1e6;i++) {
        if (mobius(i) != mob[i]) cout << "Error in I = " << i << '\n';
    }

    cout << "Finished !!";

    return 0;
}