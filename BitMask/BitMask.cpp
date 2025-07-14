#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long

string binary(ll n) {
    
    string ans;

    if (n == 0) return "0";

    while (n > 0) {
        ans.push_back(char('0' + (n&1))); // n%2
        n >>= 1; // n /= 2;
    }
    

    reverse(ans.begin(), ans.end());
    return ans;
}

bool checkParity(ll n) {
    /*
        Checks the Parity of a number.
        Returns true(1) if the number has odd parity(odd number of set bits)
        else it returns false(0) for even parity(even number of set bits).
    */
    return __builtin_parityll(n);

}

bool checkBit(ll n, int bit) {
    return (n >> bit) & 1LL;
}

ll setBit(ll n, int bit) {
    return n | (1LL<<bit);
}

ll clearBit(ll n, int bit) {
    return n & ~(1LL<<bit);
}

ll toggleBit(ll n, int bit) {
    return n ^ (1LL<<bit);
}

bool isPowerOf2(ll n) {
    if (n == 0) return false;
    return !(n & (n - 1));
}

// Find Lowest Set Bit
int findLowest(ll n) {

    int count = -1; // in case of 0 there's no set bits
    ll x = n & -n;

    while(x) {
        x >>= 1; //x /= 2;
        count++;
    }

    return count; 
}

int findLowestBuiltIn(ll n) {
    if (n == 0) return -1;
    return __builtin_ctzll(n);// count Trainling zeros
}

// Clear Lowest Set Bit
ll clearLowest(ll n) {
    return n & (n - 1);
}

int findHighest(int n) {
    if (n == 0) return -1;
    return 31 - __builtin_clz(n); // count leading zeros
}

int findHighest(ll n) {
    if (n == 0) return -1;
    return 63 - __builtin_clzll(n); // count leading zeros
}

int countBuiltIn(ll n) {
    return __builtin_popcountll(n);
}

int countSetBits(ll n) {
    int count = 0;
    while (n) {
        n = n & (n-1);
        count++;
    }
    return count;
}

// How many bits are different
int hammingDistance(ll a, ll b) {
    return __builtin_popcountll(a ^ b);
}


ll xorFrom0ToN(ll n) {
    if (n%4 == 0) return n;
    if (n%4 == 1) return 1;
    if (n%4 == 2) return n+1;
    return 0;
}

/*
    XOR Props
    ---------
    -> A ^ B = (A+B) % 2   (if A and B consists of only 1 Bit)
    -> A + B = A^B + 2*(A&B)
        Note: 2*(A&B) is the carry of the sum
                then A + B = A^B if carry = zero (in other form if A&B is zero)
*/



int main() {

    #ifndef ONLINE_JUDGE
        // freopen('input.txt', 'r', stdin);
        freopen("output.txt", "w", stdout);
    #endif





    // ?Bitset
    /*
    | Operation       | Description                           |
    | --------------- | ------------------------------------- |
    | `b.set(i)`      | Set bit `i` to 1                      |
    | `b.reset(i)`    | Set bit `i` to 0                      |
    | `b.flip(i)`     | Flip bit `i`                          |
    | `b.test(i)`     | Check if bit `i` is set               |
    | `b.count()`     | Returns number of bits set to 1       |
    | `b.any()`       | Returns `true` if any bit is 1        |
    | `b.none()`      | Returns `true` if all bits are 0      |
    | `b.all()`       | Returns `true` if all bits are 1      |
    | `b.to_string()` | Converts to a string of '0' and '1'   |
    | `b.to_ulong()`  | Converts to `unsigned long` (if fits) |
    | `b.to_ullong()` | Converts to `unsigned long long`      |
    
    Note: for bitset<N> Max Size of `N` is 1e6 -> 1e7
    */
    bitset<8>  a1(18);
    bitset<16> a2(50);
    bitset<16> a3;

    cin >> a3; // Input like `1001` not decimal
    cout << a3 << '\n';

    // Input Decimal
    int x;
    cin >> x;
    a3 = x;

    // Increment/Decrement or any other math operation
    a3 = a3.to_ullong() + 5;
    cout << a3 << '\n';




    // Other Way to Increment/Decrement
    const int S = 200; // can go up to a few thousand safely
    auto increment = [](bitset<S> &bs) {
        for (int i = 0; i < S; ++i) {
            if (!bs[i]) {
                bs[i] = 1;
                break;
            } else {
                bs[i] = 0;
            }
        }
    };

    auto decrement = [](bitset<S> &bs) {
        for (int i = 0; i < S; ++i) {
            if (bs[i]) {
                bs[i] = 0;
                break;
            } else {
                bs[i] = 1;
            }
        }
    };

    bitset<S> a4;

    cin >> a4;

    increment(a4);
    increment(a4);
    cout << a4 << '\n';
    decrement(a4);
    cout << a4 << '\n';








    // ?Prefix
    const int N = 5;
    int pref[N][32];
    unsigned int arr[N] = {1, 11, 5, 15, 7};
    /*
        0001
        1011
        0101
        1111
        0111
    */


    for (int i = 0;i < N;i++) {
        for (int bit = 0;bit < 32;bit++) {
            pref[i][bit] = checkBit(arr[i], bit);
            if (i > 0) pref[i][bit] += pref[i - 1][bit];
        }
    }

    int l = 2, r = 4, OR = 0, AND = 0, XOR = 0;

    for (int bit = 0;bit < 32;bit++) {

        int bitCount = pref[r][bit];
        if (l > 0) bitCount -= pref[l-1][bit];

        if (bitCount > 0) OR = setBit(OR, bit);
        if (bitCount == (r-l+1)) AND = setBit(AND, bit);
        if (bitCount & 1) XOR = setBit(XOR, bit);

    }

    cout << "AND = " << AND << '\n';
    cout << "XOR = " << XOR << '\n';
    cout << "OR  = " << OR << '\n';


}
