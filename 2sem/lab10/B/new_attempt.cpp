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

vector <pair <int, int>> temp;
// vector<pair<int, int>> fg;
// vector < vector < long double
//                       vector<bool>
//                           was;

ld distance(int a, int b) {
    // cerr << "distance between " << a << " " << temp[a].f << " " 
    // << temp[a].s << ", " << b << " " << temp[b].f << " " << temp[b].s << "  = " <<
    //  sqrt(
    //     (temp[a].f - temp[b].f) * (temp[a].f - temp[b].f) +
    //     (temp[a].s - temp[b].s) * (temp[a].s - temp[b].s)) << endl;
    return sqrt(
        (temp[a].f - temp[b].f) * (temp[a].f - temp[b].f) +
        (temp[a].s - temp[b].s) * (temp[a].s - temp[b].s));
}

void solve() {
    temp.clear();
    temp.resize(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        temp.pb(mp(x, y));
    }

    vector<vector<ld>> g(n);
    vector<bool> was(n);
    vector<int> min_e(n, INF), sel_e(n, -1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i].pb(distance(i, j));
        }
    }
    cerr << endl;
    ld ans = 0;
    min_e[0] = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j)
            if (!was[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        was[v] = true;
        if (sel_e[v] != -1)
            ans+= g[v][sel_e[v]];

        for (int to = 0; to < n; ++to)
            if (g[v][to] < min_e[to]) {
                min_e[to] = g[v][to];
                sel_e[to] = v;
            }
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}