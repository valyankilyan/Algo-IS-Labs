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

// graph and reverse graph
vector<vector<int>> g, gr;
// time of exit and was
vector<int> vertices, out, was;
// strong related
vector<vector<int>> sr;
// time of exit  and cur strong related node
int cur;

void dfs(int v) {
    // cerr << "dfs(" << v << ")\n";
    was[v] = 1;
    for (int i = 0; i < g[v].size(); i++) {
        if (!was[g[v][i]]) {
            dfs(g[v][i]);
        }
    }
    vertices.pb(v);
    // out[v] = t++;
}

void rdfs(int v) {
    was[v] = 1;
    sr[cur].pb(v);
    for (int i = 0; i < gr[v].size(); i++) {
        if (!was[gr[v][i]]) {
            rdfs(gr[v][i]);
        }
    }
}

void solve() {
    g.clear();
    gr.clear();
    // vertices.clear();
    was.clear();
    sr.clear();

    int n, m;
    cin >> n >> m;

    g.resize(n);
    gr.resize(n);
    vertices.resize(0);
    was.resize(n);
    sr.resize(n);

    for (int i = 0; i < m; i++) {
        int f, s;
        cin >> f >> s;
        f--;
        s--;
        g[f].pb(s);
        gr[s].pb(f);
    }

    // cerr << "okay\n";
    for (int i = 0; i < n; i++) {
        // cerr << i << endl;
        if (!was[i]) {
            dfs(i);
        }
    }
    // cerr << "okay\n";

    was.assign(n, 0);
    cur = 0;
    // cerr << " vertices.size() = " << vertices.size() << endl;
    for (int i = vertices.size() - 1; i >= 0; i--) {
        // cerr << " vertices[" << i << "] = " << vertices[i] << " was = " << was[vertices[i]] << endl;
        if (!was[vertices[i]]) {
            rdfs(vertices[i]);
            cur++;
        }
    }

    int ans[n];
    // cerr << "cur = " << cur << endl;
    for (int i = 0; i < cur; i++) {
        for (int j = 0; j < sr[i].size(); j++) {
            ans[sr[i][j]] = i;
        }
    }

    cout << cur << endl;
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);
#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}