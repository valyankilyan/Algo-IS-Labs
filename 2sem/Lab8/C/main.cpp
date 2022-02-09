#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    int a[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        int fr, to;
        cin >> fr >> to;
        ans = a[fr - 1][to - 1] || a[to - 1][fr - 1] || ans;
        a[fr - 1][to - 1] = 1;
    }

    cout << (ans ? "YES" : "NO") << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie();

    int tests = 1;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}