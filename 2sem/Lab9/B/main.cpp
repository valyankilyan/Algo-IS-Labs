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
 
vector <vector<int>> v;
vector <int> was;
stack <int> path;
bool cycle;


int dfs(int cur) {
	was[cur] = 1;
	for (int i = 0; i < v[cur].size(); i++) {
		if (was[v[cur][i]] == 1) {
			path.push(cur);
			return v[cur][i] + 1;
		}
		if (!was[v[cur][i]]) {
			int ans = dfs(v[cur][i]);
			if (ans == -1) {
				return -1;
			}
			if (ans > 0) {
				path.push(cur);
				if (ans == cur + 1) {
					return -1;
				} else {
					return ans;
				}
			}
		}
	}
	was[cur] = 2;
	return 0;
}

void solve(){
	v.clear();
	was.clear();
	cycle = 0;
	int n, m;
	cin >> n >> m;
	v.resize(n);
	was.resize(n);

	for (int i = 0; i < m; i++) {
		int fr, to;
		cin >> fr >> to;
		v[fr-1].pb(to-1);
	}
	
	for (int i = 0; i < n; i++) {
		if (!was[i]) {
			if (dfs(i) == -1) {
				cout << "YES\n";
				while(!path.empty()) {
					cout << path.top() + 1 << " ";
					path.pop();
				}
				cout << endl;
				return;
			}
		}
	}
	cout << "NO\n";
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("cycle.in", "r", stdin);
	freopen("cycle.out", "w", stdout);

#ifdef LOCAL
	cin >> tests;
#endif

	while(tests--)
		solve();
}