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

vector<int> v;

ll merge(int l, int m, int r) {
	ll inv = 0;
    int save[r - l + 1];
    for (int i = l; i <= r; i++)
        save[i - l] = v[i];

    int sl = 0, el = m - l;
    int sr = m - l + 1, er = r - l;
    for (int p = l, pl = sl, pr = sr; p <= r; p++) {
        if (pl <= el && (pr > er || save[pl] <= save[pr])) {
            v[p] = save[pl];
            pl++;
            inv += pr - sr;
        } else if (pr <= er && (pl > pr || save[pr] <= save[pl])) {
            v[p] = save[pr];
            pr++;
        }
    }
	return inv;
}

ll getInversions(int l, int r) {
    if (r == l)
        return 0;
    int m = (r + l) / 2;

    ll a = getInversions(l, m);
    ll b = getInversions(m + 1, r);
    ll mer = merge(l, m, r);

    return a + b + mer;
}

void solve() {    
    int n;
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    ll inv = getInversions(0, n - 1);

    cout << inv << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("inversions.in", "r", stdin);
    freopen("inversions.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}