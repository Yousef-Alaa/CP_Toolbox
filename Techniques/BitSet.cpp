#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Dynamic Bitwise Set for Min/Max AND & OR queries.
 * 
 * TIME COMPLEXITY:
 *   - All add() calls combined : O(2^BITS * BITS) total amortized time.
 *   - maxAND(x), maxOR(x)       : O(BITS) per query.
 *   - minAND(x), minOR(x)       : O(BITS) per query.
 * 
 * SPACE COMPLEXITY:
 *   - O(2^BITS) memory (~256 KB for BITS = 20).
 */

template <int BITS = 20>
struct BitSet {
    
    vector<bool> vis;       // Tracks submasks for maxAND / maxOR
    vector<bool> super_vis; // Tracks supermasks for minAND / minOR
    
    static constexpr int MAX_V = 1 << BITS;
    static constexpr int MASK_LIMIT = MAX_V - 1;

    BitSet() : vis(MAX_V, false), super_vis(MAX_V, false) {}

    // Inserts mask into submask graph (for max operations)
    void add_sub(int mask) {
        if (vis[mask]) return;
        vis[mask] = true;
        for (int i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                add_sub(mask ^ (1 << i));
            }
        }
    }

    // Inserts mask into supermask graph (for min operations)
    void add_super(int mask) {
        if (super_vis[mask]) return;
        super_vis[mask] = true;
        for (int i = 0; i < BITS; ++i) {
            if (!((mask >> i) & 1)) {
                add_super(mask | (1 << i));
            }
        }
    }

    // Inserts mask into the set
    void add(int mask) {
        add_sub(mask);
        add_super(mask);
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

    // Returns min(x & a) for all a in S
    int minAND(int x) {
        int ans = 0;
        int req_zeros = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            if ((x >> i) & 1) {
                int cz = req_zeros | (1 << i); // candidate_zeros
                int target_mask = MASK_LIMIT ^ cz;
                // Checks if there exists an element 'a' in S where a <= target_mask
                if (super_vis[target_mask]) req_zeros = cz;
                else ans |= (1 << i);
            }
        }
        return ans;
    }

    // Returns min(x | a) for all a in S via Duality
    int minOR(int x) {
        int not_x = (~x) & MASK_LIMIT;
        int min_and = minAND(not_x);
        return x | min_and;
    }
};