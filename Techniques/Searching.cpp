#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long

int findFirst(vector<int> &arr, int key) {
    int left = 0, right = arr.size() - 1, mid, ans = -1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            ans = mid;
            right = mid - 1;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ans;
    
}

int findLast(vector<int> arr, int key) {
    int left = 0, right = arr.size() - 1, mid, ans = -1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            ans = mid;
            left = mid + 1;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ans;
    
}

// Example for binarySearch on double
double getSqrt(ll n) {
    
    double precision = 1e-10;
    double left = 1, right = n, mid;
    
    while (right - left > precision) {

        mid = left + (right - left) / 2;
        if (mid * mid > n) right = mid;
        else left = mid;

    }

    return mid;

}

// Ternary Search on Integer Domain (Finds x in [l, r] that maximizes f(x))
// Change f(m1) < f(m2) to f(m1) > f(m2) for minimization
ll ternarySearchInt(ll l, ll r, const function<ll(ll)> &f) {
    while (r - l >= 3) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) l = m1; // m2 is strictly better
        else r = m2;               // m1 is better or equal
    }
    ll best_x = l;
    for (ll i = l + 1; i <= r; i++) {
        if (f(i) > f(best_x)) best_x = i;
    }
    return best_x;
}

// Ternary Search on Real / Double Domain (Finds x in [l, r] that maximizes f(x))
// Run fixed 100 iterations for high numerical precision
double ternarySearchDouble(double l, double r, const function<double(double)> &f, int iterations = 100) {
    for (int i = 0; i < iterations; i++) {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;
        if (f(m1) < f(m2)) l = m1;
        else r = m2;
    }
    return (l + r) / 2.0;
}

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif
    
    /* 
        upper_bound => nearest greater
        lower_bound => nearest greater or equal
        upper_bound - 1 => nearest smaller or equal
        lower_bound - 1 => nearest smaller
    */ 
    
    // cout << upper_bound(v.begin(), v.end(), 5) - v.begin() - 1;

    vector<int> v = {1, 3, 5, 8, 8, 8, 8, 17, 18, 36};

    // cout << findFirst(v, 8) << '\n';
    // cout << findLast(v, 8) << '\n';
    cout << fixed << setprecision(10);
    cout << getSqrt(16363) << '\n';
    cout << sqrtl(16363) << '\n';


}