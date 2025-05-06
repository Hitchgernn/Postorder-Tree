#include <bits/stdc++.h>
using namespace std;

struct Node {
    string data;
    Node *right, *left;

    Node(string data) {
        this->data = data;
        this->right = nullptr;
        this->left = nullptr;
    }
};

void postOrderTraversal(Node* node, stringstream& ss) {
    if (node == nullptr) return;
    postOrderTraversal(node->left, ss);
    postOrderTraversal(node->right, ss);
    ss << node->data << " ";
}

int evalPostfix(const string& expr) {
    stringstream ss(expr);
    stack<int> stk;
    string token;

    while (ss >> token) {
        if (!(token == "+" || token == "-" || token == "*" || token == "/" || token == "^")) {
            stk.push(stoi(token));    
        } else {
            int right = stk.top(); stk.pop();
            int left = stk.top(); stk.pop();

            if (token == "+") stk.push(left + right);
            else if (token == "-") stk.push(left - right);
            else if (token == "*") stk.push(left * right);
            else if (token == "/") stk.push(left / right);
            else if (token == "^") stk.push(pow(left, right));
        }
    }
    return stk.top();
}

int main () {
    Node* root = new Node("*");
    root->left = new Node("+");
    root->right = new Node("-");
    root->left->left = new Node("-");
    root->left->right = new Node("/");
    root->right->left = new Node("*");
    root->right->right = new Node("^");
    root->left->left->left = new Node("7");
    root->left->left->right = new Node("5");
    root->left->right->left = new Node("7");
    root->left->right->right = new Node("7");
    root->right->left->left = new Node("9");
    root->right->left->right = new Node("3");
    root->right->right->left = new Node("6");
    root->right->right->right = new Node("2");

    stringstream postfix;
    postOrderTraversal(root, postfix);
    string expr = postfix.str();
    cout << "Potfix form: " << expr << endl;
    cout << "Evaluated result: " << evalPostfix(expr);
    return 0;
}