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

vector < vector <int> > m;
int h, w;

void solve(){
	cin >> h >> w;
	m.resize(h);
	for(int i = 0; i < h; i++){
		m[i].resize(w);
		for(int j = 0; j < w; j++)
			cin >> m[i][j];			
	}

	queue < pair < int, int> > q;
	int mx[h][w] = {};
	mx[h-1][0] = m[h-1][0];
	q.push(mp(h-1, 0));
	while(!q.empty()){
		int x = q.front().f;
		int y = q.front().s;
		q.pop();
		
		// if(x == 0 && y == w-1)
		// 	cout << mx[x][y] << " " << m[x][y] << endl;

		if(x != 0 && mx[x-1][y] < mx[x][y] + m[x-1][y]){
			mx[x-1][y] = mx[x][y] + m[x-1][y];
			q.push(mp(x-1, y));
		}

		if(y != w-1 && mx[x][y+1] < mx[x][y] + m[x][y+1]){
			mx[x][y+1] = mx[x][y] + m[x][y+1];
			q.push(mp(x, y+1));
		}
	}

	cout << mx[0][w-1] << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("turtle.in", "r", stdin);
	freopen("turtle.out", "w", stdout);
#ifdef LOCAL
	bool a;
	a = freopen("in.data", "r", stdin);
	a = freopen("out.data", "w", stdout);
	cin >> tests;
#endif

	while(tests--)
		solve();
}