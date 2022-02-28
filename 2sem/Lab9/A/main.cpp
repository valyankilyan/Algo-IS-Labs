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

vector<vector<int>> v;
vector<int> was;
stack<int> st;
bool possibility;

void dfs(int cur) {
    was[cur] = 1;
    for (int i = 0; i < v[cur].size(); i++) {
        if (was[v[cur][i]] == 1) {
            possibility = 0;
            return;
        }
        if (!was[v[cur][i]]) {
            dfs(v[cur][i]);
        }
    }
    st.push(cur);
    was[cur] = 2;
}

void solve() {
    was.clear();
    v.clear();
    possibility = 1;
    int n, m;
    cin >> n >> m;
    v.resize(n);
    was.resize(n);
    for (int i = 0; i < m; i++) {
        int fr, to;
        cin >> fr >> to;
        v[fr - 1].pb(to - 1);
    }
    for (int i = 0; i < n && possibility; i++) {
        if (!was[i]) {
            dfs(i);
        }
    }

    if (!possibility) {
        cout << -1 << endl;
        return;
    }

    while (!st.empty()) {
        cout << st.top() + 1 << " ";
        st.pop();
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}
