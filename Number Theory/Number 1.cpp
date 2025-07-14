#include <bits/stdc++.h>

using namespace std;

#define bigInt __int128

#define ll long long
#define ull unsigned long long

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

// Check If Prime
bool isPrime(int n) {
    
    if(n == 2) return true;
    if(n < 2 || n % 2 == 0) return false;
    
    for(int i = 3; i*i <= n; i+=2)
        if(n % i == 0) return false;
    
    return true;
}

// Find Primes from 1 to n
// Max N is 10^7 – 10^8
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
            primes.push_back(i); // if you need array of primes
            for (int j = i*i;j <= n;j+=i) isPrime[j] = false;
        }
    }

}


// Find Divisors of n
void findDivisors(int n, bool srt = false) {
    
    vector<int> divs;

    for (int i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            if (i * i != n) divs.push_back(i), divs.push_back(n / i);
            else divs.push_back(i);
        }
    }

    if (srt) sort(divs.begin(), divs.end());

}

// Find Divisors from 0 to n (Anti sieve)
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

// Prime Factors for a single Number
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

// Smallest Prime Factor for numbers from 1 to n
vector<int>& SPF(int n) {
    
    static vector<int> spf(n+1);

    for (int i = 1;i <= n;i++) spf[i] = i;
    for (int i = 2;i <= n;i++) {
        if (spf[i] == i) {
            for (int k = i*i;k <= n;k+=i) {
                if (spf[k] == k) spf[k] = i;
            }
        }
    }

    return spf;
}

// Prime Factors for a single Number
void primeFactorsSPF(int n) {

    vector<int>& spf = SPF(n);
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

    // Print
    for (auto &e : factors ) cout << e.first << '^' << e.second << '\n';

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
int gcd(int a, int b) {

    if (b > a) swap(a, b);

    if(b == 0) return a;
    return gcd(b, a % b);
}

/*
    lcm(0, n) = 0
    lcm(1, n) = n
    lcm(n, n) = n
*/
long long lcm(int a, int b) {
    return 1LL * a * b / gcd(a, b);
}

ll C(int n, int k) { // max n is 20 (non-mod)
    ll res = 1; 
    for (int i = n - k + 1; i <= n; ++i) 
        res *= i; 
    for (int i = 2; i <= k; ++i) 
        res /= i; 
    return res; 
} 

ll P(int n, int k) { // max n is 20 (non-mod)
    ll res = 1; 
    for (int i = n - k + 1; i <= n; ++i) 
        res *= i; 
    return res; 
}


int main() {

    #ifndef ONLINE_JUDGE
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif



    // cout << C(66, 33) << '\n';
    cout << P(20, 10) << '\n';

    return 0;
}