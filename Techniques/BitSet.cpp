#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Dynamic Bitwise Set for Max-AND and Max-OR queries using Submask Reachability.
 * 
 * TIME COMPLEXITY:
 *   - All add() calls combined : O(2^BITS * BITS) total amortized time.
 *   - maxAND(x)                : O(BITS) per query.
 *   - maxOR(x)                 : O(BITS) per query.
 * 
 * SPACE COMPLEXITY:
 *   - O(2^BITS) memory (~128 KB for BITS = 20).
 */

template <int BITS = 20>
struct BitSet {
    
    vector<bool> vis;
    static constexpr int MAX_V = 1 << BITS;
    static constexpr int MASK_LIMIT = MAX_V - 1;

    BitSet() : vis(MAX_V, false) {}

    // Inserts mask and marks all its submasks as reachable
    void add(int mask) {
        if (vis[mask]) return;
        vis[mask] = true;
        for (int i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                add(mask ^ (1 << i));
            }
        }
    }

    // Returns max(x & a) for all a in S
    int maxAND(int x) {
        int ans = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            if (((x >> i) & 1) && vis[ans | (1 << i)]) {
                ans |= (1 << i);
            }
        }
        return ans;
    }

    // Returns max(x | a) for all a in S via Duality
    int maxOR(int x) {
        int not_x = (~x) & MASK_LIMIT;
        int best_and = maxAND(not_x);
        return x | best_and;
    }
};