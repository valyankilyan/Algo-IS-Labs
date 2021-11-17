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
        if (root == NULL) {
            root->value = in;
        } else {
            Node *cur = root;
            while (!put_if_right_node(cur, in)) {
                cur = next_node(cur, in);
            }
        }
    }

    void remove(int in) {
        Node *node = find_node(in);
    }

    bool exists(int in) {
    }

    int next(int in) {
    }

    int prev(int in) {
    }

    void print() {
		queue <Node> q;
		q.push(*root);
		bool is_not_end = false;
		while (!q.empty()) {
			Node *last = q.back();
			Node *cur;
			queue <int> printing;
			while (cur != last) {
				cur = q.front();
				q.pop();
				printing.push(cur != NULL ? cur->value : -INF);
				is_not_end = is_not_end || cur != NULL;
			}
		}
    }

   private:
    bool put_if_right_node(Node *cur, int in) {
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
        if (cur->value < in && cur->right != NULL) {
            return cur->right;
        }
        if (in < cur->value && cur->left != NULL) {
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
            cout << bst.exists(x) << '\n';
        } else if (request == "next") {
            int ans = bst.exists(x);
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

#ifdef LOCAL
    bool a;
    a = freopen("in.data", "r", stdin);
    a = freopen("out.data", "w", stdout);
    cin >> tests;
#endif

    while (tests--)
        solve();
}