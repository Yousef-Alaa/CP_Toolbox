#include <bits/stdc++.h>

using namespace std;

#define ll long long

class Trie {
private:
    struct Node {
        int end = 0;
        int freq = 0;
        Node* child[26] = {nullptr};
    };

    Node* root;

    void erase(const string& s, int idx, Node* curr) {
        
        if (idx == s.size()) {
            curr->end--;
            return;
        }
        
        int i = s[idx] - 'a';
        if (curr->child[i]) {
            erase(s, idx + 1, curr->child[i]);
            curr->child[i]->freq--;
            if (curr->child[i]->freq == 0) {
                delete curr->child[i];
                curr->child[i] = nullptr;
            }
        }
    }

public:
    Trie() : root(new Node()) {}

    void insert(const string& a) {
        
        Node* curr = root;
        
        for (char c : a) {
            int i = c - 'a';
            if (!curr->child[i]) curr->child[i] = new Node();
            curr = curr->child[i];
            curr->freq++;
        }

        curr->end++;
    }

    void erase(const string& s) {
        erase(s, 0, root);
    }
    
    int count(const string& s) {
        const Node* ptr = root;
        for (char c : s) {
            int i = c - 'a';
            if (!ptr->child[i]) return false;
            ptr = ptr->child[i];
        }
        return ptr->end;
    }

    int is_prefix(const string& s) {

        const Node* ptr = root;
        for (char c : s) {
            int i = c - 'a';
            if (!ptr->child[i]) return false;
            ptr = ptr->child[i];
        }

        return ptr->freq;
    }
    
};

class BinaryTrie {
public:
    struct Node {
        
        int freq;
        Node* child[2];
        
        Node() {
            freq = 0;
            child[0] = child[1] = nullptr;
        }
    };

    Node* root;
    static const int LOG = 30;

    BinaryTrie() : root(new Node()) {}

    void insert(int x) {
        Node* curr = root;
        for(int bit = LOG; bit >= 0; --bit) {
            int bit_val = get_bit(x, bit);
            if(!curr->child[bit_val]) curr->child[bit_val] = new Node();
            curr = curr->child[bit_val];
            curr->freq++;
        }
        
    }

    void erase(int x) {
        if (count(x)) erase(x, LOG, root);
    }

    int count(int x) {
        Node* curr = root;
        for(int bit = LOG; bit >= 0; --bit) {
            int bit_val = get_bit(x, bit);
            if(!curr->child[bit_val]) return 0;
            curr = curr->child[bit_val];
        }
        return curr->freq;
    }
    
private:
    void erase(int x, int bit, Node* curr) {
        if(bit < 0) return;
        int bit_val = get_bit(x, bit);
        if (curr->child[bit_val]) {
            erase(x, bit - 1, curr->child[bit_val]);
            if (--curr->child[bit_val]->freq == 0) {
                delete curr->child[bit_val];
                curr->child[bit_val] = nullptr;
            }
        }
    }

    inline int get_bit(int x, int bit) {
        return (x >> bit) & 1;
    }
};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    Trie tr;

    string names[] = {"Yousef", "Yousef", "Yousef", "You", "Yasser", "Yassin"};

    for (string s : names) tr.insert(s);

    cout << tr.count("Yousef") << '\n';
    tr.erase("Yousef");
    cout << tr.count("Yousef") << '\n';
    cout << tr.is_prefix("You") << '\n';
    cout << tr.is_prefix("Yass") << '\n';

    cout << "########\n";

    BinaryTrie bt;

    bt.insert(7);
    bt.insert(1);
    bt.insert(1);
    bt.insert(7);
    bt.insert(15);

    cout << bt.count(7) << '\n';
    bt.erase(7);
    cout << bt.count(7) << '\n';


}