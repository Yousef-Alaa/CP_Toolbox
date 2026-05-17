#include <bits/stdc++.h>

using namespace std;

// Supports min, max, gcd, lcm, OR, AND
class SparseTable {
private:
    int n;
    int maxLog;
    const int iden = INT_MAX;
    vector<int> Log;
    vector<vector<int>> st; // [position][size] Note: size stored as 2^i

    int merge(int a, int b) {
        return min(a, b);
    }

public:
    SparseTable(const vector<int>& arr) {

        n = arr.size();
        maxLog = __lg(n) + 1;
        
        Log.resize(n);
        st.assign(n, vector<int>(maxLog, iden));

        Log[1] = 0;
        // log(n) = log(n / 2) + 1
        for (int i = 2; i < n; i++) Log[i] = Log[i / 2] + 1;

        for (int i = 0; i < n; i++) st[i][0] = arr[i];

        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                int part1 = st[i][j - 1];
                int part2 = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = merge(part1, part2);
            }
        }
    }

    // O(1)
    int query(int L, int R) {
        int len = R - L + 1;
        int j = Log[len];
        int part1 = st[L][j];
        int part2 = st[R - (1 << j) + 1][j];
        return merge(part1, part2);
    }
    
    // O(log n)
    int query2(int L, int R) {

        int ans = iden;
        int len = R - L + 1;

        for (int i = maxLog;i >= 0;i--) {
            if (len & (1 << i)) {
                ans = merge(ans, st[L][i]);
                L += (1 << i);
            }
        }


        return ans;
    }
};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    vector<int> arr = {1, 3, 1, 8, 5, 6, 7, 2};
    SparseTable table(arr);

    cout << "[0, 2]: " << table.query(0, 2) << '\n';
    cout << "[1, 4]: " << table.query(1, 4) << '\n';
    cout << "[3, 7]: " << table.query(4, 7) << '\n';


}