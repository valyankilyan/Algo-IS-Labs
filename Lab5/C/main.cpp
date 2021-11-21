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

    void insert(int in) {
        if (exists(in)) {
            return;
        }
        cerr << "insert(" << in << ") \n";
        if (root == NULL) {
            Node *tmp = new Node(in);            
            root = tmp;            
        } else {
            Node *cur = root;
            while (!put_if_right_node(cur, in)) {
                cur = next_node(cur, in);
            }
        }
        print();
    }

    // void remove(int in) {
    //     cerr << "remove(" << in << ") \n";
    //     Node *node = find_node(in);
    //     cerr << "node->value = " << node->value << endl;
    //     if (node->left == NULL && node->right == NULL) {
    //         node = NULL;
    //         delete node;            
    //     } else if (node->left == NULL) {
    //         // Node *tmp = node->right;
    //         node->value = node->right->value;
    //         node->left = node->right->left;
    //         node->right = node->right->right;            
    //     } else if (node->right == NULL) {
    //         // Node *tmp = node->left;
    //         node->value = node->left->value;
    //         node->right = node->left->right;
    //         node->left = node->left->left;
    //     } else {
    //         int tmp = min_node(node->right)->value;
    //         remove(tmp);
    //         node->value = tmp;
    //     }
    //     print();
    // }

    void remove(int in) {
        cerr << "remove(" << in << ")\n";
        root = removeNode(root, in);
        print();
    }

    bool exists(int in) {
        Node *search = find_node(in);
        cerr << "exist(" << in << ") = " << (search != NULL) << "\n";
        print();
        return search != NULL;
    }

    int next(int value) {
        Node *tmp = find_next_node(root, value);
        int ans = tmp == NULL ? -INF : tmp->value;
        cerr << "next(" << value << ") = " << ans << '\n';
        print();
        return ans;
    }

    int prev(int value) {
        Node *tmp = find_prev_node(root, value);
        int ans = tmp == NULL ? -INF : tmp->value;
        cerr << "prev(" << value << ") = " << ans << '\n';
        print();
        return ans;
    }

    void print() {        
        // cerr << "printing bst\n";
		vector<vector<Node*>> v;
        vector <Node*> f_v;
        f_v.pb(root);
		v.pb(f_v);        
        bool neot = true;
		bool is_not_end = false;
		while (neot) {            
            neot = 0;
            vector <Node*> new_line;
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
        for (auto x: v) {            
            for (auto y: x) {                
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
    Node* removeNode(Node *cur, int value) {
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
                Node* tmp = cur->right;
                delete cur;
                return tmp;
            }
            if (cur->right == NULL) {
                Node* tmp = cur->left;
                delete cur;
                return tmp;
            }

            Node* tmp = min_node(cur->right);
            cur->value = tmp->value;
            cur->right = removeNode(cur->right, tmp->value);
        }

        return cur;
    }

    Node* min_node(Node *cur) {
        if (cur->left != NULL)
            return min_node(cur->left);
        return cur;
    }

    bool put_if_right_node(Node *cur, int in) {
        // cerr << cur->value << " " << in << endl;
        if (cur->value < in && cur->right == NULL) {
            Node *tmp = new Node(in);
            cur->right = tmp;
            return true;
        }
        if (in < cur->value && cur->left == NULL) {
            Node *tmp = new Node(in);
            cur->left = tmp;
            return true;
        }
        return false;
    }

    Node *next_node(Node *cur, int in) {
        if (cur->value < in) {
            return cur->right;
        }
        if (in < cur->value) {
            return cur->left;
        }
        return cur;
    }

    Node *find_node(int in) {
        Node *cur = root;
        while (cur != NULL && cur->value != in) {
            cur = next_node(cur, in);
        }
        return cur;
    }

    Node *find_next_node(Node *cur, int value) {
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