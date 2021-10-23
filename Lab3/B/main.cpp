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

void heapify(int arr[], int n, int i) {
	int largest = i;
	int r = i * 2 + 1, l = r + 1;
	if (r < n && arr[largest] < arr[r]) 
		largest = r;
	if (l < n && arr[largest] < arr[l])
		largest = l;
	
	if (largest != i) {
		swap(arr[largest], arr[i]);
		heapify(arr, n, largest);
	}
}

void heap_sort(int arr[], int n) {
	for (int i = n/2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	
	for (int i = n-1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

void solve(){
	int n;
	cin >> n;
	int a[n];
	for(int i = 0; i < n; i++) 
		cin >> a[i];
	heap_sort(a, n);

	for(int i = 0; i < n; i++) 
		cout << a[i] << " ";
	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);

#ifdef LOCAL	
	cin >> tests;
#endif

	while(tests--)
		solve();
}