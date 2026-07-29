#include <bits/stdc++.h>

using namespace std;

class SparseTable2D {
private:

    using M1D = vector<int>;
    using M2D = vector<M1D>;
    using M3D = vector<M2D>;
    using M4D = vector<M3D>;

    int n, m;
    const int iden = INT_MAX;
    
    vector<int> Log;
    M4D st; // [row][col][row_pw][col_pw]
    
    int merge(int a, int b) {
        return min(a, b);
    }
    
    int merge(int a, int b, int c, int d) {
        return min({a, b, c, d});
    }

public:
    SparseTable2D(const vector<vector<int>> &arr) {

        n = arr.size();
        m = arr[0].size();
        int lg1 = __lg(n) + 1;
        int lg2 = __lg(m) + 1;
        
        Log.resize(max(n, m) + 1, 0);
        st.assign(n, M3D(m, M2D(lg1, M1D(lg2, iden))));

        for (int i = 2; i <= max(n, m); i++) Log[i] = Log[i / 2] + 1;

        for (int i = 0; i < n; i++) 
            for (int j = 0; j < m; j++) st[i][j][0][0] = arr[i][j];

        for (int pw1 = 0; pw1 < lg1; pw1++) {
            for (int pw2 = 0; pw2 < lg2; pw2++) {

                if (pw1 == 0 && pw2 == 0) continue;

                for (int i = 0; i + (1 << pw1) <= n; i++) {
                    for (int j = 0; j + (1 << pw2) <= m; j++) {
                        
                        if (pw1 == 0) {
                            // Combine two blocks vertically
                            st[i][j][0][pw2] = merge(
                                st[i][j][0][pw2 - 1],
                                st[i][j + (1 << (pw2 - 1))][0][pw2 - 1]
                            );
                        } else {
                            // Combine two blocks horizontally
                            st[i][j][pw1][pw2] = merge(
                                st[i][j][pw1 - 1][pw2],
                                st[i + (1 << (pw1 - 1))][j][pw1 - 1][pw2]
                            );
                        }
                    }
                }
            }
        }


    }

    int query(int x1, int y1, int x2, int y2) {
        
        int len1 = x2 - x1 + 1;
        int len2 = y2 - y1 + 1;

        int lg1 = Log[len1];
        int lg2 = Log[len2];
        
        int part1 = st[x1][y1][lg1][lg2];
        int part2 = st[x2 - (1 << lg1) + 1][y1][lg1][lg2];
        int part3 = st[x1][y2 - (1 << lg2) + 1][lg1][lg2];
        int part4 = st[x2 - (1 << lg1) + 1][y2 - (1 << lg2) + 1][lg1][lg2];
        
        return merge(part1, part2, part3, part4);
    }
    
};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    int N = 4, M = 4;
    vector<vector<int>> matrix1 = { 
        { 5, 8, 2, 4 },
        { 7, 2, 9, 1 },
        { 1, 4, 7, 3 },
        { 3, 5, 6, 8 }
    };

    SparseTable2D sp2d(matrix1);

    srand(time(0));
    cout << "Good " << rand() % 1000 << '\n';

    cout << sp2d.query(0, 0, 3, 3) << '\n';
    cout << sp2d.query(1, 1, 2, 2) << '\n';
    
    return 0;


}