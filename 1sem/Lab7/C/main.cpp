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

    int correctHeight(Node* rt) {
        if (!rt) {
            return -1;
        }

        rt->height = max(correctHeight(rt->right), correctHeight(rt->left)) + 1;
        return rt->height;
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
            // int prev = 0;
            for (auto y : x) {
                // cerr << string(max(space - prev, 0), ' ');
                cerr << string(space, ' ');
                // prev = 0;
                if (y != NULL) {
                    cerr << y->value << " ";
                    // prev = to_string(y->value).size() - 1;
                } else {
                    cerr << "- ";
                }
                // int spacing = max(space - prev, 0);
                // prev -= min(spacing, prev);
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

    void adjustHeight(Node* rt) {
        rt->height = max(getHeight(rt->right), getHeight(rt->left)) + 1;
    }

    Node* correctNode(Node* rt) {
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

    tree.correctHeight(tree.root);
    int in;
    cin >> in;
    tree.insert(in);

    int ind = 1;
    queue<Node*> q_out;
    cout << ++n << endl;
    q_out.push(tree.root);
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
        cout << q_out.front()->value << " " << l << " " << r << endl;
        q_out.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("addition.in", "r", stdin);
    freopen("addition.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}