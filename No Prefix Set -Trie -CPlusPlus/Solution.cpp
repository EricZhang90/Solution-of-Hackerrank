#include <iostream>
#include <map>

using namespace std;



class Trie {

public:
    Trie() {
        node = new TrieNode();
    }
    
    ~Trie() {
        clear(node);
        delete node;
    }
    
    // return true if find two string are same.(no need to continue to save the s)
    // otherwise save the s in Trie
    bool saveAndCheck(string s) {
        bool same = true;
        TrieNode* current = node;
        
        for (char c: s) {
            if (current->isCompleted) {
                return true;
            }
            if (current->children[c] == nullptr) {
                current->children[c] = new TrieNode();
                same = false;
            }
            current = current->children[c];
        }
        
        current->isCompleted = true;
        
        return same;
    }
    
    
private:
    struct TrieNode {
        map<char, TrieNode*>children;
        bool isCompleted;
    };
    
    TrieNode *node;
    
private:
    // recursively delete node from bottom to top. 
    void clear(TrieNode* node) {
        
        if (node->children.size() == 0) { // is bottom
            delete node;
            return;
        }
        
        auto children = node->children;
        auto it = children.begin();
        auto end = children.end();
        
        for(; it !=end; ++it) {
            if (it->second != nullptr) {
                clear(it->second);
            }
        }
    }
};


int main() {
    int n;
    cin >> n;
    Trie tire;
    
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (tire.saveAndCheck(s)){
            cout << "BAD SET" << endl << s;
            return 0;
        }
    }
    
    cout << "GOOD SET";
    
    return 0;
}
