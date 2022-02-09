#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int a[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = -1;
        }
    }

    bool ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];			
            if (a[i][j] && i == j) {
                ans = 0;				
            } else if (a[j][i] != -1 && a[i][j] != a[j][i]) {
                ans = 0;
            }
        }
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