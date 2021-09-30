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
	int M; 
	cin >> M;
	pair < long double, int > a[M];
	for(int i = 0; i < M; i++){
		long double c; 
		cin >> c; 
		a[i] = mp(c, i+1);
	}
	
	for(int i = 0; i < M-1; i++){
		for(int j = i+1; j < M; j++){
			if(a[i].f > a[j].f){
				auto save = a[j];
				a[j] = a[i];
				a[i] = save;
			}
		}
	}

	
	cout << a[0].s << " " << a[(M-1)/2].s << " " << a[M-1].s << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("sortland.in", "r", stdin);
	freopen("sortland.out", "w", stdout);

#ifdef LOCAL
	bool a;
	a = freopen("in.data", "r", stdin);
	a = freopen("out.data", "w", stdout);
	cin >> tests;
#endif

	while(tests--)
		solve();
}