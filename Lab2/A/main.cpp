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

void merge(int l, int m, int r) {
    int save[r - l + 1];
    for (int i = l; i <= r; i++)
        save[i - l] = v[i];
    int pl = 0, pr = m - l + 1;
    int bl = m - l, br = r - l;
    for (int p = l; pl <= bl || pr <= br; p++) {
        if (pr <= br && (pl > bl || save[pr] <= save[pl])) {
            v[p] = save[pr];
            pr++;
        } else if (pl <= bl && (pr > br || save[pl] <= save[pr])) {
            v[p] = save[pl];
            pl++;
        }
    }
}

void mergeSort(int l, int r) {
    if (l == r) return;
    int m = l + (r - l) / 2;
    mergeSort(l, m);
    mergeSort(m + 1, r);

    merge(l, m, r);
}

void solve() {
    int n;
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    mergeSort(0, n - 1);

    for (int i = 0; i < n; i++)
        cout << v[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--) solve();
}
