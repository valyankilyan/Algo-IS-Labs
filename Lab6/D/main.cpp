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

#define MAP_SIZE 10001
#define SET_SIZE 10001

class setNode;
class Set;

struct Node {
    string key;    
    Node* next;
	setNode* set;
};

struct setNode {
    string value;
    Node* next;
};

class Set {
    setNode** array;
    int size;

   public:
    Set() {
        array = new setNode*[SET_SIZE];
        size = 0;
    }

    void push(string value) {
        if (exists(value)) {
            return;
        }
        size_t hash = get_hash(value);
        if (array[hash] == NULL) {
            array[hash] = new setNode;
            array[hash]->value = value;
            array[hash]->next = NULL;
            return;
        }
        Node* cur = array[hash];
        while (cur->next != NULL && cur->next->value != value) {
            cur = cur->next;
        }
        Node* temp = new setNode;
        temp->value = value;
        temp->next = NULL;
        cur->next = temp;
        return;
    }

    bool exists(string value) {
        size_t hash = get_hash(value);
        if (array[hash] == NULL) {
            return 0;
        }
        setNode* cur = array[hash];
        while (cur != NULL && cur->value != value) {
            cur = cur->next;
        }
        if (cur != NULL && cur->value == value) {
            return 1;
        }
        return 0;
    }

    void remove(string value) {
        if (!exists(value)) {
            return;
        }
        size_t hash = get_hash(value);
        setNode* cur = array[hash];
        if (cur->value == value) {
            setNode* temp = cur->next;
            delete cur;
            array[hash] = temp;
            return;
        }
        while (cur->next->value != value) {
            cur = cur->next;
        }

        setNode* del = cur->next;
        cur->next = del->next;
        delete del;
    }

   private:
    size_t get_hash(string key) {
        size_t out = 0;
        int st = 1;
        for (int i = 0; i < key.size() && out < MAP_SIZE; i++) {
            out += st * (key[i] - 'a');
            st *= 'z' - 'a';
        }
        return out % MAP_SIZE;
        // return abs(key % MAP_SIZE);
    }
}



class Map {
    Node** array;

   public:
    Map() {
        array = new Node*[MAP_SIZE];		
    }

    void push(string key, string value) {
        Node* c = getNode(key);
        if (c != NULL) {
            c->set->push(value);
            return;
        }

        size_t hash = get_hash(key);
        if (array[hash] == NULL) {
            array[hash] = new Node;
            array[hash]->key = key;
			array[hash]->set = new Set;
            array[hash]->set->push(value);
            array[hash]->next = NULL;
            return;
        }
        Node* cur = array[hash];
        while (cur->next != NULL && cur->next->key != key) {
            cur = cur->next;
        }
        Node* temp = new Node;
        temp->key = key;
		temp->set = new Set;
        temp->set->push(value);
        temp->next = NULL;
        cur->next = temp;
        return;
    }

    bool exists(string key) {
        return getNode(key) == NULL ? 0 : 1;
    }

    Set* get(string key) {
        Node* nd = getNode(key);
        if (nd == NULL) {
            return NULL;
        } else {
            return nd->set;
        }
    }

    void removeAll(string key) {
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

    void remove(string key, string value) {
        if (!exists(key)) {
            return;
        }
        Node* node = getNode(key);
        node->set->remove(value);
        if (node->set->getSize() == 0) {
            removeAll(key);
        }
    }

   private:
    size_t get_hash(string key) {
        size_t out = 0;
        int st = 1;
        for (int i = 0; i < key.size() && out < MAP_SIZE; i++) {
            out += st * (key[i] - 'a');
            st *= 'z' - 'a';
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
        cerr << s << " " << x << endl;
        if (s == "put") {
            string y;
            cin >> y;
            mp.push(x, y);
        }
        if (s == "get") {
            Set* list = mp.get(x);
            if (list == NULL) {
                cout << 0;
            } else {
                cout << list->getSize() << " ";
                list->print();
            }
			cout << '\n';
        }
        if (s == "deleteall") {
            mp.removeAll(x);
        }
        if (s == "delete") {
            string y;
            cin >> y;
            mp.remove(x, y);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);

    while (tests--)
        solve();
}
