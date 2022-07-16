#include <bits/stdc++.h>
using namespace std;

struct node
{
    node *left, *right;
    int left_height, right_height;
    int count;
    int val;
    node(int val) : val(val), left(nullptr), right(nullptr), left_height(1), right_height(1), count(1) {}
    int bf()
    {
        return left_height - right_height;
    }
};

void assignHeight(node *root)
{
    root->left_height = root->left ? max(root->left->left_height, root->left->right_height) + 1 : 1;
    root->right_height = root->right ? max(root->right->left_height, root->right->right_height) + 1 : 1;
    root->count = (root->left ? root->left->count : 0) + (root->right ? root->right->count : 0) + 1;
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
        root = balance(root);
        return root;
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
        root->left = rr(root->left);
        return ll(root);
    }
    node *rl(node *root)
    {
        root->right = ll(root->right);
        return rr(root);
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
        return root;
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

    int nth_node(node* root, int n) {
        if (root == nullptr) return -1;
        int left_val = root->left ? root->left->count : 0;
        int right_val = root->right ? root->right->count : 0;
        if (n == left_val + 1) return root->val;
        if (n > left_val + 1) {
            return nth_node(root->right, n - left_val - 1);
        } else {
            return nth_node(root->left, n);
        }
    }

    int get_rank(node* root, int val) {
        if (root == nullptr) return -1;
        if (root->val == val) {
            return (root->left ? root->left->count : 0) + 1;
        } else if (root->val < val) {
            return get_rank(root->right, val) + (root->left ? root->left->count : 0) + 1;
        } else {
            return get_rank(root->left, val);
        }
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
        return true;
    }

    void print() {
        queue<node*> q;
        q.push(root);
        while (!q.empty()) {
            queue<node*> nq;
            while (!q.empty()) {
                cout << q.front()->val << ' ' << q.front()->left_height << ' ' << q.front()->right_height << ' ' << q.front()->count << endl;
                if (q.front()->left) nq.push(q.front()->left);
                if (q.front()->right) nq.push(q.front()->right);
                q.pop();
            }
            q = move(nq);
        }
    }

    int nth_node(int n) {
        return nth_node(root, n);
    }

    int get_rank(int val) {
        return get_rank(root, val);
    }
};

int main()
{
    srand(time(NULL));
    tree t;
    int n = 7;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.push_back(rand() % 100);
        t.insert(a.back());
    }
    cout << endl;

    t.print();

    for (int i = 1; i <= n; i++) {
        cout << t.nth_node(i) << ' ';
    }

    cout << endl;

    for (int& i : a) {
        cout << i << ' ' << t.get_rank(i) << endl;
    }
}
