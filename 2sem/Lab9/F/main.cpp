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

vector<vector<int> > gr;
vector<int> color;

void solve() {
    gr.clear();
    color.clear();
    int n, m, S;
    cin >> n >> m >> S;
	S--;
    color.resize(n, 0);
    gr.resize(n);
    vector<bool> is_list(n, 1);

    for (int i = 0; i < m; i++) {
        int fr, to;
        cin >> fr >> to;
        is_list[fr - 1] = 0;
        gr[to - 1].pb(fr - 1);
    }

    queue<int> q;
	// cerr << "is_list: ";
    for (int i = 0; i < n; i++) {
		// cerr << is_list[i] << " ";
        if (is_list[i]) {
            q.push(i);
        }
    }
	// cerr << endl;
    while (!q.empty() && !color[S]) {
        int cur = q.front();
		cerr << cur+1 << " ";
        for (int i = 0; i < gr[cur].size() && !color[S]; i++) {
			if (!color[gr[cur][i]] && gr[cur][i] != S) {
				q.push(gr[cur][i]);
			}
            if (!color[gr[cur][i]] && !color[cur]) {
                color[gr[cur][i]] = 1;                
            }			
        }
        q.pop();
    }
	cerr << endl;
	// for (int i = 0; i < n; i++) {
		// cerr << color[i] << " ";
	// }
	// cerr << endl;
	cout << (color[S] ? "First" : "Second") << " player wins\n";

	cerr << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}