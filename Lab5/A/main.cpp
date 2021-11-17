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
    vector<int> parent;
    vector<vector<int> > kids;
    int n;
    cin >> n;

	if (!n) {
		cout << 0 << '\n';
		return;
	}

    parent.resize(n, -1);
    kids.resize(n);
    for (int i = 0; i < n; i++) {
        int v, k[2];
        cin >> v >> k[0] >> k[1];
        for (int j = 0; j < 2; j++) {
            if (k[j]) {
                kids[i].pb(k[j] - 1);
                parent[k[j] - 1] = i;
            }
        }
    }

    int root = 0;
    for (; parent[root] != -1; root++);

    queue<int> q;
    q.push(root);
    int level = 0;
    while (!q.empty()) {
        int last = q.back();
        int cur = -1;
        while (cur != last) {
            cur = q.front();
            q.pop();
            for (int i = 0; i < kids[cur].size(); i++) {
                q.push(kids[cur][i]);
            }
        }
        level++;
    }

    cout << level << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);
#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}
