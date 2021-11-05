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

int rightSearch(int aim, int a[], int l, int r) {
    if (r <= l + 1) {
        return a[r] == aim ? r + 1: -1;
    }
    int m = (l + r) / 2;
    if (a[m] < aim) {
        return rightSearch(aim, a, m, r);
    } else {
        return rightSearch(aim, a, l, m);
    }
}

int leftSearch(int aim, int a[], int l, int r) {
    if (r <= l + 1) {
        return a[l] == aim ? l + 1: -1;
    }
    int m = (l + r) / 2;
    if (a[m] <= aim) {
        return leftSearch(aim, a, m, r);
    } else {
        return leftSearch(aim, a, l, m);
    }
}

void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int aim;
        cin >> aim;
        cout << rightSearch(aim, a, -1, n) << " " << leftSearch(aim, a, -1, n) << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);

    while (tests--)
        solve();
}

// int binarySearch(int arr[], int l, int r, int x) {
//     if (r >= l) {
//         int mid = l + (r - l) / 2;
//         if (arr[mid] == x)
//             return mid;
//         if (arr[mid] > x)
//             return binarySearch(arr, l, mid - 1, x);
//         return binarySearch(arr, mid + 1, r, x);
//     }
//     return -1;
// }

// int binaryRightSearch(int arr[], int l, int r, int aim) {
// 	if (r >= l) {
//         int mid = l + (r - l) / 2;
//         if (arr[mid] == aim)
//             return mid;
//         if (arr[mid] < aim)
// 			return binarySearch(arr, mid + 1, r, aim);
// 		return binarySearch(arr, l, mid - 1, aim);
//     }
//     return -1;
// }