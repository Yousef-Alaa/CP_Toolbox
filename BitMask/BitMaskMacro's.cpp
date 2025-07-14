#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long


#define isPowerOf2(n) !(n & (n - 1)); // Should be greater than zero
#define setBit(n, bit) n |= (1LL<<bit);
#define checkBit(n, bit) (n >> bit) & 1LL;
#define clearBit(n, bit)  n &= ~(1LL<<bit);
#define toggleBit(ll n, int bit)  n ^= (1LL<<bit);

#define clearLowest(n) n &= (n - 1);
#define checkParity(n) __builtin_parityll(n); // odd_parity ? 1 : 0
#define findHighest(n) 63 - __builtin_clzll(n); // Should be greater than zero
#define findLowestBuiltIn(n) __builtin_ctzll(n);// Should be greater than zero
#define countBuiltIn(n)  __builtin_popcountll(n);
#define hammingDistance(a, b) __builtin_popcountll(a ^ b); // How many bits are different


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

int countSetBits(ll n) {
    int count = 0;
    while (n) {
        n = n & (n-1);
        count++;
    }
    return count;
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




}
