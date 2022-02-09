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

class Maze {
    int n, m;
    bool** field;
    pair<int, int> start, end;

   public:
    Maze(int n_in, int m_in) {
        n = n_in;
        m = m_in;
        field = new bool*[n];
        for (int i = 0; i < n; i++) {
            field[i] = new bool[m];
        }
        start = mp(-1, -1);
        end = mp(-1, -1);
    }

    void read() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char c;
                cin >> c;
                field[i][j] = c != '#';
                if (c == 'S') {
                    start = mp(i, j);
                }
                if (c == 'T') {
                    end = mp(i, j);
                }
            }
        }
    }

    vector<char> find_way() {
        vector<vector<vector<char>>> way(n);
        vector<vector<bool>> was(n);
        for (int i = 0; i < n; i++) {
            was[i].resize(m, 0);
            way[i].resize(m);
        }
        queue<pair<int, int>> q;
        q.push(start);
        was[start.f][start.s] = 1;

        while (!q.empty()) {
            int x = q.front().f, y = q.front().s;
            if (q.front() == end) {
                return way[x][y];
            }
            vector<char> cur_way = way[x][y];
            if (is_allowed(x - 1, y) && !was[x - 1][y]) {
                way[x - 1][y] = cur_way;
                way[x - 1][y].pb('U');
                was[x - 1][y] = 1;
                q.push(mp(x - 1, y));
            }
            if (is_allowed(x + 1, y) && !was[x + 1][y]) {
                way[x + 1][y] = cur_way;
                way[x + 1][y].pb('D');
                was[x + 1][y] = 1;
                q.push(mp(x + 1, y));
            }
            if (is_allowed(x, y - 1) && !was[x][y - 1]) {
                way[x][y - 1] = cur_way;
                way[x][y - 1].pb('L');
                was[x][y - 1] = 1;
                q.push(mp(x, y - 1));
            }
            if (is_allowed(x, y + 1) && !was[x][y + 1]) {
                way[x][y + 1] = cur_way;
                way[x][y + 1].pb('R');
                was[x][y + 1] = 1;
                q.push(mp(x, y + 1));
            }
            q.pop();
        }

        return way[start.f][start.s];
    }

   private:
    bool is_allowed(int i, int j) {
        return i >= 0 && i < n && j >= 0 && j < m && field[i][j];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Maze maze = Maze(n, m);
    maze.read();
    vector<char> ans = maze.find_way();
    if (ans.size() == 0) {
        cout << -1 << endl;
    } else {
        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie();

    int tests = 1;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#ifdef LOCAL
    cin >> tests;
#endif

    while (tests--)
        solve();
}