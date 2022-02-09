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

void solve(){
	int n, m; 
	cin >> n >> m;
	vector <vector <int>> g(n);
	for (int i = 0; i < m; i++) {
		int a, b; 
		cin >> a >> b;
		g[--a].pb(--b);
		g[b].pb(a);
	}

	queue <int> q;
	vector <int> ans(n, -1);	
	ans[0] = 0;
	q.push(0);
	while (!q.empty()) {						
		for (auto &x: g[q.front()]) {
			if (ans[x] == -1) {				
				q.push(x);
				ans[x] = ans[q.front()] + 1;
			}
		}		
		q.pop();
	}
	cerr << endl;

	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie();

    int tests = 1;

    freopen("pathbge1.in", "r", stdin);
    freopen("pathbge1.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}