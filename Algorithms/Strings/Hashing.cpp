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
vector<int> prefPow1, prefPow2;

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
    prefPow1.resize(N + 1);
    prefPow2.resize(N + 1);
    pow1[0] = pow2[0] = 1;
    prefPow1[0] = prefPow2[0] = 1;
    for (int i = 1;i <= N;i++) {
        pow1[i] = (1LL * pow1[i - 1] * base1) % mod1;
        pow2[i] = (1LL * pow2[i - 1] * base2) % mod2;
        prefPow1[i] = (1LL * pow1[i] + prefPow1[i - 1]) % mod1;
        prefPow2[i] = (1LL * pow2[i] + prefPow2[i - 1]) % mod2;
    }
}

// Double Hashing with Forward & Reverse Hash (O(1) Substring Palindrome Check)
struct Hash {
    int n;
    char b;
    vector<int> h1, h2;   // Forward hash
    vector<int> rh1, rh2; // Reverse hash

    Hash(const string &s, char base = 'a') {
        init();
        b = base;
        n = s.size();
        h1.resize(n);
        h2.resize(n);
        rh1.resize(n);
        rh2.resize(n);
        make(s);
    }

    void make(const string &s) {
        // Forward Hash
        h1[0] = s[0] - b + 1;
        h2[0] = s[0] - b + 1;
        for (int i = 1; i < n; i++) {
            int c = s[i] - b + 1;
            h1[i] = (1LL * h1[i - 1] * base1 + c) % mod1;
            h2[i] = (1LL * h2[i - 1] * base2 + c) % mod2;
        }

        // Reverse Hash
        rh1[n - 1] = s[n - 1] - b + 1;
        rh2[n - 1] = s[n - 1] - b + 1;
        for (int i = n - 2; i >= 0; i--) {
            int c = s[i] - b + 1;
            rh1[i] = (1LL * rh1[i + 1] * base1 + c) % mod1;
            rh2[i] = (1LL * rh2[i + 1] * base2 + c) % mod2;
        }
    }

    pair<int, int> get_hash() const {
        return {h1[n - 1], h2[n - 1]};
    }

    pair<int, int> get_hash_rev() const {
        return {rh1[0], rh2[0]};
    }

    // Returns hash pair for forward substring s[l...r]
    pair<int, int> range(int l, int r) const {
        if (l == 0) return {h1[r], h2[r]};

        int v1 = (h1[r] - 1LL * h1[l - 1] * pow1[r - l + 1]) % mod1;
        int v2 = (h2[r] - 1LL * h2[l - 1] * pow2[r - l + 1]) % mod2;

        if (v1 < 0) v1 += mod1;
        if (v2 < 0) v2 += mod2;

        return {v1, v2};
    }

    // Returns hash pair for reversed substring s[l...r]
    pair<int, int> range_rev(int l, int r) const {
        if (r == n - 1) return {rh1[l], rh2[l]};

        int v1 = (rh1[l] - 1LL * rh1[r + 1] * pow1[r - l + 1]) % mod1;
        int v2 = (rh2[l] - 1LL * rh2[r + 1] * pow2[r - l + 1]) % mod2;

        if (v1 < 0) v1 += mod1;
        if (v2 < 0) v2 += mod2;

        return {v1, v2};
    }

    bool is_palindrome(int l, int r) const {
        return range(l, r) == range_rev(l, r);
    }

    pair<int, int> concat(const Hash &other) const {
        pair<int, int> cur = get_hash();
        pair<int, int> oth = other.get_hash();
        int v1 = (1LL * cur.first * pow1[other.n] + oth.first) % mod1;
        int v2 = (1LL * cur.second * pow2[other.n] + oth.second) % mod2;
        return {v1, v2};
    }

    pair<int, int> concat(pair<int, int> hash2, int len2) const {
        pair<int, int> cur = get_hash();
        int v1 = (1LL * cur.first * pow1[len2] + hash2.first) % mod1;
        int v2 = (1LL * cur.second * pow2[len2] + hash2.second) % mod2;
        return {v1, v2};
    }
};

// ============================================================================
// Hashing Standalone Helper Utilities
// ============================================================================

// Longest Common Prefix (LCP) of suffixes starting at index i and j in O(log N)
int get_lcp(const Hash &h, int i, int j) {
    int low = 1, high = min(h.n - i, h.n - j), ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (h.range(i, i + mid - 1) == h.range(j, j + mid - 1)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

// LCP between substrings s1[l1..r1] and s2[l2..r2] in O(log N)
int lcp(const Hash &h1, int l1, int r1, const Hash &h2, int l2, int r2) {
    int len1 = max(0, r1 - l1 + 1), len2 = max(0, r2 - l2 + 1);
    if (len1 == 0 || len2 == 0) return 0;
    int low = 1, high = min(len1, len2), ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (h1.range(l1, l1 + mid - 1) == h2.range(l2, l2 + mid - 1)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

// LCP between suffix s1[i...] and suffix s2[j...] (defaults to full strings)
int lcp(const Hash &h1, const Hash &h2, int i = 0, int j = 0) {
    if (i >= h1.n || j >= h2.n) return 0;
    return lcp(h1, i, h1.n - 1, h2, j, h2.n - 1);
}

// Lexicographical Comparison of substring s[l1..r1] vs s[l2..r2] in O(log N)
// Returns -1 if s[l1..r1] < s[l2..r2], 0 if equal, +1 if s[l1..r1] > s[l2..r2]
int compare_substrings(const string &s, const Hash &h, int l1, int r1, int l2, int r2) {
    int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
    int common = get_lcp(h, l1, l2);
    if (common >= min(len1, len2)) {
        if (len1 == len2) return 0;
        return (len1 < len2 ? -1 : 1);
    }
    return (s[l1 + common] < s[l2 + common] ? -1 : 1);
}

// Lexicographical Comparison between substring s1[l1..r1] vs s2[l2..r2] in O(log N)
int compare(const string &s1, const Hash &h1, int l1, int r1, const string &s2, const Hash &h2, int l2, int r2) {
    int len1 = max(0, r1 - l1 + 1), len2 = max(0, r2 - l2 + 1);
    int common = lcp(h1, l1, r1, h2, l2, r2);
    if (common >= min(len1, len2)) {
        if (len1 == len2) return 0;
        return (len1 < len2 ? -1 : 1);
    }
    return (s1[l1 + common] < s2[l2 + common] ? -1 : 1);
}

// Lexicographical Comparison between 2 entire strings s1 and s2 in O(log N)
int compare(const string &s1, const Hash &h1, const string &s2, const Hash &h2) {
    return compare(s1, h1, 0, (int)s1.size() - 1, s2, h2, 0, (int)s2.size() - 1);
}

// Longest Palindromic Substring centered at index (odd or even length) in O(log N)
int get_max_palindrome(const Hash &h, int center, bool is_even = false) {
    int low = 0, high = (is_even ? min(center + 1, h.n - 1 - center) : min(center, h.n - 1 - center));
    int max_radius = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int l = (is_even ? center - mid + 1 : center - mid);
        int r = center + mid;
        if (l >= 0 && r < h.n && h.is_palindrome(l, r)) {
            max_radius = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return (is_even ? 2 * max_radius : 2 * max_radius + 1);
}

// Sliding Window Hashing using Deque
class Hash_dq {
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
    Hash_dq() {
        init();
    }

    Hash_dq(const string &s) : Hash_dq() {
        for (char c : s) push_back(c);
    }

    pair<int, int> get_val() { return {H1, H2}; }

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
        H1 = (1LL * (H1 - x + mod1) * inv1) % mod1;
        H2 = (1LL * (H2 - x + mod2) * inv2) % mod2;
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
        dq.clear();
    }

};


int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../../input.txt", "r", stdin);
        freopen("../../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    string str1 = "racecar";
    Hash h(str1);

    cout << str1 << " is palindrome (0..6)? " << (h.is_palindrome(0, 6) ? "Yes" : "No") << '\n';
    cout << str1 << " substring (1..5 'aceca') is palindrome? " << (h.is_palindrome(1, 5) ? "Yes" : "No") << '\n';
    cout << str1 << " substring (0..3 'race') is palindrome? " << (h.is_palindrome(0, 3) ? "Yes" : "No") << '\n';

    string s1 = "abcdef";
    string s2 = "abcxyz";
    Hash h1(s1), h2(s2);
    cout << "LCP of " << s1 << " and " << s2 << ": " << lcp(h1, h2) << '\n';
    cout << "Compare " << s1 << " and " << s2 << ": " << compare(s1, h1, s2, h2) << '\n';

    return 0;
}