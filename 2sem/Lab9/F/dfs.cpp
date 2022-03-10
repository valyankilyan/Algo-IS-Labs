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

vector<vector<int> > g;
vector<bool> is_list;
vector<char> color;

bool dfs(int v) {
    if (is_list[v]) {    
        color[v] = 0;    
        return 0;
    }
    bool ans = 0;
    for (int i = 0; i < g[v].size() && !ans; i++) {
        ans = !(color[g[v][i]] == -1 ? dfs(g[v][i]) : color[g[v][i]]);
    }    
    color[v] = ans;    
    return ans;
}

void solve() {
    g.clear();
    is_list.clear();
    color.clear();    
    int n, m, S;
    cin >> n >> m >> S;
	S--;    
    g.resize(n);
    is_list.resize(n, 1);
    color.resize(n, -1);

    for (int i = 0; i < m; i++) {
        int fr, to; 
        cin >> fr >> to;
        g[fr-1].pb(to-1);
        is_list[fr-1] = 0;
    }

    cout << (dfs(S) ? "First" : "Second") << " player wins\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}