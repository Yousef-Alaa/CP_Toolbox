#include <bits/stdc++.h>

using namespace std;

#define bigInt __int128

#define ll long long
#define ull unsigned long long
#define vll vector<ll>

const int N = 1e7;

// count how many p in n!
ll legendreFormula(ll n, ll p) {
    ll cnt = 0;
    while (n > 0) {
        n /= p;
        cnt += n;
    }
    return cnt;
}

// Check If Prime O(sqrt(N)) // Good for n < 1e6
bool isPrime(int n) {
    
    if(n == 2) return true;
    if(n < 2 || n % 2 == 0) return false;
    
    for(int i = 3; i*i <= n; i+=2)
        if(n % i == 0) return false;
    
    return true;
}

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

// Find Primes from 1 to N
// Time: O( n*loglog(N) )
void sieve() {
    

    vector<bool> isPrime(N + 1, true);
    
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2;i*i <= N;i++) {
        if (isPrime[i]) {
            for (ll j = 1LL*i*i;j <= N;j+=i) isPrime[j] = false;
            }
    }
    
    // if you need array of primes
    vector<int> primes;
    for (int i = 2;i <= N;i++) {
        if (isPrime[i]) primes.push_back(i);
    }

}

// Time: O(N) because number not marked multiple times
vector<int> linearSieve() {


    // Return any of theme
    vector<int> primes;
    vector<int> spf(N+1);
    vector<bool> isPrime(N+1, true);

    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i <= N; i++) {

        if (isPrime[i]) {
            spf[i] = i;
            primes.push_back(i);
        }

        for (int p : primes) {
            if (p > spf[i] || 1LL * p * i > N) break;
            spf[p * i] = p;
            isPrime[p * i] = false;
        }
    }

    return primes;  // Optional: return list of primes
}

// takes 0.5s for n = 1e9  O( N*loglog(N) )
pair<vector<bool>, vector<int>> bigSieve() {
    
    const int Q = 17;
    const int L = 1 << 15;
    static const int rs[] = {1, 7, 11, 13, 17, 19, 23, 29};
    struct P { 
        P(int p) : p(p) {}
        int p; int pos[8];
    };

    auto approx_prime_count = [] (const int N) -> int {
        return N > 60184 ? N / (log(N) - 1.1) : max(1., N / (log(N) - 1.11)) + 1;
    };

    const int v = sqrt(N), vv = sqrt(v);
    vector<bool> isp(v + 1, true);
    for (int i = 2; i <= vv; ++i) if (isp[i]) {
        for (int j = i * i; j <= v; j += i) isp[j] = false;
    }

    vector<bool> isPrime(N + 1, false);
    vector<int> primes;

    if (N >= 2) isPrime[2] = true, primes.push_back(2);
    if (N >= 3) isPrime[3] = true, primes.push_back(3);
    if (N >= 5) isPrime[5] = true, primes.push_back(5);

    const int rsize = approx_prime_count(N + 30);
    primes.reserve(rsize);

    vector<P> sprimes;
    size_t pbeg = 0;
    int prod = 1; 
    for (int p = 7; p <= v; ++p) {
        if (!isp[p]) continue;
        if (p <= Q) prod *= p, ++pbeg, primes.push_back(p), isPrime[p] = true;
        auto pp = P(p); 
        for (int t = 0; t < 8; ++t) {
            int j = (p <= Q) ? p : p * p;
            while (j % 30 != rs[t]) j += p << 1;
            pp.pos[t] = j / 30;
        }
        sprimes.push_back(pp);
    }

    vector<unsigned char> pre(prod, 0xFF);
    for (size_t pi = 0; pi < pbeg; ++pi) {
        auto pp = sprimes[pi]; const int p = pp.p;
        for (int t = 0; t < 8; ++t) {
            const unsigned char m = ~(1 << t);
            for (int i = pp.pos[t]; i < prod; i += p) pre[i] &= m;
        }
    }

    const int block_size = (L + prod - 1) / prod * prod;
    vector<unsigned char> block(block_size);
    unsigned char* pblock = block.data();
    const int M = (N + 29) / 30;

    for (int beg = 0; beg < M; beg += block_size, pblock -= block_size) {
        int end = min(M, beg + block_size);
        for (int i = beg; i < end; i += prod) {
            copy(pre.begin(), pre.end(), pblock + i);
        }
        if (beg == 0) pblock[0] &= 0xFE;

        for (size_t pi = pbeg; pi < sprimes.size(); ++pi) {
            auto& pp = sprimes[pi];
            const int p = pp.p;
            for (int t = 0; t < 8; ++t) {
                int i = pp.pos[t]; const unsigned char m = ~(1 << t);
                for (; i < end; i += p) pblock[i] &= m;
                pp.pos[t] = i;
            }
        }

        for (int i = beg; i < end; ++i) {
            for (int m = pblock[i]; m > 0; m &= m - 1) {
                int val = i * 30 + rs[__builtin_ctz(m)];
                if (val <= N && !isPrime[val]) {
                    isPrime[val] = true;
                    primes.push_back(val);
                }
            }
        }
    }

    return {isPrime, primes};
}

// Max: High ~ 1e12
// Max: High-Low ~ 1e7
// Time: O( (R-L)*loglog(R) + sqrt(R)*loglog(sqrt(R)) ) ~ O( (R-L)*loglog(R) )
pair<vector<bool>, vector<ll>> segmentedSieve(ll Low, ll High) {

    
    // Generate primes from 0 -> sqrt(R)
    
    ll limit = sqrt(High);
    vector<ll> primes;
    vector<bool> mark(limit + 1, false);
    for (ll i = 2; i <= limit; i++) {
        if (!mark[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= limit; j += i) mark[j] = true;
        }
    }

    vector<bool> isPrime(High - Low + 1, true);

    for (ll p : primes) {
        // ll start = ceil( 1.0*Low / p);
        ll start = max(p * p, (Low + p - 1) / p * p);
        for (ll j = start; j <= High; j += p) isPrime[j - Low] = false;
    }

    if (Low == 1) isPrime[0] = false;

    // Generate the primes (remove if you want isPrime only)
    vector<ll> segment_primes;
    for (ll i = Low; i <= High; ++i) {
        if (isPrime[i - Low]) {
            segment_primes.push_back(i);
        }
    }

    return {isPrime, segment_primes};
}

vector<ll> segmentedSieveSPF(ll Low, ll High) {
    // 1. Generate primes up to sqrt(High) using standard sieve
    ll limit = sqrt(High);
    vector<ll> primes;
    vector<bool> mark(limit + 1, false);
    for (ll i = 2; i <= limit; i++) {
        if (!mark[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= limit; j += i) mark[j] = true;
        }
    }

    // 2. Initialize spf[i] with the actual value (Low + i)
    vector<ll> spf(High - Low + 1);
    for (ll i = 0; i < spf.size(); ++i) {
        spf[i] = Low + i;
    }

    // 3. Update SPF for range [Low, High]
    for (ll p : primes) {
        ll start = max(p * p, (Low + p - 1) / p * p);
        for (ll j = start; j <= High; j += p) {
            // Only update if it hasn't been marked by a smaller prime factor
            if (spf[j - Low] == j) {
                spf[j - Low] = p;
            }
        }
    }

    // Edge case for 1
    if (Low == 1) spf[0] = 1;

    return spf;
}


// Prime Factors for a single Number O(sqrt(N))
vector<pair<int, int>> primeFactors(int n) {

    vector<pair<int, int>> factors;
    
    int count;
    for(int i = 2; i*i <= n;i++) {
        count = 0;
        while(n % i == 0) {
            count++;
            n /= i;
        }
        if (count > 0) factors.push_back({i, count});
    }

    if(n != 1) factors.push_back({n, 1});

    // Print
    for (auto &e : factors ) cout << e.first << '^' << e.second << '\n';

    return factors;
}


// Max N is 10^7
// Time: O( N*loglog(N) )
// Smallest Prime Factor for numbers from 1 to n
vector<int> spf(N+1, 0);
void SPF() {

    spf[1] = 1;

    for (int i = 2;i <= N;i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            for (ll k = 1LL*i*i;k <= N;k+=i) {
                if (spf[k] == 0) spf[k] = i;
            }
        }
    }

}


// Prime Factors for a single Number
// Time: O(logN)
vector<pair<int, int>> primeFactorsSPF(int n) {

    vector<pair<int, int>> factors;
    
    int prime;
    int count;
    
    while(n != 1) {
        count = 0;
        prime = spf[n];
        
        while(n % prime == 0){
            count++;
            n /= prime;
        }
        
        factors.push_back({prime, count});
    }

    // NOTE: Sorted by default

    // Print
    for (auto &e : factors ) cout << e.first << '^' << e.second << '\n';

    return factors;

}