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
    struct Node *left, *right;

    Node(int x) {
        value = x;
        left = NULL;
        right = NULL;
    }
};

class BSTSimple {
    Node *root;

   public:
    BSTSimple() {
        root = NULL;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = removeNode(root, value);
    }

    bool exists(int value) {
        Node *search = find_node(root, value);
        return search != NULL;
    }

    int next(int value) {
        Node *tmp = find_next_node(root, value);
        int ans = tmp == NULL ? -INF : tmp->value;
        return ans;
    }

    int prev(int value) {
        Node *tmp = find_prev_node(root, value);
        int ans = tmp == NULL ? -INF : tmp->value;
        return ans;
    }

    void print() {
        vector<vector<Node *>> v;
        vector<Node *> f_v;
        f_v.pb(root);
        v.pb(f_v);
        bool neot = true;
        bool is_not_end = false;
        while (neot) {
            neot = 0;
            vector<Node *> new_line;
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
                if (y != NULL)
                    cerr << y->value << " ";
                else
                    cerr << "- ";
                cerr << string(space, ' ');
            }
            space = space >> 1;
            cerr << "\n";
        }
    }

   private:
    Node *insertNode(Node *cur, int value) {
        if (cur == NULL) {
            Node *tmp = new Node(value);
            return tmp;
        }
        if (cur->value < value) {
            cur->right = insertNode(cur->right, value);
        }
        if (value < cur->value) {
            cur->left = insertNode(cur->left, value);
        }
        return cur;
    }

    Node *removeNode(Node *cur, int value) {
        if (cur == NULL) {
            return NULL;
        }
        if (value < cur->value) {
            cur->left = removeNode(cur->left, value);
        } else if (cur->value < value) {
            cur->right = removeNode(cur->right, value);
        } else {
            if (cur->left == NULL && cur->right == NULL) {
                return NULL;
            }
            if (cur->left == NULL) {
                Node *tmp = cur->right;
                delete cur;
                return tmp;
            }
            if (cur->right == NULL) {
                Node *tmp = cur->left;
                delete cur;
                return tmp;
            }

            Node *tmp = min_node(cur->right);
            cur->value = tmp->value;
            cur->right = removeNode(cur->right, tmp->value);
        }

        return cur;
    }

    Node *min_node(Node *cur) {
        if (cur->left != NULL)
            return min_node(cur->left);
        return cur;
    }

    Node *find_node(Node *cur, int value) {
        if (cur == NULL) {
            return NULL;
        }
        if (cur->value < value) {
            return find_node(cur->right, value);
        }
        if (value < cur->value) {
            return find_node(cur->left, value);
        }
        return cur;
    }

    Node *find_next_node(Node *cur, int value) {
        if (cur == NULL) {
            return cur;
        }

        if (cur->value <= value) {
            if (cur->right == NULL) {
                return NULL;
            }
            return find_next_node(cur->right, value);
        }
        if (value < cur->value) {
            if (cur->left == NULL) {
                return cur;
            }
            Node *tmp = find_next_node(cur->left, value);
            if (tmp == NULL) {
                return cur;
            } else {
                return tmp;
            }
        }
        return NULL;
    }

    Node *find_prev_node(Node *cur, int value) {
        if (cur == NULL) {
            return cur;
        }

        if (value <= cur->value) {
            if (cur->left == NULL) {
                return NULL;
            }
            return find_prev_node(cur->left, value);
        }
        if (cur->value < value) {
            if (cur->right == NULL) {
                return cur;
            }
            Node *tmp = find_prev_node(cur->right, value);
            if (tmp == NULL) {
                return cur;
            } else {
                return tmp;
            }
        }
        return NULL;
    }
};

void solve() {
    BSTSimple bst;
    string request;
    while (cin >> request) {
        int x;
        cin >> x;
#ifdef CERR
        cerr << request << " " << x << endl;
#endif
        if (request == "insert") {
            bst.insert(x);
        } else if (request == "delete") {
            bst.remove(x);
        } else if (request == "exists") {
            cout << (bst.exists(x) ? "true" : "false") << '\n';
        } else if (request == "next") {
            int ans = bst.next(x);
            if (ans != -INF) {
                cout << ans << '\n';
            } else {
                cout << "none\n";
            }
        } else if (request == "prev") {
            int ans = bst.prev(x);
            if (ans != -INF) {
                cout << ans << '\n';
            } else {
                cout << "none\n";
            }
        }
#ifdef CERR
        bst.print();
#endif
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("bstsimple.in", "r", stdin);
    freopen("bstsimple.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}