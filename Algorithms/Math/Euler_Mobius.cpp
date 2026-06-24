#include <bits/stdc++.h>

using namespace std;

#define bigInt __int128

#define ll long long
#define ull unsigned long long
#define vll vector<ll>

const int N = 1e7;


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
void compute_phi() {
    
    vector<int> phi(N + 1);

    for (int i = 0; i <= N; i++) phi[i] = i;

    for (int i = 2; i <= N; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= N; j += i) phi[j] -= phi[j] / i;
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

// From Shahin Template
int mobius_sh(int n) {
    
    int p = 0; 
    if (n % 2 == 0) { 
        n = n / 2; 
        p++; 
        if (n % 2 == 0) 
        return 0; 
    } 

    for (int i = 3; i * i <= n; i = i + 2) { 
        if (n % i == 0) { 
            n = n / i; 
            p++; 
            if (n % i == 0) 
                return 0; 
        } 
    } 
    
    return (p % 2 == 0) ? -1 : 1; 
}

// Compute from μ(1) to μ(n) in O(n*loglog(n))
vector<int> mob(N+1, -1);
void compute_mobius() {

    vector<bool> prime(N+1, true);

    mob[1] = 1;

    for (ll i = 2; i <= N; i++) {
        if (prime[i]) {
            mob[i] = 1;
            for (ll j = 2 * i; j <= N; j += i) {
                prime[j] = false;
                if (j % (i * i) == 0) mob[j] = 0;
                else mob[j] = -mob[j];
            }
        }
    }


}


int main() {

    #ifndef ONLINE_JUDGE
        freopen("../../input.txt", "r", stdin);
        freopen("../../output.txt", "w", stdout);
    #endif

    compute_mobius();


    return 0;
}