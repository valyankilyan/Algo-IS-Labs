#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define mp make_pair
#define ll long long
#define ld long double

#define MAXN 200005
#define INF 1000000009
#define MOD 1000000007

vector<vector<pair<int, int>>> g;
vector<bool> was;
multimap<int, pair<int, int>> m;

void fill_with_distances(int a) {
    was[a] = 1;
    for (int i = 0; i < g[a].size(); i++) {
        if (!was[g[a][i].f]) {
            m.insert(mp(g[a][i].s, mp(a, g[a][i].f)));
        }
    }
}

void solve() {
    m.clear();
    g.clear();
    was.clear();

    int n, M;
    cin >> n >> M;
    was.resize(n);
    g.resize(n);
    for (int i = 0; i < M; i++) {
        int fr, to, value;
        cin >> fr >> to >> value;
        g[fr-1].pb(mp(to-1, value));
        g[to-1].pb(mp(fr-1, value));
    }
    fill_with_distances(0);
    long double ans = 0;
    int checked = 1;
    while (!m.empty() && checked < n) {
        auto it = m.begin();
        ans += (*it).f;
        fill_with_distances((*it).s.s);
        checked++;
        for (; it != m.end() && was[(*it).s.s];) {
            m.erase(it++);
        }
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("spantree3.in", "r", stdin);
    freopen("spantree3.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}