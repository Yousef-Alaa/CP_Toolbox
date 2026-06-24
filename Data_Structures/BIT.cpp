#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct BIT {
    int n;
    vector<ll> bit;

    BIT(int sz) {
        n = sz;
        bit.assign(n + 1, 0);
    }
    
    BIT(const vector<int> &arr) {
        n = arr.size();
        bit.assign(n + 1, 0);
        for (int i = 0; i < n; i++) add(i, arr[i]);
    }

    void add(int i, ll val) {
        i++; // 1-based
        while (i <= n) {
            bit[i] += val;
            i += i & -i;
        }
    }

    ll query(int i) {
        i++;
        ll sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= i & -i; 
        }
        return sum;
    }

    ll range(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }

    int lower_bound(ll sum) {
        
        if (sum <= 0) return 0;
        
        int idx = 0;
        ll curr = 0;
        
        int pow = 1;
        while (pow * 2 <= n) pow *= 2;

        for (int i = pow; i > 0; i /= 2) {
            if (idx + i <= n && curr + bit[idx + i] < sum) {
                idx += i;
                curr += bit[idx];
            }
        }
        
        return (idx < n) ? idx : -1;
    }
};


int main() {

    #ifndef ONLINE_JUDGE
        // freopen("input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    vector<int> a = {1, 3, 1, 8, 5, 6, 7, 2};

    BIT tr(a);

    cout << tr.range(1, 3) << '\n';
    cout << tr.lower_bound(14) << '\n';
    tr.add(2, 10);
    cout << tr.range(1, 3) << '\n';
    cout << tr.lower_bound(14) << '\n';


}