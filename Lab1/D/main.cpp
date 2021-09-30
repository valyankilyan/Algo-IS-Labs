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
	int a[n];
	for(int i = 0; i < n; i++)
		cin >> a[i];

	sort(a, a+n);
	
	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("smallsort.in", "r", stdin);
	freopen("smallsort.out", "w", stdout);

#ifdef LOCAL
	bool a;
	a = freopen("in.data", "r", stdin);
	a = freopen("out.data", "w", stdout);
	cin >> tests;
#endif

	while(tests--)
		solve();
}