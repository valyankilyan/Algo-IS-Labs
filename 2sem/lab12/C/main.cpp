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

bitset <100020002> prv;
int cx, cy;

pair <bool, bool> get_prev(int x, int y) {
    pair <bool, bool> ans;
    ans.f = prv[((x)*cy + (y)) * 2];
    ans.s = prv[((x)*cy + (y)) * 2+1];
    return ans;
}

void put_prev(int x, int y, bool a, bool b) {
    prv[((x)*cy + (y)) * 2] = a;
    prv[((x)*cy + (y)) * 2+1] = b;
}

void solve() {
    string s1, s2;
    cin >> s1 >> s2;
    cx = s1.size() + 1;
    cy = s2.size() + 1;
    short int m[s1.size() + 1][s2.size() + 1];
    for (int i = 0; i < s1.size()+1; i++) {
        for (int j = 0; j < s2.size()+1; j++) {
            m[i][j] = 0;
        }
    }

    pair <int, int> mx = mp(0, 0);

    for (int i = 0; i < s1.size(); i++) {
        for (int j = 0; j < s2.size(); j++) {
            if (s1[i] == s2[j]) {
                // cerr << s1[i] << " " << i << " = " << s2[j] << " " << j << endl;
                m[i+1][j+1] = m[i][j] + 1;

                put_prev(i+1, j+1, 1, 1);
                if (m[i+1][j+1] > m[mx.f][mx.s]) {
                    mx.f = i+1;
                    mx.s = j+1;
                }
            } else {
                if (m[i][j+1] > m[i+1][j]) {
                    m[i+1][j+1] = m[i][j+1];
                    put_prev(i+1, j+1, 1, 0);
                } else {
                    m[i+1][j+1] = m[i+1][j];
                    put_prev(i+1, j+1, 0, 1);
                }
            }
        }
    }

    stack<char> ans;

    // for (int i = 0; i < s1.size()+1; i++) {
    //     for (int j = 0; j < s2.size()+1; j++) {
    //         cerr << m[i][j] << " ";
    //     }
    //     cerr << endl;
    // }
    // cerr << endl;
    // cerr << mx.f << " " << mx.s << endl;
    // cerr << m[mx.f][mx.s] << endl;
    // cerr << get_prev(mx.f, mx.s).f << " " << get_prev(mx.f, mx.s).s << endl;

    while (m[mx.f][mx.s]) {
        auto pr = get_prev(mx.f, mx.s);
        // cerr << "hhh " << pr.f << " " << pr.s << " " << mx.f << " " << mx.s << endl;
        if(pr.f && pr.s) {
            ans.push(s1[mx.f-1]);
        }
        mx.f -= pr.f;
        mx.s -= pr.s;
    }

    while(!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;


#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    cin >> tests;
#endif

    while (tests--)
        solve();
}