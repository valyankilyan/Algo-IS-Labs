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
	int a[n+1];
	a[0] = -2*INF;	
	bool isHeap = 1;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] < a[i / 2])
			isHeap = 0;
	}
	cout << (isHeap ? "YES" : "NO") << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("isheap.in", "r", stdin);
	freopen("isheap.out", "w", stdout);
#ifdef LOCAL	
	cin >> tests;
#endif

	while(tests--)
		solve();
}
