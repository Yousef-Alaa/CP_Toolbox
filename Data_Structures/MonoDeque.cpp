#include <bits/stdc++.h>
#include "MonoStack.cpp"
using namespace std;
template<typename T>
class MonoDeque {
	
private:
    MonoStack<T> l, r, t;
    void rebalance() { // Note: only called if 'l' or 'r' is empty
        bool f = false;
        if (r.empty()) {f = true; l.swap(r);}
        int sz = r.size() / 2;
        while (sz--) {t.push(r.top()); r.pop();}
        while (!r.empty()) {l.push(r.top()); r.pop();}
        while (!t.empty()) {r.push(t.top()); t.pop();}
        if (f) l.swap(r);
    }

public:

	T getMax() {
		if (l.empty()) return r.getMax();
		if (r.empty()) return l.getMax();
		return max(l.getMax(), r.getMax());
	}

	void push_front(const T &x) {l.push(x);}
	void push_back(const T &x) {r.push(x);}
	void pop_front() {
        if (l.empty()) rebalance();
        l.pop();
    }
	
    void pop_back() {
        if (r.empty()) rebalance();
        r.pop();
    }
	

    T front() {
        if (l.empty()) rebalance();
        return l.top();
    
    }
	T back() {
        if (r.empty()) rebalance();
        return r.top();
    
    }
    
	bool empty() {return l.empty() && r.empty();}
	int size() {return l.size() + r.size();}

};