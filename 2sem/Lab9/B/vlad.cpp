#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 1e6;
int n, m, v1, v2, finish, k = 0;
vector<int> color, points;
bool cycle = false;
vector<vector<int>> g;

void dfs(int v) {
    color[v] = 1;
    for (int i = 0; i < g[v].size(); i++) {
        if (color[g[v][i]] == 1) {
            cycle = true;
            finish = g[v][i];
            points[k] = v;
            k++;
            return;
        }
        if (color[g[v][i]] == 0) {
            dfs(g[v][i]);
        }
        if (cycle) {
            break;
        }
    }
    if (cycle) {
        points[k] = v;
        k++;
        if (v == finish)
            cycle = false;
    }
    color[v] = 2;
}

int solve() {
    g.clear();
    color.clear();
    points.clear();
    finish = 0;
    k = 0;
    cin >> n >> m;
    g.resize(n+1);
    color.resize(n+1);
    points.resize(n+1);
    for (int i = 0; i < m; i++) {
        cin >> v1 >> v2;
        g[v1].push_back(v2);
    }
    for (int i = 1; i <= n && !cycle; i++) {
        if (color[i] == 0) {
            dfs(i);
        }
    }
    if (k > 0) {
        cout << "YES" << '\n';
        for (int i = 0; i < k; i++) {
            cout << points[i] << ' ';
        }
    } else {
        cout << "NO";
    }
    cout << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}