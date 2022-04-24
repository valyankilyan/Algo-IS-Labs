#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define mp make_pair
#define ll long long

#define MAXN 200005
#define INF 1000000009
#define LINF 9223372036854775807
#define MOD 1000000007

void solve() {
    int n, m;
    cin >> n >> m;
    int a[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = INF;
        }
    }

    for (int i = 0; i < m; i++) {
        int f, s, w;
        cin >> f >> s >> w;
        a[f - 1][s - 1] = w;
    }

    for (int i = 0; i < n; i++) {
        for (int u  = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (u == v) 
                    continue;
                a[u][v] = min(a[u][v], a[u][i] + a[i][v]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (a[i][j] == INF ? (i == j ? 0 : -1) : a[i][j]) << " ";
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

    freopen("pathsg.in", "r", stdin);
    freopen("pathsg.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}