#include <bits/stdc++.h>
#include <time.h>
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

int qselect(int l, int r, int aim) {

    if (l == r && l == aim)
        return v[aim];
    int pivot = v[rand() % (r - l + 1) + l];    
    int i = l, j = r;
    while (i <= j) {
        while (v[i] < pivot)
            i++;
        while (v[j] > pivot)
            j--;
        if (i <= j) {
            int save = v[i];
            v[i] = v[j];
            v[j] = save;
            i++;
            j--;
        }
    }

    if (l <= aim && aim <= j)
        return qselect(l, j, aim);
    else if (i <= aim && aim <= r)
        return qselect(i, r, aim);
    else if (i == aim + 1 && j == aim - 1)
        return qselect(j + 1, i - 1, aim);

    return -1;
}

void solve() {
    int n, k;
    cin >> n >> k;
    int a, b, c;
    v.resize(n);
    cin >> a >> b >> c >> v[0] >> v[1];
    for (int i = 2; i < n; i++) {
        v[i] = a * v[i - 2] + b * v[i - 1] + c;
    }    

    cout << qselect(0, n - 1, k - 1) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    srand((unsigned)time(NULL));

    int tests = 1;

    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}
