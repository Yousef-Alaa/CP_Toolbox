#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long

#define isPowerOf2(n) (n && !(n & (n - 1)))
#define setBit(n, bit) n |= (1LL<<bit)
#define checkBit(n, bit) ((n >> bit) & 1LL)
#define clearBit(n, bit) n &= ~(1LL<<bit)
#define toggleBit(n, bit) n ^= (1LL<<bit)

#define clearLowest(n) n &= (n - 1)
#define clearTrailOnes(n) n &= (n + 1) // 00110111 -> 00110000
#define setLastCleared(n) n |= (n + 1) // 00110101 -> 00110111

#define findLowest(n) (n == 0 ? -1 : __builtin_ctzll(n))// Should be greater than zero
#define findHighest(n) (n == 0 ? -1 : 63 - __builtin_clzll(n)) // Should be greater than zero
#define checkParity(n) __builtin_parityll(n) // odd_parity ? 1 : 0
#define countBuiltIn(n)  __builtin_popcountll(n)
#define hammingDistance(a, b) __builtin_popcountll(a ^ b) // How many bits are different

int countInRange(ll n, int start, int end) {
    ll mask = ((1LL << (end+1)) - 1) ^ ((1LL << start) - 1);
    return countBuiltIn(n & mask);
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

int findLowest_Iterative(ll n) {

    int count = -1; // in case of 0 there's no set bits
    ll x = n & -n;
    while(x) {
        x >>= 1; // x /= 2;
        count++;
    }
    return count; 
}

int countSetBits(ll n) {
    int count = 0;
    while (n) {
        n = n & (n-1);
        count++;
    }
    return count;
}

void BitSetLib();

int main() {

    #ifndef ONLINE_JUDGE
        // freopen('input.txt', 'r', stdin);
        freopen("output.txt", "w", stdout);
    #endif

    ll num = 457;
    // 111001001
    // 876543210

    cout << "R -> " << countInRange(num, 3, 6) << '\n';


    // BitSetLib();


    //? Prefix
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

        if (bitCount > 0) setBit(OR, bit);
        if (bitCount == (r-l+1)) setBit(AND, bit);
        if (bitCount & 1) setBit(XOR, bit);

    }

    cout << "AND = " << AND << '\n';
    cout << "XOR = " << XOR << '\n';
    cout << "OR  = " << OR << '\n';


}


void BitSetLib() {
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
    
}