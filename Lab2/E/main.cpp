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
 
int qselect(int a[], int l, int r, int aim) {
	int pivot = a[(l+r)/2], i=l, j=r;
	while (i <= j) {
		while (a[i] < pivot) 
			i++;
		while (pivot < a[j])
			j--;
		
		if (i <= j) {
			int save = a[i];
			a[i] = a[j];
			a[j] = save;
			i++;
			j--;
		}
	}
	if (l == r - 1) return a[aim];

	if (l < j && aim <= j) return qselect(a, l, j, aim);
	if (r > i && aim >= i) return qselect(a, i, r, aim);

	return 0;
}

void solve(){
	int n, k; 
	cin >> n >> k;
	int a, b, c;
	int m[n];
	cin >> a >> b >> c >> m[0] >> m[1];
	for(int i = 2; i < n; i++) {
		m[i] = a*m[i-2] + b*m[i-1] + c;
	}

	for (int i = 0; i < n; i++) {
		cerr << m[i] << " ";
	}
	cerr << endl;

	cout << qselect(m, 0, n-1, k-1) << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("kth.in", "r", stdin);
	freopen("kth.out", "w", stdout);

#ifdef LOCAL	
	cin >> tests;
#endif

	while(tests--)
		solve();
}