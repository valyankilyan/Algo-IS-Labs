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

#define MAP_SIZE 100001
#define SET_SIZE 101

struct setNode;

struct LinkedNode {
    LinkedNode *prev, *next;
    setNode* snode;
};

struct setNode {
    string value;
    setNode* next;
    LinkedNode* ln;
};

class LinkedList {
    LinkedNode *head, *tail;

   public:
    int size;

    LinkedList() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    LinkedNode* push_back(setNode* snode) {
        LinkedNode* temp = new LinkedNode;
        size++;
        temp->snode = snode;
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

    void del(LinkedNode* lnode) {
        size--;
        if (tail == lnode) {
            tail = lnode->prev;
        }
        if (head == lnode) {
            head = lnode->next;
        }
        if (lnode->prev != NULL) {
            lnode->prev->next = lnode->next;
        }
        if (lnode->next != NULL) {
            lnode->next->prev = lnode->prev;
        }
        delete lnode;
    }

    setNode* getPrev(LinkedNode* node) {
        if (node->prev == NULL) {
            return NULL;
        }
        return node->prev->snode;
    }

    setNode* getNext(LinkedNode* node) {
        if (node->next == NULL) {
            return NULL;
        }
        return node->next->snode;
    }

    void print() {
        LinkedNode* cur = head;
        cout << size << " ";
        while (cur != NULL) {
            cout << cur->snode->value << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

class Set {
    setNode** array;

   public:
    LinkedList* list;

    Set() {
        array = new setNode*[SET_SIZE];
        list = new LinkedList();
        for (int i = 0; i < SET_SIZE; i++) {
            array[i] = 0;
        }
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
            array[hash]->ln = list->push_back(array[hash]);
            return;
        }
        setNode* cur = array[hash];
        while (cur->next != NULL && cur->next->value != value) {
            cur = cur->next;
        }
        setNode* temp = new setNode;
        temp->value = value;
        temp->next = NULL;
        temp->ln = list->push_back(temp);
        cur->next = temp;
        return;
    }

    bool exists(string value) {
        return getNode(value) == NULL ? 0 : 1;
    }

    void remove(string value) {
        if (!exists(value)) {
            return;
        }
        size_t hash = get_hash(value);
        setNode* cur = array[hash];
        if (cur->value == value) {
            setNode* temp = cur->next;
            list->del(cur->ln);
            delete cur;
            array[hash] = temp;
            return;
        }
        while (cur->next->value != value) {
            cur = cur->next;
        }

        setNode* del = cur->next;
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
        return out % SET_SIZE;
    }

    setNode* getNode(string value) {
        size_t hash = get_hash(value);
        if (array[hash] == NULL) {
            return NULL;
        }
        setNode* cur = array[hash];
        while (cur != NULL && cur->value != value) {
            cur = cur->next;
        }
        if (cur != NULL && cur->value == value) {
            return cur;
        }
        return NULL;
    }
};

struct Node {
    Node* next;
    string key;
    Set* st;
};

class Map {
    Node** array;

   public:
    Map() {
        array = new Node*[MAP_SIZE];
        for (int i = 0; i < MAP_SIZE; i++) {
            array[i] = 0;
        }
    }

    void push(string key, string value) {
        Node* node = getNode(key);
        if (node != NULL) {
            node->st->push(value);
            return;
        }

        size_t hash = get_hash(key);
        Node* temp = new Node;
        temp->next = NULL;
        temp->st = new Set();
        temp->key = key;
        temp->st->push(value);

        if (array[hash] == NULL) {
            array[hash] = temp;
            return;
        }
        Node* cur = array[hash];
        while (cur->next != NULL && cur->next->key != key) {
            cur = cur->next;
        }
        cur->next = temp;
    }

    void remove(string key, string value) {
        if (!exists(key)) {
            return;
        }
        Node* node = getNode(key);
        node->st->remove(value);
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

    void print(string key) {
        Node* node = getNode(key);
        if (node == NULL) {
            cout << 0 << endl;
            return;
        }
        node->st->list->print();
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
    }

    bool exists(string key) {
        Node* node = getNode(key);
        return node == NULL ? 0 : 1;
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
    Map* mp = new Map();
    while (cin >> s) {
        string x;
        cin >> x;
        if (s == "put") {
            string y;
            cin >> y;
            mp->push(x, y);
        }
        if (s == "delete") {
            string y;
            cin >> y;
            mp->remove(x, y);
        }

        if (s == "deleteall") {
            mp->removeAll(x);
        }
        if (s == "get") {
            mp->print(x);
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
