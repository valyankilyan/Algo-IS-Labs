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
    string str;
    cin >> str;
    vector <int> pi(str.size());
    for (int i = 1; i < str.size(); i++) {
        int j = pi[i-1];
        while (j > 0 && str[i] != str[j]) j = pi[j-1];
        j+= str[i] == str[j];
        pi[i] = j;
    }
    for (int i = 0; i < str.size(); i++) {
        cout << pi[i] << " ";
    }
    cout << endl;

    // var str string
	// fmt.Fscanf(reader, "%s ", &str)
	// pi := make([]int, len(str))
	// for i := 1; i < len(str); i++ {
	// 	j := pi[i-1]
	// 	for j > 0 && str[i] != str[j] {
	// 		j = pi[j-1]
	// 	}
	// 	if str[i] == str[j] {
	// 		j++
	// 	}
	// 	pi[i] = j
	// }
	// for _, p := range pi {
	// 	fmt.Fprintf(writer, "%d ", p)
	// }
	// fmt.Fprintf(writer, "\n")
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while(tests--)
        solve();
}