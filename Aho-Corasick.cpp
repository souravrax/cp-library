#include <bits/stdc++.h>
using namespace std;

const int CHAR_LENGTH = 26;
struct TrieNode
{
    TrieNode *children[CHAR_LENGTH];
    TrieNode *fail_node;
    TrieNode *parent;
    int val;
    string log_val;
    bool is_word;
    TrieNode()
    {
        memset(children, 0, sizeof children);
        parent = nullptr;
        fail_node = nullptr;
        val = -1;
        is_word = false;
    }
    TrieNode(TrieNode *p, int v) : parent(p), val(v)
    {
        memset(children, 0, sizeof children);
        fail_node = nullptr;
        is_word = false;
    }
};

struct Aho
{
    TrieNode *root;
    Aho(const vector<string> &patterns)
    {
        this->root = new TrieNode();
        root->parent = root;
        root->log_val = "root";

        for (auto &pattern : patterns)
            insert(pattern);
        build_failure_links();
    }

    void insert(string word)
    {
        auto curr = this->root;
        string now;
        for (char &c : word)
        {
            int id = c - 'a';
            now += c;
            if (!curr->children[id])
            {
                curr->children[id] = new TrieNode(curr, id);
            }
            curr = curr->children[id];
            curr->log_val = now;
        }
        curr->is_word = true;
    }

private:
    void build_failure_links()
    {
        root->fail_node = root;
        queue<TrieNode *> q;
        for (int i = 0; i < 26; i++)
        {
            if (root->children[i])
            {
                root->children[i]->fail_node = root;
                q.push(root->children[i]);
            }
        }
        while (!q.empty())
        {
            auto t = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
            {
                if (t->children[i])
                {
                    t->children[i]->fail_node = get_link(t->children[i]);
                    q.push(t->children[i]);
                }
            }
        }
    }

    TrieNode *get_link(TrieNode *node)
    {
        auto curr = node->parent;
        while (curr != root)
        {
            curr = curr->fail_node;
            if (curr->children[node->val] != nullptr)
            {
                return curr->children[node->val];
            }
        }
        return root;
    }

public:
    void print()
    {
        queue<TrieNode *> q;
        q.push(root);
        while (!q.empty())
        {
            queue<TrieNode *> nq;
            while (!q.empty())
            {
                auto t = q.front();
                q.pop();
                cout << t->parent->val << ' ';
                for (int i = 0; i < 26; i++)
                {
                    if (t->children[i])
                    {
                        nq.push(t->children[i]);
                    }
                }
            }
            cout << endl;
            q = nq;
        }
        q.push(root);
        while (!q.empty())
        {
            queue<TrieNode *> nq;
            while (!q.empty())
            {
                auto t = q.front();
                q.pop();
                cout << t->fail_node->log_val << ' ';
                for (int i = 0; i < 26; i++)
                {
                    if (t->children[i])
                    {
                        nq.push(t->children[i]);
                    }
                }
            }
            cout << endl;
            q = nq;
        }
    }
};

int main()
{
    int n;
    cin >> n;
    vector<string> have;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        have.emplace_back(s);
    }
    Aho aho(have);
    aho.print();
}
