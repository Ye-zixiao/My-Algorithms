/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> preorder(Node* root) {
        stack<Node*> nodeStack;
        vector<int> ivec;
        Node* temp;

        if (root != nullptr) {
            nodeStack.push(root);
            while (!nodeStack.empty()) {
                temp = nodeStack.top();
                nodeStack.pop();
                ivec.push_back(temp->val);
                for (int i = temp->children.size() - 1;i >= 0;--i)
                    nodeStack.push(temp->children[i]);
            }
        }
        return ivec;
    }
};