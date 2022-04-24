#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define mp make_pair
#define ll long long

#define MAXN 200005
#define INF 1000000009
#define LINF 10000000000000016
#define MOD 1000000007

struct edge {
    int a, b, cost;
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<edge> e(m);
    for (int i = 0; i < m; i++) {
        cin >> e[i].a >> e[i].b >> e[i].cost;
        e[i].a--;
        e[i].b--;
    }
    vector<ll> d(n, LINF);
    d[0] = 0;
    while (true) {
        bool any = false;
        for (int j = 0; j < m; j++) {
            if (d[e[j].a] < LINF) {
                if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    any = true;
                }
            }
            if (d[e[j].b] < LINF) {    
                if (d[e[j].a] > d[e[j].b] + e[j].cost) {
                    d[e[j].a] = d[e[j].b] + e[j].cost;
                    any = true;
                }
            }
        }
        if (!any) break;
    }

    for (int i = 0; i < n; i++) {
        cout << (d[i] == LINF ? -1 : d[i]) << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("pathbgep.in", "r", stdin);
    freopen("pathbgep.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}