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

int sr = 0;
vector <int> v;

void qsort(int l, int r) {
    int pivot = v[(l+r)/2], i = l, j = r;
    cerr << pivot << " -> ";
    while (i <= j) {
        while (v[i] < pivot) {
            i++;
            sr++;
        }
        while (pivot < v[j]) {
            j--;
            sr++;
        }
        sr+=2;
        if (i <= j) {
            int save = v[i]; 
            v[i] = v[j];
            v[j] = save;
            i++;
            j--;
        }
    }
    cout << v[i-1] << " " << v[j+1] << " " << i << " " << j << endl;
    if (l < j) qsort(l, j);
    if (i < r) qsort(i, r);
}

void qsort_pivotout(int l, int r) {
    int pivot = v[(l+r)/2], i = l, j = r;
    cout << pivot << " -> ";
    while (i <= j) {
        while (v[i] < pivot) {
            i++;
            sr++;
        }
        while (pivot < v[j]) {
            j--;
            sr++;
        }
        sr+=2;
        if (i <= j) {
            int save = v[i]; 
            v[i] = v[j];
            v[j] = save;
            i++;
            j--;
        }
    }
    if (l < j) qsort(l, j);
    if (r > i) qsort(i, r);
}


vector <pair <int, vector <int>>> variants;
vector <vector <int> > vectors;
void vecgen(set <int> allow, vector <int> cur, int last) {
    cur.pb(last);
    allow.erase(last);
    if(allow.empty()) {
        vectors.pb(cur);
    }
    for (auto &a: allow) {        
        vecgen(allow, cur, a);
    }
}

void sort_variants() {
    for(int i = 0; i < variants.size(); i++) {
        for (int j = i+1; j < variants.size(); j++) {
            if (variants[i].f > variants[j].f) {
                auto save = variants[i];
                variants[i] = variants[j];
                variants[j] = save;
            }
        }
    }
}

void check_sr(int n) {
    vectors.clear();
    vector <int> cur;
    set <int> allow;
    for (int i = 1; i <= n; i++) 
        allow.insert(i);
    for (int i = 1; i <= n; i++)
        vecgen(allow, cur, i);

    for (auto &ve: vectors) {
        v = ve;
        sr = 0;
        qsort(0, v.size() - 1);
        for (auto &i: ve) {
            cout << i << " ";
        }
        cout << "| " << sr << endl;
        variants.pb(mp(sr, ve));
    }
    sort_variants();
    for (auto &var: variants) {
        cout << var.f << " | ";
        for (auto &i: var.s) {
            cout << i << " ";
        }
        cout << " | ";
        v = var.s;
        qsort_pivotout(0, v.size()-1);
        cout << endl;
    }
}

void solve(){
    sr = 0;
	int n;
	cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    qsort(0, n-1);

    // for (int i = 0; i < n; i++) 
    //     cout << v[i] << " ";
    // cout << '\n';
    cerr << "| " << sr << '\n';
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("qsort.in", "r", stdin);
	freopen("qsort.out", "w", stdout);

#ifdef LOCAL
	cin >> tests;
#endif
	while(tests--)
		solve();

    check_sr(5);
}