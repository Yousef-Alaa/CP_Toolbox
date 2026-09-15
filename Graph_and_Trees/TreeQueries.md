```
                        TREE QUERY PROBLEM
                                │
   ┌────────────────────────────┴────────────────────────────────────┐
SUBTREE                                                             PATH
   │                                                                 │
Has Updates?                                                  Has Updates?
   ├── NO                                                            ├── YES
   │    ├── Offline/Complex ──► Sack's Algorithm                     |    ├── Invertible (Sum/Xor) ──► SegTree with -ve at out[node]
   │    └── Online/Simple   ──► Euler Tour + SegTree                 |    └── Other                ──► HLD + Segment Tree
   │                                                                 |
   └── YES ──► Euler Tour + SegTree                                  └── NO    
                                                                         |
                                                                     Value Type?
                                                                         ├── Standard (Min/Max/gcd) ──► Binary Lifting (LCA)
                                                                         ├── Distinct/Frequencies   ──► Mo's on Trees
                                                                         └── K-th Element on Path   ──► Persistent SegTree + LCA
```

### Quick Reference Summary

* **Subtree + No Updates:** **Sack's Algorithm** (simplest, minimal memory) or **Euler Tour + BIT/SegTree**
* **Subtree + Updates:** **Euler Tour + Segment Tree**
* **Path + Updates:** **HLD + Segment Tree**
* **Path + Standard Operations (Static):** **Binary Lifting (LCA)**
* **Path + Distinct/Frequencies (Offline):** **Mo's on Trees**