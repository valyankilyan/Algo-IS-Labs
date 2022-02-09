#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define mp make_pair
#define ll long long

#define MAXN 200005
#define INF 1000000009
#define MOD 1000000007

struct Node {
    int value;
    int height;
    Node *left, *right;

    Node(int x) {
        value = x;
        height = 0;
        left = NULL;
        right = NULL;
    }
};

class Tree {
    Node* root;

   public:
    Tree() {
        root = NULL;
    }

    Node* getRoot() {
        return root;
    }

    int getRootBalance() {
        if (!root) {
            return 0;
        }
        return getBalance(root);
    }

    bool exists(int x) {
        return searchNode(root, x);
    }

    void insert(int x) {
        if (root == NULL) {
            Node* new_node = new Node(x);
            root = new_node;
            return;
        }
        root = insertNode(root, x);
    }

    void remove(int x) {
        if (!root) {
            return;
        }
        if (root->value == x && !root->left && !root->right) {
            delete root;
            root = NULL;
            return;
        }
        root = removeNode(root, x);
    }

    int getSize(Node* node) {
        if (!node) {
            return 0;
        }
        return getSize(node->right) + getSize(node->left) + 1;
    }

    void print_tree() {
        cerr << "------------------\n";
        if (!root) {
            cerr << "-\n";
            return;
        }
        vector<vector<Node*>> v;
        vector<Node*> f_v;
        f_v.pb(root);
        v.pb(f_v);
        bool neot = true;
        bool is_not_end = false;
        while (neot) {
            neot = 0;
            vector<Node*> new_line;
            int last = v.size() - 1;
            for (int i = 0; i < v[last].size(); i++) {
                if (v[last][i] == NULL) {
                    new_line.pb(NULL);
                    new_line.pb(NULL);
                } else {
                    new_line.pb(v[last][i]->left);
                    new_line.pb(v[last][i]->right);
                    neot = (v[last][i]->left != NULL) || neot;
                    neot = (v[last][i]->right != NULL) || neot;
                }
            }
            if (neot)
                v.pb(new_line);
        }

        int space = (1 << (v.size() - 1)) - 1;
        for (auto x : v) {
            for (auto y : x) {
                cerr << string(space, ' ');
                if (y != NULL) {
                    cerr << y->value << " ";
                } else {
                    cerr << "- ";
                }
                cerr << string(space, ' ');
            }
            space = space >> 1;
            cerr << "\n";
        }
    }

   private:
    Node* searchNode(Node* node, int x) {
        if (!node) {
            return NULL;
        }

        if (node->value < x) {
            return searchNode(node->right, x);
        } else if (x < node->value) {
            return searchNode(node->left, x);
        } else {
            return node;
        }
    }

    int correctHeight(Node* rt) {
        if (!rt) {
            return -1;
        }

        rt->height = max(correctHeight(rt->right), correctHeight(rt->left)) + 1;
        return rt->height;
    }

    Node* insertNode(Node* node, int x) {
        if (!node) {
            Node* new_node = new Node(x);
            return new_node;
        }

        if (x < node->value) {
            node->left = insertNode(node->left, x);
        } else if (node->value < x) {
            node->right = insertNode(node->right, x);
        } else {
            return node;
        }
        adjustHeight(node);
        node = correctNode(node);
        return node;
    }

    Node* removeNode(Node* node, int x) {
        if (!node) {
            return NULL;
        }

        if (node->value < x) {
            node->right = removeNode(node->right, x);
        } else if (x < node->value) {
            node->left = removeNode(node->left, x);
        } else {
            if (!node->left && !node->right) {
                delete node;
                return NULL;
            } else if (!node->left) {
                Node* right = node->right;
                delete node;
                return right;
            } else {
                int value = 0;
                node->left = removeRightest(node->left, &value);
                node->value = value;
            }
        }
        adjustHeight(node);
        node = correctNode(node);
        return node;
    }

    Node* removeRightest(Node* node, int* value) {
        if (node->right) {
            node->right = removeRightest(node->right, value);
        } else {
            *value = node->value;
            if (node->left) {
                Node* left = node->left;
                delete node;
                adjustHeight(left);
                return left;
            } else {
                delete node;
                return NULL;
            }
        }
        adjustHeight(node);
        node = correctNode(node);
        return node;
    }

    void adjustHeight(Node* rt) {
        rt->height = max(getHeight(rt->right), getHeight(rt->left)) + 1;
    }

    Node* correctNode(Node* rt) {
        if (!rt) {
            return NULL;
        }
        if (getBalance(rt) > 1) {
            if (getBalance(rt->right) < 0) {
                rt = leftHeavyRotation(rt);
            } else {
                rt = leftRotation(rt);
            }
            correctHeight(rt);
        } else if (getBalance(rt) < -1) {
            if (getBalance(rt->left) > 0) {
                rt = rightHeavyRotation(rt);
            } else {
                rt = rightRotation(rt);
            }
            correctHeight(rt);
        }
        return rt;
    }

    Node* rightRotation(Node* rt) {
        Node* b = rt->left;
        rt->left = b->right;
        b->right = rt;
        return b;
    }

    Node* leftRotation(Node* rt) {
        Node* b = rt->right;
        rt->right = b->left;
        b->left = rt;
        return b;
    }

    Node* rightHeavyRotation(Node* rt) {
        rt->left = leftRotation(rt->left);
        return rightRotation(rt);
    }

    Node* leftHeavyRotation(Node* rt) {
        rt->right = rightRotation(rt->right);
        return leftRotation(rt);
    }

    int getHeight(Node* rt) {
        if (!rt) {
            return -1;
        }
        return rt->height;
    }

    int getBalance(Node* rt) {
        return getHeight(rt->right) - getHeight(rt->left);
    }
};

void solve() {
    int n;
    cin >> n;
    Tree tree = Tree();

    for (int i = 0; i < n; i++) {
        char c;
        int x;
        cin >> c >> x;

        switch (c) {
            case 'A':
                tree.insert(x);
                cout << tree.getRootBalance() << endl;
                break;
            case 'D':
                tree.remove(x);
                cout << tree.getRootBalance() << endl;
                break;
            case 'C':
                cout << (tree.exists(x) ? 'Y' : 'N') << endl;
                break;
        }
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("avlset.in", "r", stdin);
    freopen("avlset.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}