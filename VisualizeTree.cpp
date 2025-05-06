#include <bits/stdc++.h>
using namespace std;

struct Node {
    string val;
    Node* left;
    Node* right;

    Node(string v) : val(v), left(nullptr), right(nullptr) {}
};

void postorder(Node* root, stringstream& ss) {
    if (!root) return;

    postorder(root->left, ss);
    postorder(root->right, ss);
    ss << root->val << " ";
}

bool isNumber(const string& token) {
    if (token.empty()) return false;
    if (token[0] == '-' && token.length() > 1)
        return all_of(token.begin() + 1, token.end(), ::isdigit);
    return all_of(token.begin(), token.end(), ::isdigit);
}

int evalPostfix(const string& expr) {
    stack<int> stk;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        if (isNumber(token)) {
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

void writeDot(Node* node, ofstream& out) {
    if (!node) return;

    string id = "\"" + to_string(reinterpret_cast<uintptr_t>(node)) + "\"";
    out << "    " << id << " [label=\"" << node->val << "\"];\n";

    if (node->left) {
        string leftId = "\"" + to_string(reinterpret_cast<uintptr_t>(node->left)) + "\"";
        out << "    " << id << " -> " << leftId << ";\n";
        writeDot(node->left, out);
    }

    if (node->right) {
        string rightId = "\"" + to_string(reinterpret_cast<uintptr_t>(node->right)) + "\"";
        out << "    " << id << " -> " << rightId << ";\n";
        writeDot(node->right, out);
    }
}

void exportToDot(Node* root, const string& filename) {
    ofstream out(filename);
    out << "digraph ExpressionTree {\n";
    out << "    node [shape=circle, style=filled, color=lightblue, fontname=\"Helvetica\"];\n";
    writeDot(root, out);
    out << "}\n";
    out.close();
}

int main() {
    // insert node here
    Node* root = new Node("-27");
    // root->left = new Node("3");
    // root->right = new Node("-9");
    // root->left->left = new Node("2");
    // root->left->right = new Node("1");
    // root->right->left = new Node("27");
    // root->right->right = new Node("36");
    // root->left->left->left = new Node("7");
    // root->left->left->right = new Node("5");
    // root->left->right->left = new Node("7");
    // root->left->right->right = new Node("7");
    // root->right->left->left = new Node("9");
    // root->right->left->right = new Node("3");
    // root->right->right->left = new Node("6");
    // root->right->right->right = new Node("2");
    
    stringstream postfix;
    postorder(root, postfix);
    string expr = postfix.str();

    cout << "Postfix: " << expr << endl;
    cout << "Evaluated Result: " << evalPostfix(expr) << endl;

    exportToDot(root, "tree.dot");
    cout << "DOT file exported as tree.dot" << endl;

    return 0;
}
