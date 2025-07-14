#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long

class BitVector {
private:
    size_t N, W;
    vector<uint64_t> data;
    static constexpr uint64_t ALL_ONES = ~uint64_t(0);

    void check_size_match(const BitVector &o) const {
        if (N != o.N) throw invalid_argument("Size mismatch");
    }
    void clear_unused_bits_in_last_word() {
        if (N % 64)
            data[W-1] &= (uint64_t(1) << (N % 64)) - 1;
    }
    // internal: set data[] from a bit-string MSB first
    void init_from_string(const string &s) {
        N = s.size();
        W = (N + 63) / 64;
        data.assign(W, 0);
        // parse: s[0] is MSB ⇒ bit index N-1
        for (size_t i = 0; i < N; ++i) {
            char c = s[i];
            if (c != '0' && c != '1')
                throw invalid_argument("Invalid character in bit-string");
            if (c == '1') {
                size_t bit = N - 1 - i;
                data[bit / 64] |= (uint64_t(1) << (bit % 64));
            }
        }
    }

public:
    // 1) default constructor: all zeros
    BitVector(size_t size)
      : N(size),
        W((size + 63) / 64),
        data(W, 0ULL)
    {}

    // 2) fill constructor: all bits = v
    BitVector(size_t size, bool v)
      : BitVector(size)
    {
        if (v) {
            fill(data.begin(), data.end(), ALL_ONES);
            clear_unused_bits_in_last_word();
        }
    }

    // 3) construct from bit-string (MSB first)
    BitVector(const string &bitstr) {
        init_from_string(bitstr);
    }

    // re-initialize or modify from bit-string
    void from_string(const string &bitstr) {
        init_from_string(bitstr);
    }

    // size
    size_t size() const { return N; }

    // element access
    bool operator[](size_t i) const {
        if (i >= N) throw out_of_range("Index out of range");
        return (data[i/64] >> (i%64)) & 1;
    }
    void set(size_t i) {
        if (i >= N) throw out_of_range("Index out of range");
        data[i/64] |=  (uint64_t(1) << (i%64));
    }
    void reset(size_t i) {
        if (i >= N) throw out_of_range("Index out of range");
        data[i/64] &= ~(uint64_t(1) << (i%64));
    }
    void flip(size_t i) {
        if (i >= N) throw out_of_range("Index out of range");
        data[i/64] ^=  (uint64_t(1) << (i%64));
    }

    // bulk
    void set()   { fill(data.begin(), data.end(), ALL_ONES);  clear_unused_bits_in_last_word(); }
    void reset() { fill(data.begin(), data.end(), 0ULL); }
    void flip()  { for(auto &w : data) w = ~w; clear_unused_bits_in_last_word(); }

    // queries
    size_t count() const {
        size_t tot = 0;
        for (auto w : data) tot += __builtin_popcountll(w);
        return tot;
    }
    bool any()  const { for(auto w:data) if (w) return true; return false; }
    bool none() const { return !any(); }

    // inc/dec
    void increment() {
        for (size_t wi = 0; wi < W; ++wi) {
            if (data[wi] != ALL_ONES) { data[wi] += 1; break; }
            data[wi] = 0;
        }
        clear_unused_bits_in_last_word();
    }
    void decrement() {
        for (size_t wi = 0; wi < W; ++wi) {
            if (data[wi] != 0) { data[wi] -= 1; break; }
            data[wi] = ALL_ONES;
        }
        clear_unused_bits_in_last_word();
    }

    // bitwise
    BitVector operator~() const {
        BitVector r(*this);
        r.flip();
        return r;
    }
    BitVector operator&(const BitVector &o) const {
        check_size_match(o);
        BitVector r(N);
        for (size_t i = 0; i < W; ++i) r.data[i] = data[i] & o.data[i];
        return r;
    }
    BitVector operator|(const BitVector &o) const {
        check_size_match(o);
        BitVector r(N);
        for (size_t i = 0; i < W; ++i) r.data[i] = data[i] | o.data[i];
        return r;
    }
    BitVector operator^(const BitVector &o) const {
        check_size_match(o);
        BitVector r(N);
        for (size_t i = 0; i < W; ++i) r.data[i] = data[i] ^ o.data[i];
        return r;
    }
    BitVector& operator&=(const BitVector &o) { return *this = *this & o; }
    BitVector& operator|=(const BitVector &o) { return *this = *this | o; }
    BitVector& operator^=(const BitVector &o) { return *this = *this ^ o; }

    // shifts
    BitVector& operator<<=(size_t sh) {
        if (sh >= N) { reset(); return *this; }
        size_t word_off = sh / 64, bit_off = sh % 64;
        if (word_off) {
            for (size_t i = W-1; i >= word_off; --i)
                data[i] = data[i - word_off];
            for (size_t i = 0; i < word_off; ++i) data[i] = 0;
        }
        if (bit_off) {
            for (size_t i = W-1; i > 0; --i)
                data[i] = (data[i] << bit_off) | (data[i-1] >> (64-bit_off));
            data[0] <<= bit_off;
        }
        clear_unused_bits_in_last_word();
        return *this;
    }
    BitVector& operator>>=(size_t sh) {
        if (sh >= N) { reset(); return *this; }
        size_t word_off = sh / 64, bit_off = sh % 64;
        if (word_off) {
            for (size_t i = 0; i + word_off < W; ++i)
                data[i] = data[i + word_off];
            for (size_t i = W-word_off; i < W; ++i) data[i] = 0;
        }
        if (bit_off) {
            for (size_t i = 0; i + 1 < W; ++i)
                data[i] = (data[i] >> bit_off) | (data[i+1] << (64-bit_off));
            data[W-1] >>= bit_off;
        }
        return *this;
    }
    BitVector operator<<(size_t sh) const { BitVector r(*this); return r <<= sh; }
    BitVector operator>>(size_t sh) const { BitVector r(*this); return r >>= sh; }

    // to_string (MSB first)
    string to_string() const {
        string s; s.reserve(N);
        for (size_t i = 0; i < N; ++i)
            s.push_back((*this)[N-1-i] ? '1' : '0');
        return s;
    }
};

int main() {
    // init from size
    BitVector bv1(8, true);        // 11111111
    cout << bv1.to_string() << "\n";

    // init from string
    BitVector bv2("101001");       // size=6
    cout << bv2.to_string() << "\n";  // prints "101001"

    // modify existing
    bv2.from_string("000111");
    cout << bv2.to_string() << "\n";  // prints "000111"

    // shifts
    auto left = bv2 << 2;  
    auto right = bv2 >> 1;
    cout << left.to_string()  << "\n";  // "011100"
    cout << right.to_string() << "\n";  // "000011"

    return 0;
}
