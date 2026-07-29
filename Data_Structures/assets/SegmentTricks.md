## First Element <= val in range
``` cpp
ll query(ll l, ll r, ll node, ll val, ll lx, ll rx) {
        
    propegate(l, r, node);
    if (r < lx || l > rx || tree[node] > val) return -1;
    if (l >= r) return l;

    ll first = query(l, mid, Left, val, lx, rx);
    if (first != -1) return first;
    return query(mid + 1, r, Right, val, lx, rx);
}
```

## Point Query After Apply all updates
``` cpp
ll find(ll l, ll r, ll node, ll ind) {
    propegate(l, r, node);
    if (l == r) return tree[node];
    
    if (ind <= mid) return find(l, mid, node * 2 + 1, ind);
    return find(mid + 1, r, node * 2 + 2, ind);
}
```