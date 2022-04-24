#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define mp make_pair
#define ll long long

#define MAXN 200005
#define INF 1000000000
#define LINF 9223372036854775807
#define MOD 1000000007

vector<int> loop;
vector<bool> was;
vector<vector<int>> g;

bool find_loop(int v) {
    was[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        if ((!was[g[v][i]] && find_loop(g[v][i])) || was[g[v][i]]) {
            loop.pb(g[v][i]);
            return 1;
        }
    }
    return 0;
}

void solve() {
    int n;
    cin >> n;
    g.resize(n);
    was.resize(n, 0);
    loop.resize(0);
    int a[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] != INF && i != j) {
                g[i].pb(j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                a[u][v] = max(-INF, min(a[u][v], a[u][i] + a[i][v]));
            }
        }
    }

    int neg_node = -1;
    for (int i = 0; neg_node == -1 && i < n; i++) {
        if (a[i][i] < 0) {
            neg_node = i;
            break;
        }
    }
    if (neg_node == -1) {
        cout << "NO\n";
        return;
    }

    find_loop(neg_node);
    loop.pb(neg_node);
    cout << "YES\n" << loop.size() << endl;
    for (int i = loop.size() - 1; i >= 0; i--) {
        cout << loop[i] + 1 << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}