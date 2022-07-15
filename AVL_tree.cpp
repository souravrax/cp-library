#include <bits/stdc++.h>
using namespace std;

struct node
{
    node *left, *right;
    int left_height, right_height;
    int val;
    node(int val) : val(val), left(nullptr), right(nullptr), left_height(0), right_height(0) {}
    int bf()
    {
        return left_height - right_height;
    }
};

void assignHeight(node *root)
{
    root->left_height = root->left ? max(root->left->left_height, root->left->right_height) + 1 : 1;
    root->right_height = root->right ? max(root->right->left_height, root->right->right_height) + 1 : 1;
}

class tree
{
    node *root;
    int sz;
    node *insert(node *root, int val)
    {
        if (root == nullptr)
            return new node(val);
        if (root->val > val)
        {
            root->left = insert(root->left, val);
        }
        else
        {
            root->right = insert(root->right, val);
        }
        assignHeight(root);
        return balance(root);
    }

    bool find(node *root, int val)
    {
        if (root == nullptr)
            return false;
        if (root->val == val)
            return true;
        if (root->val < val)
            return find(root->right, val);
        return find(root->left, val);
    }

    node *ll(node *root)
    {
        node *left = root->left;
        root->left = left->right;
        left->right = root;
        assignHeight(root);
        assignHeight(left);
        return left;
    }
    node *rr(node *root)
    {
        node *right = root->right;
        root->right = right->left;
        right->left = root;
        assignHeight(root);
        assignHeight(right);
        return right;
    }
    node *lr(node *root)
    {
        rr(root->left);
        ll(root);
    }
    node *rl(node *root)
    {
        ll(root->right);
        rr(root->left);
    }
    node *balance(node *root)
    {
        if (root->bf() == 2)
        {
            // left_heavy
            if (root->left->bf() == 1)
            {
                // left-left
                return ll(root);
            }
            else
            {
                // left-right
                return lr(root);
            }
        }
        else if (root->bf() == -2)
        {
            // right_heavy
            if (root->right->bf() == 1)
            {
                // right-left
                return rl(root);
            }
            else
            {
                // right-right
                return rr(root);
            }
        }
    }

    node* append_end(node* curr, node* left) {
        if (curr == nullptr) return left;
        curr->left = append_end(curr->left, left);
        assignHeight(curr);
        return curr;
    }

    node* erase(node* root, int val) {
        if (root == nullptr) return nullptr;
        if (root->val == val) {
            if (root->right == nullptr) return root->left;
            root->right = append_end(root->right, root->left);
            node* right = root->right;
            delete root;
            return right;
        } 
        if (root->val < val) {
            root->right = erase(root->right, val);
        } else {
            root->left = erase(root->left, val);
        }
        assignHeight(root);
        return root;
    }

public:
    tree()
    {
        this->root = nullptr;
        sz = 0;
    }

    bool insert(int val)
    {
        if (find(val))
            return false;
        sz++;
        root = insert(root, val);
        return true;
    }

    bool find(int val)
    {
        return find(root, val);
    }

    int size()
    {
        return this->sz;
    }

    bool erase(int val) {
        if (!find(val)) return false;
        erase(root, val);
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a)
        cin >> i;
}