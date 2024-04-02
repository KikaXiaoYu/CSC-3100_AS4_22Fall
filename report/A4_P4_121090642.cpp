
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

class Node {
public:
    Node(int count): sub_count(0) {}
    unordered_map<char, Node*> child_lst; 
    int sub_count;
};

void insert(Node* root, string str) {
    Node* cur_node = root;
    Node* new_node;
    for (int i = 0; i < str.size(); i++) {
        if (cur_node->child_lst.find(str[i]) == cur_node->child_lst.end()) {
            new_node = new Node(0);
            cur_node->child_lst.insert({str[i], new_node});
        }
        cur_node = cur_node->child_lst.find(str[i])->second;
        cur_node->sub_count++;
    }
}

int getNum(Node* root, string prefix) {
    Node* cur_node = root;
    for (int i = 0; i < prefix.size(); i++) {
        if (cur_node->child_lst.find(prefix[i]) == cur_node->child_lst.end()) {
            return 0;
        }
        cur_node = cur_node->child_lst.find(prefix[i])->second;
    }
    return cur_node->sub_count;
}

int main() {
    Node* root = new Node(0);
    int i;
    int n;
    cin >> n;
    string str;
    for (i = 0; i < n; i++) {
        cin >> str;
        insert(root, str);
    }
    int q;
    cin >> q;
    for (i = 0; i < q; i++) {
        cin >> str;
        cout << getNum(root, str) << endl;
    }
}

