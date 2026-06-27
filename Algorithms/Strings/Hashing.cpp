#include <bits/stdc++.h>

using namespace std;

#define ll long long

/*
Useful Bases
============
31, 37, 131, 137
*/

const int N = 1e6 + 1;
const int base1 = 131;
const int base2 = 137;
const int mod1 = 1e9 + 7;
const int mod2 = 2e9 + 11;
int inv1 = 0, inv2 = 0;
vector<int> pow1, pow2;

ll powMod(ll x, ll y, ll mod) {
    ll res = 1;
    x %= mod;
    while (y > 0) {
        if (y & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        y >>= 1;
    }
    return res;
}

void init() {

    if (pow1.size() > 0) return;

    inv1 = powMod(base1, mod1 - 2, mod1);
    inv2 = powMod(base2, mod2 - 2, mod2);

    pow1.resize(N + 1);
    pow2.resize(N + 1);
    pow1[0] = pow2[0] = 1;
    for (int i = 1;i <= N;i++) {
        pow1[i] = (1LL * pow1[i - 1] * base1) % mod1;
        pow2[i] = (1LL * pow2[i - 1] * base2) % mod2;
    }
}

vector<pint> pref(N, 0);
auto sub_hash = [&](int l, int r) -> pint {
    if (l < 1) return pref[r];
    int h1 = (pref[r].first - 1LL * pref[l - 1].first * pow1[r - l + 1]) % mod1;
    int h2 = (pref[r].second - 1LL * pref[l - 1].second * pow2[r - l + 1]) % mod2;
    if (h1 < 0) h1 += mod1;
    if (h2 < 0) h2 += mod2;
    return {h1, h2};
};

class Hash {
private:
    deque<int> dq;
    int H1 = 0, H2 = 0;

    int get_char(char c) {
        if (c == ' ') return 1;
        if (c >= 'a' && c <= 'z') return (c - 'a') + 2;
        if (c >= 'A' && c <= 'Z') return (c - 'A') + 28;
        return 0; 
    }

public:
    Hash() {
        init();
    }

    Hash(string &s) : Hash() {
        for (char &c : s) push_back(c);
    }

    pair<int, int> get_val() {return {H1, H2};}

    void push_back(char c) {
        // H * base + x
        int x = get_char(c);
        H1 = (1LL * H1 * base1 + x) % mod1;
        H2 = (1LL * H2 * base2 + x) % mod2;
        dq.push_back(x);
    }

    void pop_back() {
        // (H - x) / base
        int x = dq.back();
        H1 = ((H1 - x + mod1) * inv1 * 1LL) % mod1;
        H2 = ((H2 - x + mod2) * inv2 * 1LL) % mod2;
        dq.pop_back();
    }
    void push_front(char c) {
        // H + x * pow(len)
        int x = get_char(c);
        H1 = (H1 + 1LL * x * pow1[dq.size()]) % mod1;
        H2 = (H2 + 1LL * x * pow2[dq.size()]) % mod2;
        dq.push_front(x);
        
    }
    void pop_front() {
        // H - x * pow(len - 1)
        int x = dq.front();
        H1 = (H1 - 1LL * x * pow1[dq.size() - 1]) % mod1;
        H2 = (H2 - 1LL * x * pow2[dq.size() - 1]) % mod2;
        if (H1 < 0) H1 += mod1;
        if (H2 < 0) H2 += mod2;
        dq.pop_front();
    }

    void reset() {
        H1 = H2 = 0;
    }

};


int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    string str1 = "yousef";
    string str2 = "youseff";
    Hash s1(str1), s2(str2);

    cout << (s1.get_val() == s2.get_val() ? "Same" : "Different") << '\n';
    

}