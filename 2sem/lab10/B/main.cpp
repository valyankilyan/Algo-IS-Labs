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

vector<pair<ld, ld>> g;
vector<bool> was;
multimap<ld, int> m;

ld distance(int a, int b) {
    ld A = (g[a].f - g[b].f) * (g[a].f - g[b].f);
    ld B = (g[a].s - g[b].s) * (g[a].s - g[b].s);
    return sqrt(A + B);
}

void fill_with_distances(int a) {
    was[a] = 1;
    for (int i = 0; i < g.size(); i++) {
        if (!was[i]) {
            m.insert(mp(distance(a, i), i));
        }
    }
}


void solve() {
    m.clear();
    g.clear();
    was.clear();

    int n;
    cin >> n;
    was.resize(n);
    for (int i = 0; i < n; i++) {
        ld x, y;
        cin >> x >> y;
        g.pb(mp(x, y)); 
    }
    fill_with_distances(0);
    long double ans = 0;
    int checked = 1;

    while (!m.empty() && checked < n) {
        auto it = m.begin();
        for (; it != m.end() && was[(*it).s];) {
            m.erase(it++);
        }
        ans+= (*it).f;
        fill_with_distances((*it).s);
        checked++;
        for (; it != m.end() && was[(*it).s];) {
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

    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}