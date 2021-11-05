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
 
int leftSearch(int aim, int a[], int l, int r) {
	if (r - l == 1) {
		return r;
	} 
	int m = (l + r) / 2;
	if (a[m] < aim) {
		return leftSearch(aim, a, m, r);
	} else {
		return leftSearch(aim, a, l, m);
	}
}

int rightSearch(int aim, int a[], int l, int r) {
	if (l >= r - 1) {
		return l;
	}
	int m = (l + r) / 2;
	if (a[m] <= aim) {
		return rightSearch(aim, a, m, r);
	} else {
		return rightSearch(aim, a, l, m);
	}
}

void solve(){
	int n; 
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++) 
		cin >> a[i];
	int m; 
	cin >> m;
	for(int i = 0; i < m; i++) {
		int aim;
		cin >> aim;		
		cout << rightSearch(aim, a, -1, n) << " " << leftSearch(aim, a, -1, n) << endl;
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("binsearch.in", "r", stdin);
	freopen("binsearch.out", "w", stdout);

	while(tests--)
		solve();
}