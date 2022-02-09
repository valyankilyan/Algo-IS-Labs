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
   public:
    Node* root;

    Tree() {
        root = NULL;
    }

    Node* getRoot() {
        return root;
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
        if (root->value == x && !root->left && !root->right) {
            delete root;
            root = NULL;
            return;
        }
        root = removeNode(root, x);
    }

    int correctHeight(Node* rt) {
        if (!rt) {
            return -1;
        }

        rt->height = max(correctHeight(rt->right), correctHeight(rt->left)) + 1;
        return rt->height;
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

    Node* insertNodeWithoutCorrection(Node* node, int x) {
        if (x < node->value) {
            if (node->left == NULL) {
                Node* new_node = new Node(x);
                node->left = new_node;
                return new_node;
            } else {
                return insertNodeWithoutCorrection(node->left, x);
            }
        } else if (node->value < x) {
            if (node->right == NULL) {
                Node* new_node = new Node(x);
                node->right = new_node;
                return new_node;
            } else {
                return insertNodeWithoutCorrection(node->right, x);
            }
        } else if (node->value == x) {
            return node;
        }
        return NULL;
    }

   private:
    Node* insertNode(Node* node, int x) {
        if (!node) {
            Node* new_node = new Node(x);
            return new_node;
        }

        if (x < node->value) {
            node->left = insertNode(node->left, x);
        } else if (node->value < x) {
            node->right = insertNode(node->right, x);
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

#define NODES_COUNT 31
#define LEN 16

Tree make_test(int nodes) {
    Tree tree = Tree();
    for (int i = 1; i <= NODES_COUNT; i++) {
        tree.insert(i);
    }
    for (int i = 0; i < LEN; i++) {
        if ((1 << i) & nodes) {
            tree.remove(i * 2 - 1);
        }
    }

    return tree;
}

void test() {
    int n = 1;
    for (int nodes = 0; nodes < (1 << LEN) && n; nodes++) {
        cerr << nodes << endl;
        for (int del = 1; del < NODES_COUNT; del++) {
            if (del % 2)
                continue;
            Tree tree = make_test(nodes);
            n = tree.getSize(tree.root) - 1;
            tree.remove(del);
            if (n != tree.getSize(tree.root)) {
                make_test(nodes).print_tree();
                tree.print_tree();
                cerr << "DEL = " << del << endl;
                while (n--)
                    cerr << "kek";
                cerr << endl;
                nodes = INF;
                break;
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> vk(n + 1), vl(n + 1), vr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> vk[i] >> vl[i] >> vr[i];
    }

    Tree tree = Tree();
    queue<pair<int, Node*>> in_q;

    if (n) {
        tree.insert(vk[1]);
        in_q.push(mp(1, tree.root));
    }
    while (!in_q.empty()) {
        int cur_num = in_q.front().f;
        Node* cur_node = in_q.front().s;
        in_q.pop();

        if (vl[cur_num]) {
            in_q.push(mp(vl[cur_num],
                         tree.insertNodeWithoutCorrection(cur_node, vk[vl[cur_num]])));
        }
        if (vr[cur_num]) {
            in_q.push(mp(vr[cur_num],
                         tree.insertNodeWithoutCorrection(cur_node, vk[vr[cur_num]])));
        }
    }

    // tree.print_tree();
    tree.correctHeight(tree.root);
    int d;
    cin >> d;
    // cerr << "deleting: " << d << endl;
    tree.remove(d);
    // tree.print_tree();

    int ind = 1;
    queue<Node*> q_out;
    cout << --n << '\n';
    if (n) {
        q_out.push(tree.root);
    }
    while (!q_out.empty()) {
        int l = 0, r = 0;
        if (q_out.front()->left) {
            l = ++ind;
            q_out.push(q_out.front()->left);
        }
        if (q_out.front()->right) {
            r = ++ind;
            q_out.push(q_out.front()->right);
        }
        cout << q_out.front()->value << ' ' << l << ' ' << r << '\n';
        q_out.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("deletion.in", "r", stdin);
    freopen("deletion.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}