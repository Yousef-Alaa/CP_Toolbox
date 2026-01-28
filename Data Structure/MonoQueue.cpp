#include <bits/stdc++.h>
using namespace std;

//* Deque Implementation
template<typename T>
class MonoQueue {
private:
    queue <T> q;
    deque <T> dq1;
    deque <T> dq2;
public:
    void push(const T &x) {
        
        q.push(x);
        
        while (!dq1.empty() && dq1.back() < x) dq1.pop_back();
        dq1.push_back(x);

        while (!dq2.empty() && dq2.back() > x) dq2.pop_back();
        dq2.push_back(x);
    }

    void pop() {
        if (q.front() == dq1.front()) dq1.pop_front();
        if (q.front() == dq2.front()) dq2.pop_front();
        q.pop();
    }

    T top() {
        return q.top();
    }

    bool empty() {
        return q.empty();
    }

    T getMax() {
        return (dq1.empty() ? -1e18 : dq1.front());
    }

    T getMin() {
        return (dq2.empty() ? 1e18 : dq2.front());
    }

    size_t size() {
        return q.size();
    }

    void clear() {
        while (!q.empty()) {
            pop();
        }
    }
};

//* Stack Implementation
template<typename T>
class MonoQ {
private:
    MonoStack<T> in, out;
public:
    void push(const T &x) {
        in.push(x);
    }

    void pop() {
        if (out.empty()) moveInToOut();
        out.pop();
    }

    T top() {
        if (out.empty()) moveInToOut();
        return out.top();
    }

    bool empty() {
        return in.empty() && out.empty();
    }

    size_t size() {
        return in.size() + out.size();
    }

    T getMax() {
        if (in.empty())  return out.getMax();
        if (out.empty()) return in.getMax();
        return max(in.getMax(), out.getMax());
    }

    void moveInToOut() {
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }
};

//* Sliding Window Implementation
//  Find Max/Min in Range (Fixed Range)
vector<int> MonoQueue() {

    vector<int> vec = {1, 5, 12, 7, 16, 2, 23, 40, 9, 17};

    int l = 0, r = 2; // window size = 3
    vector<int> ans(vec.size() - 2, -1);
    deque<int> window;

    // Initiat The Window
    for (int i = l;i <= r;i++) {
        while (!window.empty() && vec[window.back()] < vec[i]) window.pop_back();
        window.push_back(i);
    }

    l++;
    r++;
    ans[0] = vec[window.front()];

    int size = vec.size();

    while (r < size) {

        while (!window.empty() && vec[window.back()] < vec[r]) window.pop_back();
        
        if (window.front() < l) window.pop_front();
        
        window.push_back(r);
        
        ans[l] = vec[window.front()];

        l++;
        r++;
    }

    return ans;
}