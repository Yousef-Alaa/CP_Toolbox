struct multiSet {
    ll n;
    vector<ll> bit;
    void init(ll mx) {
        n = 1;
        while (n < mx + 2)
            n <<= 1;
        bit.assign(n + 1, 0);
    }
    void add(ll i, ll val){
        assert(i >= 0 && i < n);
        for (++i; i <= n; i += (i & -i))
            bit[i - 1] += val;
    }
    ll get(ll i) const {
        if (i < 0)
            return 0;
        i = min(i, n - 1);
        ll res = 0;
        for (++i; i; i -= (i & -i))
            res += bit[i - 1];
        return res;
    }
    ll count(ll l, ll r) const {
        if (l > r)
            return 0;
        return get(r) - get(l - 1);
    }
    ll count(ll i) const {
        return count(i, i);
    }
    void insert(ll val, ll f = 1) {
        add(val, f);
    }
    void erase(ll val, ll f = 1) {
        add(val, -min(count(val), f));
    }
    void eraseAll(ll val) {
        add(val, -count(val));
    }
    size_t size() const {
        return get(n - 1);
    }
    ll order_of_key(ll x) const {
        return get(x - 1);
    }
    ll find_by_order(ll x) const {
        ll s = 0;
        for (ll sz = n >> 1; sz; sz >>= 1) {
            if (s + sz <= n && bit[s + sz - 1] < x) {
                x -= bit[s + sz - 1];
                s += sz;
            }
        }
        return s;
    }
    ll operator[](ll i) const {
        assert(i >= 0 && i < size());
        return find_by_order(i + 1);
    }
};