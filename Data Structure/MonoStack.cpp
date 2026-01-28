#include <bits/stdc++.h>
using namespace std;

template<typename T>
class MonoStack {
private:
    stack<pair<T, T>> st;
public:
    void push(const T &x) {
        T mx = st.empty() ? x : max(x, st.top().second);
        st.emplace(x, mx);
    }

    void pop() {st.pop();}
    T top() { return st.top().first; }
    T getMax() { return st.top().second; }
    
    size_t size() { return st.size(); }
    bool empty() { return st.empty(); }
    void swap(MonoStack &x) {st.swap(x.st);}
};