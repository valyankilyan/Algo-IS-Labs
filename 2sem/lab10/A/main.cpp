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
    vector<int> g(n);
    for (int i = 0; i < 2 * m; i++) {
        int v;
        cin >> v;
        g[v - 1]++;
    }

    for (int i = 0; i < n; i++) {
        cout << g[i] << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}