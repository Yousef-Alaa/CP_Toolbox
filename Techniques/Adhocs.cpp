#include <bits/stdc++.h>

using namespace std;


#define ll long long
#define bigInt __int128
#define ull unsigned long long


// Next Element Greater/Smaller Than 
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

// Prev Element Greater/Smaller Than 
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

ll toInt(char c) { 
    string letters = "0123456789ABCDEF"; 
    return letters.find(c); 
} 

ll BasetoDecimal(string in, ll base) { 
    ll res = 0; 
    ll siz = in.size(); 
    for(int i = 0;i < siz;i++) res *= base, res += toInt(in[i]); 
    return res; 
} 

string DecimaltoBase(ll number, ll base) { 
    if (number == 0) 
        return "0"; 
    string res = ""; 
    for (; number; number /= base) 
        res = letters[number % base] + res; 
    return res; 
}


int main() {

    #ifndef ONLINE_JUDGE
        // freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<int> vec = {1, 5, 12, 7, 16, 2, 23, 40, 9, 17};
    vector<int> ans1 = PEG(vec);
    vector<int> ans2 = NEG(vec);
    
    for (auto &e : ans1) cout << e << ' ';
    cout << "\n################\n";
    for (auto &e : ans2) cout << e << ' ';


    return 0;
}