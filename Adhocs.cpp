#include <bits/stdc++.h>

using namespace std;


#define ll long long
#define bigInt __int128
#define ull unsigned long long

// Next Element Greater Than 
vector<int> NEG(vector<int>& vec) {

    stack<int> stk; 
    vector<int> ans(vec.size(), -1); 

    for (int i = vec.size() - 1;i >= 0;i--) {
        while (!stk.empty() && vec[i] > vec[stk.top()]) stk.pop(); // Next Greater
        // while (!stk.empty() && vec[i] < vec[stk.top()]) stk.pop(); // Next Smaller
        if (!stk.empty()) ans[i] = vec[stk.top()];
        stk.push(i);
    }

    return ans; 
} 

// Prev Element Greater Than 
vector<int> PEG(vector<int>& vec) {

    stack<int> stk; 
    vector<int> ans(vec.size(), -1); 

    for (int i = 0;i < vec.size();i++) {
        while (!stk.empty() && vec[i] > vec[stk.top()]) stk.pop(); // Prev Greater
        // while (!stk.empty() && vec[i] < vec[stk.top()]) stk.pop(); // Prev Smaller
        if (!stk.empty()) ans[i] = vec[stk.top()];
        stk.push(i);
    }

    return ans; 
} 


int main() {

    #ifndef ONLINE_JUDGE
        // freopen('input.txt', 'r', stdin);
        freopen("output.txt", "w", stdout);
    #endif

    //? Difference Array
    const int N = 10;
    vector<int> arr = {1, 5, 12, 7, 16, 2, 23, 40, 9, 17};
    vector<int> diff(N + 1, 0);

    // Add 10 from 0 -> 5
    diff[0] += 10;
    diff[6] -= 10;
    // Add 5  from 3 -> 5
    diff[3] += 5;
    diff[6] -= 5;
    // Add 8  from 8 -> 9
    diff[8] += 8;
    diff[10] -= 8;
    // Add 22 from 0 -> 2
    diff[0] += 22;
    diff[3] -= 22;

    // Pref sum on diff
    for (int i = 1;i < N;i++) diff[i] += diff[i - 1];
    // Add to original Array
    for (int i = 0;i < N;i++) cout << diff[i] + arr[i] << ' ';


    cout << "\n##########\n";
    
    
    
    //? 2D Prefix Sum (pref rows then pref cols)
    const int rows = 3, cols = 5;
    int matrix[rows][cols] = {
        {1, 7, 4, 6,   2},
        {11, 1, 9, 2,  31},
        {8, 3, 11, 13, 22}
    };

    vector<vector<int>> pref_2d(rows, vector<int>(cols, 0));

    // Pref on Rows
    for (int i = 0;i < rows;i++) {
        for (int k = 0;k < cols;k++) {
            pref_2d[i][k] = matrix[i][k];
            if (k > 0) pref_2d[i][k] += pref_2d[i][k - 1];
        }
    }
    
    // Pref on Cols
    for (int i = 1;i < rows;i++) {
        for (int k = 0;k < cols;k++) pref_2d[i][k] += pref_2d[i - 1][k];
    }

    cout << "##########\n";
    
    // Print
    for (int i = 0;i < rows;i++) {
        for (int k = 0;k < cols;k++) {
            cout << pref_2d[i][k] << ' ';
        }
        cout << '\n';
    }

    auto getInRange = [&](vector<vector<int>> &vec, int x1, int y1, int x2, int y2) {

        if (x1 == 0 && y1 == 0) return vec[x2][y2];

        if (x1 == 0) return vec[x2][y2] - vec[x2][y1 - 1];

        if (y1 == 0) return vec[x2][y2] - vec[x1 - 1][y2];

        return vec[x2][y2] - vec[x2][y1 - 1] - vec[x1 - 1][y2] + pref_2d[x1 - 1][y1 - 1];
    };

    cout << "-> " << getInRange(pref_2d, 1, 0, 2, 2) << '\n';
    
    cout << "##########\n";
    
    //? 2D Difference Array

    vector<vector<int>> diff_2d(rows, vector<int>(cols, 0));
    vector<vector<int>> opreratins = {
    //  val  r1 c1 r2 c2
        {2,  0, 0, 1, 1},   
        {-1, 1, 0, 2, 2} 
    };

    for (auto &q : opreratins) {

        int v = q[0];
        int r1 = q[1], c1 = q[2], r2 = q[3], c2 = q[4];

        diff_2d[r1][c1] += v; // top-left -> add
        if (c2 + 1 < cols) diff_2d[r1][c2 + 1] -= v; // top-right -> subtract
        if (r2 + 1 < rows) diff_2d[r2 + 1][c1] -= v; // bottom-left -> subtract
        if (r2 + 1 < rows && c2 + 1 < cols) diff_2d[r2 + 1][c2 + 1] += v; // bottim-right -> add
    }

    // Prefix Rows
    for (int i = 0; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            diff_2d[i][j] += diff_2d[i][j - 1];
        }
    }
    
    // Prefix Cols
    for (int j = 0; j < cols; j++) {
        for (int i = 1; i < rows; i++) {
            diff_2d[i][j] += diff_2d[i - 1][j];
        }
    }
    
    // Add to original Matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] + diff_2d[i][j] << ' ';
        }
        cout << '\n';
    }

    //? Deque-based Sliding Window
    vector<int> vec = {1, 5, 12, 7, 16, 2, 23, 40, 9, 17};
    int l = 0, r = 2; // window size = 3
    vector<int> ans(vec.size() - 2, -1);
    deque<int> window;

    // Initiat The Window
    for (int i = l;i <= r;i++) {

        while (!window.empty() && vec[window.back()] < vec[i]) window.pop_back();
        
        window.push_back(i);
    }

    l++;
    r++;
    ans[0] = vec[window.front()];

    int size = vec.size();
    while (r < size) {
        
        while (!window.empty() && vec[window.back()] < vec[r]) window.pop_back();
        
        if (window.front() < l) window.pop_front();
        
        if (!window.empty()) ans[l] = vec[window.front()];
        else ans[l] = vec[r];
        window.push_back(r);
        

        l++;
        r++;
    }

    for (auto &e : ans) cout << e << ' ';

    cout << "\n################\n";
    
    vector<int> ans2 = NEG(vec);
    vector<int> ans3 = PEG(vec);
    
    for (auto &e : ans2) cout << e << ' ';
    cout << "\n################\n";
    for (auto &e : ans3) cout << e << ' ';


    return 0;
}