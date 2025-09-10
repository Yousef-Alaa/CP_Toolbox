#include <bits/stdc++.h>
using namespace std;

/*
| Function Type | Identity         |
| ------------- | ---------------- |
| min(a, b)     | +∞ (INT_MAX)     |
| max(a, b)     | -∞ (INT_MIN)     |
| a + b         | 0                |
| a * b         | 1                |
| gcd(a, b)     | 0                |
| lcm(a, b)     | 1                |
| a | b         | 0                |
| a & b         | ~0 (all bits 1)  |
| a ^ b         | 0                |
*/

class SegmentTree {
private:
    int n;
    int size;
    vector<int> tree;
    const int identity = INT_MAX;

    inline int combine(int a, int b) {
        return min(a, b);
    }

    static int next_pow2(int x) {
        int p = 1;
        while (p < x) p <<= 1;
        return p;
    }

public:
    SegmentTree(const vector<int>& arr) {

        n = arr.size();
        size = next_pow2(n);
        tree.assign(2 * size, identity);

        for (int i = 0;i < n;i++) tree[size + i] = arr[i];
        for (int i = size - 1; i >= 1; i--) {
            tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
        }

    }

    void update(int pos, int value) {
        
        if (pos < 0 || pos >= n) return;
        int idx = size + pos;
        tree[idx] = value;
        idx >>= 1;
        while (idx >= 1) {
            tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
            idx >>= 1;
        }
    }

    int query(int l, int r) {
        
        if (l < 0 || r < 0 || l >= n || r >= n || l > r) return identity;

        l += size;
        r += size;
        int resL = identity;
        int resR = identity;

        while (l <= r) {
            if (l & 1) {
                resL = combine(resL, tree[l++]);
            }
            if (!(r & 1)) {
                resR = combine(tree[r--], resR);
            }
            l >>= 1;
            r >>= 1;
        }
        return combine(resL, resR);
    }
};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    vector<int> a = {1, 3, 1, 8, 5, 6, 7, 2};
    SegmentTree st(a);

    cout << "[0..2] = " << st.query(0, 2) << '\n';
    cout << "[3..7] = " << st.query(3, 7) << '\n';

    st.update(2, 10); // arr[2] = 10
    cout << "after update [0..2] = " << st.query(0, 2) << '\n';

    return 0;
}
