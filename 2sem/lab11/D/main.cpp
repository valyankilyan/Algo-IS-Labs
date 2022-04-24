#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define mp make_pair
#define ll long long

#define MAXN 200005
#define INF 1000000009
const ll LINF = 5000000000000000000;

#define MOD 1000000007

struct edge {
    int a, b;
    ll cost;
};
vector<vector<int>> g;
vector<bool> in_loop;

void loop_search(int v) {
    in_loop[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        if (!in_loop[g[v][i]]) {
            loop_search(g[v][i]);
        }
    }
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<edge> e(m);
    g.resize(n);
    in_loop.clear();
    in_loop.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> e[i].a >> e[i].b >> e[i].cost;
        e[i].a--;
        e[i].b--;
        g[e[i].a].pb(e[i].b);
    }
    vector<ll> d(n, LINF);
    d[s - 1] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (d[e[j].a] < LINF) {
                if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    d[e[j].b] = max(-LINF, d[e[j].a] + e[j].cost);
                }
            }
        }
    }

    for (int j = 0; j < m; j++) {
        if (d[e[j].a] < LINF) {
            if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                loop_search(e[j].a);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (in_loop[i]) {
            cout << '-';
        } else if (d[i] == LINF) {
            cout << '*';
        } else {
            cout << d[i];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("path.in", "r", stdin);
    // freopen("test.in", "r", stdin);
    freopen("path.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}