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

struct Node;

struct LinkedNode {
    LinkedNode *prev, *next;
    Node* mn;
};

struct Node {
    string key;
    string value;
    Node* next;
    LinkedNode* ln;
};

class LinkedList {
    LinkedNode *head, *tail;

   public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    LinkedNode* push_back(Node* mn) {
        LinkedNode* temp = new LinkedNode;
        temp->mn = mn;
        temp->next = NULL;
        if (head == NULL) {
            temp->prev = NULL;
            head = temp;
            tail = temp;
            return temp;
        }
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
        return temp;
    }

    void del(LinkedNode* node) {
        if (tail == node) {
            tail = node->prev;
        }
        if (head == node) {
            head = node->next;
        }
        if (node->prev != NULL) {
            node->prev->next = node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        delete node;
    }

    Node* getPrev(LinkedNode* node) {
        // cout << "prev: " << node->prev << " " << node->prev->mn
        if (node->prev == NULL) {
            return NULL;
        }
        return node->prev->mn;
    }

    Node* getNext(LinkedNode* node) {
        // cout << node->next << " " << node->next->mn  << " " << node->next->mn->key << endl;
        if (node->next == NULL) {
            return NULL;
        }
        return node->next->mn;
    }

    void print() {
        LinkedNode* cur = head;
        while (cur != NULL) {
            cout << cur->mn->key << " <-> ";
            cur = cur->next;
        }
        cout << endl;
    }
};

class Map {
    Node** array;
    LinkedList* list;

   public:
    Map() {
        array = new Node*[MAP_SIZE];
        list = new LinkedList();
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
            array[hash]->ln = list->push_back(array[hash]);
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
        temp->ln = list->push_back(temp);
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

    string prev(string key) {
        Node* node = getNode(key);
        if (node == NULL) {
            return "none";
        }
        Node* prev = list->getPrev(node->ln);
        if (prev == NULL) {
            return "none";
        }
        return prev->value;
    }

    string next(string key) {
        Node* node = getNode(key);
        if (node == NULL) {
            return "none";
        }
        Node* next = list->getNext(node->ln);
        if (next == NULL) {
            return "none";
        }
        return next->value;
    }

    void remove(string key) {
        if (!exists(key)) {
            return;
        }
        size_t hash = get_hash(key);
        Node* cur = array[hash];
        if (cur->key == key) {
            Node* temp = cur->next;
            list->del(cur->ln);
            delete cur;
            array[hash] = temp;
            return;
        }
        while (cur->next->key != key) {
            cur = cur->next;
        }

        Node* del = cur->next;
        cur->next = del->next;
        list->del(del->ln);
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

    // cerr << '\n';
    while (cin >> s) {
        string x;
        cin >> x;
        // cerr << s << " " << x << endl;
        if (s == "put") {
            string y;
            cin >> y;
            mp.push(x, y);
        }
        if (s == "get") {
            cout << mp.get(x) << '\n';
            // cerr << s << " " << x << " = " << mp.get(x) << '\n';
        }
        if (s == "prev") {
            cout << mp.prev(x) << '\n';
            // cerr << s << " " << x << " = " << mp.prev(x) << '\n';
        }
        if (s == "next") {
            cout << mp.next(x) << '\n';
            // cerr << s << " " << x << " = " << mp.next(x) << '\n';
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

    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);

    while (tests--)
        solve();
}
