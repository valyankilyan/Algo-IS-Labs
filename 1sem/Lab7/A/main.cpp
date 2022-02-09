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

vector<int> B;
vector<pair<int, pair<int, int>>> tree;

int dfs(int v) {
    int l = 0, r = 0;
    if (tree[v].s.f) {
        l = dfs(tree[v].s.f);
    }
    if (tree[v].s.s) {
        r = dfs(tree[v].s.s);
    }

    B[v] = r - l;
    return max(l, r) + 1;
}

void solve() {
    int n;
    cin >> n;
    B.resize(n + 1);
    tree.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int k, l, r;
        cin >> k >> l >> r;
        tree[i].s.f = l;
        tree[i].s.s = r;
        tree[l].f = i;
        tree[r].f = i;
    }
    int root;
    for (int i = 1; i <= n; i++) {
        if (tree[i].f == 0) {
            root = i;
            break;
        }
    }

    dfs(root);

    for (int i = 1; i <= n; i++) {
        cout << B[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}
