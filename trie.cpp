#include <cmath>
#include <bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);

struct TrieNode { 
    bool isLeaf;
    TrieNode* parent = nullptr;
    vector<TrieNode*> letters; 
    public:
     TrieNode() {
         letters = vector<TrieNode *> (26, nullptr);
     }
}; 

class Trie {
    private: 
    TrieNode* root; 
    int totalnum = 1;
   
    void alphabetical(TrieNode* node, string str) {
        if (node->isLeaf){
            cout << str << '\n';
        }
        
        for (int i = 0; i < 26; i++){
            string temp = "";
            temp += str;
            if (node->letters[i]){
                char letter = i + 'a';
                temp += letter;
                alphabetical(node->letters[i],temp);
            }
        }
    }
    
    void autocomplete(TrieNode* node, string prefix, int max, string str) {
        string temp = "";
        //iterate to prefix
        for (int i = 0; i < prefix.size(); i++){
            char letter = prefix[i];
            int letterIndex = letter - 'a';
            if (node->letters[letterIndex] == nullptr){
                break;
            }
            temp += letter;
            node = node->letters[letterIndex];
        }
        //prefix exists, throw into iterate
        if (!temp.empty()){
            iterate(node, temp, max);
        }
        cout << '\n';
    }
    
    void iterate (TrieNode* node, string str, int max){
        if (node->isLeaf){
            cout << str << " ";
        }
        
        --max;
        
        for (int i = 0; i < 26; i++){
            string temp = "";
            temp += str;
            if (node->letters[i]){
                char letter = i + 'a';
                temp += letter;
                if (max < -1){
                    iterate(node->letters[i],temp,max);
                }
                else if (max >= 0){
                    iterate(node->letters[i],temp,max);
                }
                else
                    return;
            }
        }
    }
        
    int info(TrieNode* node) {
        int total = 0;
        
        if (node->isLeaf){
            ++total;
        }
        
        for (int i = 0; i < 26; i++){
            if (node->letters[i]){
                total += info(node->letters[i]);
            }
        }
        return total;
    }
    
    
    public: 
    Trie() {
        root = new TrieNode();
    } 
    
    void insert(string str) {
        TrieNode* curr = root;
        
        for (int i = 0; i < str.size(); i++){
            int letterIndex = str[i] - 'a';    
            
            if (curr->letters[letterIndex] == nullptr){
                //create new node
                TrieNode* node = new TrieNode();
                node->isLeaf = false;
                curr->letters[letterIndex] = node;
                //assign parent
                node->parent = curr;
                ++totalnum;
            }
            curr = curr->letters[letterIndex];
        }
        curr->isLeaf = true;
    }
    
    bool lookup(string str) {
        TrieNode* curr = root;
        
        for (int i = 0; i < str.size(); i++){
            int letterIndex = str[i] - 'a';    
            
            if (curr->letters[letterIndex] == nullptr){
                return false;
            }
            curr = curr->letters[letterIndex];
        }
        
        return curr->isLeaf;
    } 
    
    void remove(string str) {
        TrieNode* curr = root;
        int len = str.size();
        vector<int> list;
        
        for (int i = 0; i < len; i++){
            int letterIndex = str[i] - 'a';   
            if (curr->letters[letterIndex] == nullptr){
                return;
            }
            list.push_back(letterIndex);
            curr = curr->letters[letterIndex];
        }
        curr->isLeaf = false;
        
        int pos = str.size() - 1;
        bool hasChildren = false;
        
        while (!curr->isLeaf && !hasChildren){
            //check for children
            for (auto i: curr->letters){
                if (i != nullptr){
                    hasChildren = true;
                    break;
                }
            }
            //does not have children
            if (!hasChildren){
                //remove node, go to parent
                TrieNode* temp = curr;
                curr->parent->letters[list[pos]] = nullptr;
                curr = curr->parent;
                temp = nullptr;
                --totalnum;
                --pos;
            }
        }
        
        
    } 
    
    int info() {
        int num, total;
        total = info(root);
        cout << totalnum << " ";
        return total;
    }
    
    void alphabetical() {
        string str = "";
        alphabetical(root, str);
    }
    
    void autocomplete(string prefix, int max) {
        string str = "";
        autocomplete(root, prefix, max, str);
    }
};

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}


int main() {
    string n_temp;
    getline(cin, n_temp);
    
    Trie trietree;
    
    int n = stoi(ltrim(rtrim(n_temp)));
    for (int n_itr = 0; n_itr < n; n_itr++) {
        // Write your code here to read in the command and any additional input (if needed)
        string c_temp;
        cin >> c_temp;
        string command = (ltrim(rtrim(c_temp)));
        
        if (command == "insert"){
            string str;
            cin >> str;
            trietree.insert(str);
        }
        if (command == "lookup"){
            string str;
            cin >> str;
            cout << trietree.lookup(str) << '\n';
        }
        if (command == "remove"){
            string str;
            cin >> str;
            trietree.remove(str);
        }
        if (command == "info"){
            cout << trietree.info() << endl;
        }
        
        if (command == "alphabetical"){
            trietree.alphabetical();
        }
        
        if (command == "autocomplete"){
            string prefix;
            cin >> prefix;
            int len;
            cin >> len;
            trietree.autocomplete(prefix, len);
        }
    }
    return 0;
}
