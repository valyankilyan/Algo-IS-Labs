#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define mp make_pair
#define ll long long

#define MAXN 200005
#define INF 9223372036854775807
#define MOD 1000000007

void solve() {
    int n, s, f;
    cin >> n >> s >> f;
    s--;
    f--;
    ll weight[n][n];
    ll d[n];
    bool was[n];
    for (int i = 0; i < n; i++) {
        d[i] = INF;
        was[i] = 0;
        for (int j = 0; j < n; j++) {
            cin >> weight[i][j];
        }
    }
    d[s] = 0;

    while (true) {
        ll mn = INF, mn_node = -1;
        for (int i = 0; i < n; i++) {
            if (!was[i] && d[i] < mn) {
                mn = d[i];
                mn_node = i;
            }
        }
        if (mn == INF || mn_node == f) 
            break;
        for (int i = 0; i < n; i++) {
            if (!was[i] && weight[mn_node][i] > 0) {
                d[i] = min(d[i], d[mn_node] + weight[mn_node][i]);
            }
        }
        was[mn_node] = true;
    }

    cout << (d[f] == INF ? -1 : d[f]) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}
