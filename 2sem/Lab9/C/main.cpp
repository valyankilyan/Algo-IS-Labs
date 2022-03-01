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
 
vector <vector <int> > v;
vector <int> part;

void solve(){
	v.clear();
	part.clear();
	int n, m;
	cin >> n >> m;
	v.resize(n);
	part.resize(n, -1);
	for (int i = 0; i < m; i++) {
		int fr, to;
		cin >> fr >> to;
		v[fr-1].pb(to-1);
		v[to-1].pb(fr-1);
	}

	bool ans = 1;
	// cerr << "n = " << n << endl;
	for (int i = 0; i < n && ans; i++) {
	// for (int i = 0; i < n; i++) {
		if (part[i] != -1) {
			continue;
		}
		// cerr << "OK! " << i << "\n";
		queue <int> q;
		part[i] = 1;
		q.push(i);

		while (!q.empty() && ans) {		
		// while (!q.empty()) {		
			int cur = q.front();
			cerr << cur+1 << " -> ";
			q.pop();
			for (int j = 0; j < v[cur].size(); j++) {
				if (part[v[cur][j]] == -1) {
					part[v[cur][j]] = !part[cur];
					q.push(v[cur][j]);
					// cerr << " {push " << v[cur][j] + 1 << "} ";
				} else if (part[v[cur][j]] == part[cur]) {
					ans = 0;
					break;
				}
			}
		}
	}
	cerr << endl;

	// for (int i = 0; i < n; i++) {
	// 	cout << i+1 << ": " << part[i] << endl;
	// }

	// for (int i = 0; i < n; i++) {
	// 	cerr << i+1 << " " << was[i] << endl;
	// }

	cout << (ans ? "YES\n" : "NO\n");
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("bipartite.in", "r", stdin);
	freopen("bipartite.out", "w", stdout);
#ifdef LOCAL
	cin >> tests;
#endif

	while(tests--)
		solve();
}