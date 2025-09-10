#include <bits/stdc++.h>

using namespace std;

// Supports min, max, gcd, OR, AND
class SparseTable {
private:
    int n;
    int maxLog;
    vector<vector<int>> st; // [position][size] Note: size stored as 2^i

    #define fn(x, y) min(x, y)
    #define findHigh(n) (63 - __builtin_clzll(n)) 

public:
    SparseTable(const vector<int>& arr) {

        n = arr.size();
        maxLog = findHigh(n) + 1;
        st.assign(n, vector<int>(maxLog));

        for (int i = 0; i < n; i++) st[i][0] = arr[i];

        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                int part1 = st[i][j - 1];
                int part2 = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = fn(part1, part2);
            }
        }
    }

    int query(int L, int R) {
        int len = R - L + 1;
        int j = findHigh(len);
        int part1 = st[L][j];
        int part2 = st[R - (1 << j) + 1][j];
        return fn(part1, part2);
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