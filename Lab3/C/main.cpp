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

void countSort(string arr[], int size, int d) {
    int count[26] = {};

    for (int i = 0; i < size; i++) {
        count[arr[i][d] - 'a']++;
    }
    for (int i = 1; i < 26; i++) {
        count[i] += count[i - 1];
    }

    string out[size];
    for (int i = size - 1; i >= 0; i--) {
        count[arr[i][d] - 'a']--;
        out[(count[arr[i][d] - 'a'])] = arr[i];
    }

    for (int i = 0; i < size; i++) {
		arr[i] = out[i];
	}
}

void radixSort(string arr[], int size, int m, int op) {
    for (int i = m - 1; i >= m - op; i--) {
        countSort(arr, size, i);
    }
}

void solve() {	
    int n, m, k;
    cin >> n >> m >> k;
    string arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    radixSort(arr, n, m, k);

    for (int i = 0; i < n; i++)
        cout << arr[i] << endl;
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}