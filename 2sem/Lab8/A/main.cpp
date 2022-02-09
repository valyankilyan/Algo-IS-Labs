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

void solve() {
    int n, m;
    cin >> n >> m;
    bool a[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int fr, to;
        cin >> fr >> to;
        a[fr - 1][to - 1] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

#ifdef LOCAL    
    cin >> tests;
#endif
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    while (tests--)
        solve();
}
