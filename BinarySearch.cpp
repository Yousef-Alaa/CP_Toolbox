#include <bits/stdc++.h>

using namespace std;

int main() {

    #ifndef ONLINE_JUDGE
        // freopen('input.txt', 'r', stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<int> v = {1, 5, 8, 17, 18, 36};
    int key = 18;
    int left, right, mid, ans = -1;
    left = 0;
    right = v.size() - 1;

    while (left <= right) {
        
        mid = left + (right-left) / 2;
        
        if (v[mid] == key) {
            ans = mid;
            break;
        }
        
        if (v[mid] < key) {
            
            left = mid + 1;
        }
        else right = mid - 1, ans = mid;
    }

    cout << '[' << ans << "] -> " << v[ans] << '\n';

    /* 
        upper_bound => nearest greater
        lower_bound => nearest greater or equal
        upper_bound - 1 => nearest smaller or equal
        lower_bound - 1 => nearest smaller
    */ 
    // cout << upper_bound(v.begin(), v.end(), 5) - v.begin() - 1;

}