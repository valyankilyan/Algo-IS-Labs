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

vector<pair<int, int> > kids;
vector<int> value;

bool dfs(int k, int mn, int mx) {
	if (k == -1) 
		return 1;
	bool ans = 1;
	if (kids[k].f != -1) {
		ans = ans && (value[kids[k].f] > mn);
		ans = ans && (value[kids[k].f] < value[k]);		
	}
	if (kids[k].s != -1) {
		ans = ans && (value[kids[k].s] > value[k]);
		ans = ans && (value[kids[k].s] < mx);
	}

	return ans && dfs(kids[k].f, mn, value[k]) && dfs(kids[k].s, value[k], mx);
}

void solve() {
    int n;
    cin >> n;    

    if (!n) {
        cout << "YES" << '\n';
        return;
    }

	value.resize(n);
    kids.resize(n);
    for (int i = 0; i < n; i++) {
        int v, k[2];
        cin >> v >> k[0] >> k[1];
        kids[i] = mp(k[0] - 1, k[1] - 1);
        value[i] = v;
    }

	bool ans = dfs(0, -INF, INF);

    cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}
