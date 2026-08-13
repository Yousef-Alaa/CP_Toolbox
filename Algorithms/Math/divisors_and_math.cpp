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

vector<int> get_divisors(int n) {
    auto factors = primeFactorsSPF(n);
    vector<int> divisors = {1};

    for (auto [p, count] : factors) {
        int sz = divisors.size();
        int p_pow = 1;
        for (int i = 0; i < count; i++) {
            p_pow *= p;
            for (int j = 0; j < sz; j++) {
                divisors.push_back(divisors[j] * p_pow);
            }
        }
    }

    sort(divisors.begin(), divisors.end());
    return divisors;
}

// Count Divisors for single number O(logN)
ll countDivisors(int n) {
    
    ll ans = 1;
    int prime, count;

    
    while(n != 1) {
        count = 0;
        prime = spf[n];
        
        while(n % prime == 0){
            count++;
            n /= prime;
        }
        
        ans *= (count + 1);
    }

    return ans;
}

// Find Divisors from 0 to n (Anti sieve) O( n*log(N) )
void computeDivisors() {

    vector<vector<int>> divs(N+1, vector<int>(1, 1));
    
    for (int i = 2;i <= N;i++) {
        for (int j = i;j <= N;j+=i) {
            divs[j].push_back(i);
        }
    }

    // Print
    // NOTE: Sorted by default
    for (int i = 0;i <= N;i++) {
        cout << i << " Divs: ";
        for (auto v : divs[i]) cout << v << ' ';
        cout << '\n';
    }
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
    gcd(x, y, z, k) = gcd(x - y, y, z, k)
*/
ll gcd(ll a, ll b) {

    a = abs(a);
    b = abs(b);

    if (b > a) swap(a, b);

    if(b == 0) return a;
    return gcd(b, a % b);
}

/*
    lcm(0, n) = 0
    lcm(1, n) = n
    lcm(n, n) = n
    lcm(n, n+1) = n*(n+1)
*/
ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}