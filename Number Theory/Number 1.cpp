#include <bits/stdc++.h>

using namespace std;

#define bigInt __int128

#define ll long long
#define ull unsigned long long
#define vll vector<ll>

/*

Max and Min Values
==================

| Data Type            | Minimum Value Macro | Maximum Value Macro |
| -------------------- | ------------------- | ------------------- |
| `char`               | `CHAR_MIN`          | `CHAR_MAX`          |
| `unsigned char`      | 0                   | `UCHAR_MAX`         |
| `short`              | `SHRT_MIN`          | `SHRT_MAX`          |
| `unsigned short`     | 0                   | `USHRT_MAX`         |
| `int`                | `INT_MIN`           | `INT_MAX`           |
| `unsigned int`       | 0                   | `UINT_MAX`          |
| `long`               | `LONG_MIN`          | `LONG_MAX`          |
| `unsigned long`      | 0                   | `ULONG_MAX`         |
| `long long`          | `LLONG_MIN`         | `LLONG_MAX`         |
| `unsigned long long` | 0                   | `ULLONG_MAX`        |

| Type          | Digits After Dot (approx.)         |
| ------------- | -----------------------------------|
| `float`       | ~6 digits                          |
| `double`      | ~15 digits                         |
| `long double` | ~18-21 digits (platform dependent) |

*/

bool isPerfSqr(ll num) {
    if (num < 0) return false;

    ll root = sqrt(num);
    return root * root == num;
}

ll countPerfSqrs(ll l, ll r) {
    if (l > r) return 0;

    ll lower = ceil(sqrt(l));
    ll upper = floor(sqrt(r));

    if (lower > upper) return 0;

    return upper - lower + 1;
}

// Check If Prime O(sqrt(N)) // Good for n < 1e6
bool isPrime(int n) {
    
    if(n == 2) return true;
    if(n < 2 || n % 2 == 0) return false;
    
    for(int i = 3; i*i <= n; i+=2)
        if(n % i == 0) return false;
    
    return true;
}

// Find Primes from 1 to n
// Max N is 10^7 – 10^8
// Time: O( n*loglog(N) )
// 1e8 -> 1s
// 1e7 -> 77ms
// 1e6 -> 31ms
void sieve(int n) {
    
    /*
    Note: You can use Bitset instead of vector<bool> (More Faster)
    
    const int N = 1e7 + 1;
    bitset<N> isPrime;
    isPrime.set(); // And continue
    
    */
    vector<int> primes;
    vector<bool> isPrime(n + 1, true);
    
    isPrime[0] = isPrime[1] = false;

    for (int i = 2;i*i <= n;i++) {
        if (isPrime[i]) {
            for (ll j = 1LL*i*i;j <= n;j+=i) isPrime[j] = false;
        }
    }
    
    // if you need array of primes
    for (int i = 2;i <= n;i++) {
        if (isPrime[i]) primes.push_back(i);
    }

}


// Max N is 10^7 – 10^8
// Time: O(N) because number not marked multiple times
vector<int> linearSieve(int n) {


    // Return any of theme
    vector<int> primes;
    vector<int> spf(n+1);
    vector<bool> isPrime(n+1, true);

    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i <= n; i++) {

        if (isPrime[i]) {
            spf[i] = i;
            primes.push_back(i);
        }

        for (int p : primes) {
            if (p > spf[i] || 1LL * p * i > n) break;
            spf[p * i] = p;
            isPrime[p * i] = false;
        }
    }

    return primes;  // Optional: return list of primes
}


// takes 0.5s for n = 1e9  O( N*loglog(N) )
pair<vector<bool>, vector<int>> bigSieve(const int N, const int Q = 17, const int L = 1 << 15) {
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


// Prime Factors for a single Number O(sqrt(N))
void primeFactors(int n) {

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
}


// Max N is 10^7
// Time: O( N*loglog(N) )
// Smallest Prime Factor for numbers from 1 to n
vector<int> SPF(int n) {
    
    vector<int> spf(n+1, 0);

    spf[1] = 1;

    for (int i = 2;i <= n;i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            for (ll k = 1LL*i*i;k <= n;k+=i) {
                if (spf[k] == 0) spf[k] = i;
            }
        }
    }


    return spf;
}


// Prime Factors for a single Number
// Time: O(logN) and O(N) for SPF() So total = O( n*log(N) )
void primeFactorsSPF(int n) {

    vector<int> spf = SPF(n);
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

}


// Find Divisors for single number O(sqrt(N))
vector<int> findDivisors(int n, bool srt = false) {
    
    vector<int> divs;

    for (int i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            if (i * i != n) divs.push_back(i), divs.push_back(n / i);
            else divs.push_back(i);
        }
    }

    if (srt) sort(divs.begin(), divs.end());

    return divs;

}

// Find Divisors from 0 to n (Anti sieve) O( n*log(N) )
void computeDivisors(int n) {

    vector<vector<int>> divs(n+1, vector<int>(1, 1));
    
    for (int i = 2;i <= n;i++) {
        for (int j = i;j <= n;j+=i) {
            divs[j].push_back(i);
        }
    }

    // Print
    for (int i = 0;i <= n;i++) {
        cout << i << " Divs: ";
        for (auto v : divs[i]) cout << v << ' ';
        cout << '\n';
    }
}

// Time: O(sqrt(N))
ll countDivisors(ll num) {
    
    ll total = 1;
    for (ll i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }

    if (num > 1) total *= 2;
    
    return total;
}

// Time: O(sqrt(N))
ll sumOfDivisors(ll num) {

    ll total = 1;

    for (ll i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            ll sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }

    if (num > 1) total *= (1 + num);
    
    return total;
}

/*
    gcd(0, n) = n
    gcd(1, n) = 1
    gcd(n, n) = n
    gcd(n, m*n) = n
    gcd(n, n + 1) = 1
    gcd(n, n + 2) = 2 (if n is even)
    gcd(n, n + 2^x) = 1 (if n is odd)
    gcd(ka, kb) = |k| ⋅ gcd(a, b)
    gcd(−a, b) = gcd(a, b) // ignores the sign
*/
ll gcd(ll a, ll b) {

    if (b > a) swap(a, b);

    if(b == 0) return a;
    return gcd(b, a % b);
}

/*
    lcm(0, n) = 0
    lcm(1, n) = n
    lcm(n, n) = n
*/
ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
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

void printInt128(__int128 n) {
    if (n == 0) {
        cout << '0';
        return;
    }

    if (n < 0) {
        cout << '-';
        n = -n;
    }

    string s;
    while (n > 0) {
        s += '0' + (n % 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    

    return 0;
}