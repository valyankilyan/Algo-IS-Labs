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

vector<vector<int>> g;
vector<int> was;
int last_color;

void dfs(int v) {
	was[v] = last_color;
	for (int i = 0; i < g[v].size(); i++) {
		if (!was[g[v][i]]) {
			dfs(g[v][i]);
		}
	}
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.clear();
    was.clear();
    g.resize(n);
    was.resize(n);
    last_color = 0;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
		a--;
		b--;
        g[a].pb(b);
        g[b].pb(a);
    }	

    for (int i = 0; i < n; i++) {
		if (!was[i]) {
			last_color++;
			dfs(i);
		}
    }

	cout << last_color << endl;
	for (int i = 0; i < n; i++) {
		cout << was[i] << " ";
	}
	cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie();

    int tests = 1;

    freopen("components.out", "w", stdout);
    freopen("components.in", "r", stdin);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}