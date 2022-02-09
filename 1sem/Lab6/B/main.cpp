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

#define MAP_SIZE 1000001

struct Node {
    string key;
    string value;
    Node* next;
};

class Map {
    Node** array;

   public:
    Map() {
        array = new Node*[MAP_SIZE];
    }

    void push(string key, string value) {
		Node* c = getNode(key);
        if (c != NULL) {
			c->value = value;
			return;
        }

        size_t hash = get_hash(key);
        if (array[hash] == NULL) {
            array[hash] = new Node;
            array[hash]->key = key;
			array[hash]->value = value;
            array[hash]->next = NULL;
            return;
        }
        Node* cur = array[hash];
        while (cur->next != NULL && cur->next->key != key) {
            cur = cur->next;
        }
        Node* temp = new Node;
        temp->key = key;
		temp->value = value;
        temp->next = NULL;
        cur->next = temp;
        return;
    }

    bool exists(string key) {
		return getNode(key) == NULL ? 0 : 1;
    }

	string get(string key) {
		Node* nd = getNode(key);
		if (nd == NULL) {
			return "none";
		} else {
			return nd->value;
		}
	}

    void remove(string key) {
        if (!exists(key)) {
            return;
        }
        size_t hash = get_hash(key);
        Node* cur = array[hash];
        if (cur->key == key) {
            Node* temp = cur->next;
            delete cur;
            array[hash] = temp;
            return;
        }
        while (cur->next->key != key) {
            cur = cur->next;
        }

        Node* del = cur->next;
        cur->next = del->next;
        delete del;
    }

   private:
    size_t get_hash(string key) {
        size_t out = 0;
        int st = 1;
        for (int i = 0; i < key.size() && out < MAP_SIZE; i++) {
            out += st * (key[i] - 'a');
			st*= 'z' - 'a';
        }
		return out % MAP_SIZE;
        // return abs(key % MAP_SIZE);
    }

    Node* getNode(string key) {
        size_t hash = get_hash(key);
        if (array[hash] == NULL) {
            return NULL;
        }
        Node* cur = array[hash];
        while (cur != NULL && cur->key != key) {
            cur = cur->next;
        }
        if (cur != NULL && cur->key == key) {
            return cur;
        }
        return NULL;
    }
};

void solve() {
    string s;
    Map mp;
    while (cin >> s) {
        string x;
        cin >> x;
        if (s == "put") {
            string y;
            cin >> y;
            mp.push(x, y);
        }
        if (s == "get") {
            cout << mp.get(x) << '\n';
        }
        if (s == "delete") {
            mp.remove(x);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);

    while (tests--)
        solve();
}
