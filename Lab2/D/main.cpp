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
	int n;
	cin >> n;
	int out[n];
	for (int i = 0; i < n; i++) {
		out[i] = i+1;
	}

	for (int b = 2; b < n; b++) {
		int save = out[b];
		out[b] = out[b/2];
		out[b/2] = save;
	}

	for (int i = 0; i < n; i++)
		cout << out[i] << " ";
	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("antiqs.in", "r", stdin);
	freopen("antiqs.out", "w", stdout);

#ifdef LOCAL
	cin >> tests;
#endif

	while(tests--)
		solve();
}