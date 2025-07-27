#include <bits/stdc++.h>
using namespace std;

// The main definitions to use ordered set, map
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

/*
    Compare Templates
    less<>
    less_equal<> // now it's a multiset
    greater<>
    greater_equal<> // now it's a multiset
*/

struct Compare {
    bool operator()(pair<int, int> &a, pair<int, int> &b) {
        if (a.first == b.first) return a.second > b.second;
        else return a.first < b.first;
    }
};


// *************************** priority_queue ********************************


void priorityQueue() {


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    pq.push({1, 5}); // O(Logn)
    pq.push({1, -4});
    pq.push({0, -8});
    pq.push({0, -2});
    pq.push({0, 0});
    pq.push({3, 8});
    pq.push({8, 5});
    pq.push({10, -1});
    pq.push({-1, 5});

    while (!pq.empty()) {
        cout << pq.top().first << ' ' << pq.top().second << '\n';
        pq.pop();// O(Logn) 
    }
    
}

// *************************** Set *********************************

template<class T>
using ordered_set = tree <T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Function to erase an element from the ordered set
template<typename T>
void Erase(ordered_set<T> &s, T val) {
    int order = s.order_of_key(val);
    auto it = s.find_by_order(order);
    if (it != s.end()) {
        s.erase(it);
    }
}


void SET() {
    
    //? Set
    // Unique
    // Sorted
    set<int> s;
    s.insert(5); //* O(logn)
    s.insert(4);
    s.insert(2);
    s.insert(8);
    s.insert(5);
    s.insert(5);
    s.insert(0);
    s.insert(10);
    s.insert(18);

    s.erase(5); //* O(logn)
    for (auto &e : s) cout << e << ' ';
    cout << '\n';
    for (auto it = s.begin(); it != s.end(); it++) cout << *it << ' ';
    cout << '\n';
    
    cout << *s.begin() << '\n';
    cout << *s.rbegin() << '\n';
    cout << *next(s.begin(), 1) << '\n';
    cout << *next(s.begin(), 2) << '\n';
    cout << *prev(s.rbegin(), 1) << '\n';

    // Searching in a set
    if (s.find(12) != s.end()) //* O(logn)
        cout << "Element found" << endl;
    else cout << "Element Not found" << endl;
    
    if (s.count(12))
        cout << "Element found" << endl;
    else cout << "Element Not found" << endl;
    cout << s.size();

    vector<int> v = {5, 1, 2, 5, 3, 2, 4};

    // Make a set from vector (removes duplicates and sorts)
    set<int> setFromV(v.begin(), v.end()); // O( n*log(n) )
    

    //? Multiset
    // Not Unique
    // Sorted
    // multiset<int> ms = {41, 5, 8, 8, 5, -4, 2, 0};
    
    // for (auto &e : ms) cout << e << ' ';
    // cout << '\n';
    
    // ms.erase(5); // will erase all
    // ms.erase( ms.find(8) ); // will erase first one
    // for (auto &e : ms) cout << e << ' ';
    // cout << '\n';

    // if (ms.find(41) != ms.end()) // O(1)
    //     cout << "Element found" << endl;
    // else cout << "Element Not found" << endl;

    //? Unordered Set
    // Unique
    // Not Sorted
    // use hash table and Not Prefered to use in problems
    // unordered_set<int> us = {41, 5, 8, 8, 5, -4, 2, 0};
    // for (auto &e : us) cout << e << ' ';
    // cout << '\n';
    // if (us.find(41) != us.end()) // O(1)
    //     cout << "Element found" << endl;
    // else cout << "Element Not found" << endl;

    //? Ordered Set
    // Unique
    // Sorted
    // Add Index Functionality
    // ordered_set<int> os; //! os = {1, 2, 3} not supported

    // os.insert(1);
    // os.insert(3);
    // os.insert(2);
    // os.insert(1);
    // os.insert(3);
    // os.insert(5);
    // os.insert(8);
    // os.insert(-3);

    // os.erase(-3); //! not supported
    // Erase(os, -3);

    // for (auto &e : os) cout << e << ' ';
    // cout << '\n';

    // cout << os.order_of_key(8) << '\n';
    // cout << *os.find_by_order(5) << '\n';
}


// *************************** Map *********************************

template <typename Key, typename Value>
using ordered_map = tree<Key, Value, less<Key>, rb_tree_tag, tree_order_statistics_node_update>;

void MAP() {

    

    //? Map
    // Key is unique
    // Sort Based On Key
    // NOTE: You can't use a `struct` as a key. instead use `tuple`
    map<string, int> mp;

    // mp.insert({"jo", 11}); //* O(logn)
    // mp.insert({"alaa", 111});
    // mp.insert({"omar", 15});
    // mp.insert({"hossam", -10});
    // mp.insert({"jo", 118}); //! Not Work
    // mp.erase("hossam"); //* O(logn)
    // mp["jo"]++;//* Work

    // for (auto it : mp) cout << it.first << ' ' << it.second << '\n';
    // NOTE: if you use key not found like "ahmed" it will create it
    // TODO  instead use if (mp.find("ahmed") != mp.end()) OR if (mp.count("ahmed"))
    
    // if (mp.find("ahmed") != mp.end()) cout << "Ahmed Founded";
    // if (mp.count("ahmed")) cout << "Ahmed Founded";
    
    // auto it = mp.begin();
    // cout << it->first << ' ' << it->second << '\n';
    // it++;
    // cout << it->first << ' ' << it->second << '\n';
    // it++;
    // cout << it->first << ' ' << it->second << '\n';
    
    
    //? Multimap
    // Key can be repeated
    // Sort Based On Key and Value
    multimap<string, int> mmp;
    
    // mmp.insert({"jo", 11});
    // mmp.insert({"alaa", 111});
    // mmp.insert({"omar", 15});
    // mmp.insert({"hossam", -10});
    // mmp.insert({"jo", 118}); //* Now it Will Work
    // mmp.erase("hossam");
    // mmp["jo"]++;//! Not Supported
    
    // for (auto it : mmp) cout << it.first << ' ' << it.second << '\n';
    
    //? Unordered Map
    // Key is unique
    // No Sort
    unordered_map<string, int> um;
    um.insert({"jo", 11});
    um.insert({"omar", 15});
    um.insert({"alaa", 111});
    um.insert({"hossam", -10});
    um.insert({"jo", 118}); //! Will Not Work
    um.erase("hossam");
    um["jo"]++;

    struct pair_hash {
        size_t operator()(const pair<int, int> &p) const {
            return hash<long long>()(( 1LL * p.first << 32) | p.second);
        };
    };

    unordered_map<pair<int, int>, int, pair_hash> um_hashed;




    //? ordered Map
    // Unique
    // Sorted
    // Add Index Functionality
    ordered_map<string, int> om;
    om["ahmed"] = 200;
    om.insert({"jo", 11});
    om.insert({"omar", 15});
    om.insert({"alaa", 111});
    om.insert({"hossam", -10});
    om.insert({"jo", 118}); //! Will Not Work if map is unique
    om.erase("hossam");
    om["jo"]++; //! Will create new one if multimap

    cout << om.order_of_key("jo") << '\n';
    cout << om.find_by_order(0)->first << '\n';
    cout << om.find_by_order(0)->second << '\n';
    
    for (auto it : om) cout << it.first << ' ' << it.second << '\n';

}

// **************************** LIST ************************************

void LIST() {

    
    
    //? Doubly Linked List
    list<string> ls1;
    list<string> ls2(5, "Ahmed"); // (size, initValue)
    
    // Insert
    ls1.push_back("Sedky"); // O(1)
    ls1.push_front("Yousef"); // O(1)
    ls1.insert(next(ls1.begin(), 1), "Alaa"); // O(1)
    ls1.push_back("Nour");
    ls1.push_back("El Dien");
    
    cout << ls1.front() << '\n';
    cout << ls1.back() << '\n';
    cout << ls1.size() << '\n';
    cout << ls1.empty() << '\n';

    ls1.splice(ls1.end(), ls2); // Add after specific position O(1)
    
    
    // Delete
    // ls1.pop_back(); // O(1)
    // ls1.pop_front(); // O(1)
    // ls1.erase(next(ls1.begin(), 3)); // O(1)
    // ls1.erase(start, end); // Erase range O(n)
    // ls1.remove("Alaa"); // O(n)
    // ls1.remove_if([](string &s) {return s[0] == 'S';}); // O(n)
    // ls1.clear(); // Erase all elements

    
    
    for (auto it : ls1) cout << it << ' ';
    cout << '\n';
    for (auto it : ls2) cout << it << ' ';



    cout << "##############\n";
    
    //? Single Linked List
    // More memory efficient
    forward_list<string> fl;
    forward_list<string> fl2(3, "Shahin");
    
    fl.push_front("Ahmed"); // O(1)
    fl.insert_after(fl.begin(), "Sameh"); // O(1)
    fl.insert_after(fl.before_begin(), "Shehab"); // O(1)
    fl.insert_after(fl.before_begin(), "Adballah"); // O(1)

    // cout << fl.back() << '\n'; //! Not Available
    // cout << fl.size() << '\n'; //! Not Available

    fl.splice_after(fl.begin(), fl2); // O(1)

    // fl.pop_front(); // O(1)
    // fl.erase_after(fl.before_begin()); // O(1)
    // fl.erase_after(start, end); // Erase In Range O(n)
    // fl.remove("Sameh"); // O(n)
    // fl.remove_if([](string &s) {return s[0] == 'S';}); // O(n)
    // fl.clear();

    
    for (auto it : fl) cout << it << ' ';

}

// **************************** OTHERS ************************************

void Others() {
    
    tuple<int, double, string, bool> tup(42, 3.14, "hello", true);
    
    get<0>(tup) += 15;
    get<2>(tup) = "Hellooo";

    cout << get<0>(tup) << '\n';
    cout << get<1>(tup) << '\n';
    cout << get<2>(tup) << '\n';
    cout << get<3>(tup) << '\n';
    
    // extract to variables
    int a;
    double b;
    string s;
    bool c;
    
    tie(a, b, s, c) = tup;
    
    cout << a << '\n';
    cout << b << '\n';
    cout << s << '\n';
    cout << c << '\n';
    
    tuple<int, double, string, bool> tup2(170, 53.188, "HI", false);
    
    tie(a, b, ignore, c) = tup2;

    cout << a << '\n';
    cout << b << '\n';
    cout << s << '\n';
    cout << c << '\n';

}

// **************************** MAIN ************************************

int main() {

    #ifndef ONLINE_JUDGE
        // freopen('input.txt', 'r', stdin);
        freopen("output.txt", "w", stdout);
    #endif


    SET();
    MAP();
    // LIST();
    // Others();
    // priorityQueue();

    return 0;
}