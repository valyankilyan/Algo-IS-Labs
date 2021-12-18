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

class LinkedList;

struct Node {
    string key;    
    Node* next;
	LinkedList* list;
};

struct LinkedNode {
    LinkedNode *prev, *next;
    string value;
};

class LinkedList {
    LinkedNode *head, *tail;
    int size;

   public:
    LinkedList() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

	int getSize(){
		return size;
	}

    void push_back(string str) {
        if (getNode(str) != NULL) {
            return;
        }
        LinkedNode* temp = new LinkedNode;
        size++;
        temp->value = str;
        temp->next = NULL;
        if (head == NULL) {
            temp->prev = NULL;
            head = temp;
            tail = temp;
            return;
        }
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
        return;
    }

    void remove(string str) {
		LinkedNode* node = getNode(str);
		if (node == NULL) {
			return;
		}
		del(node);
		size--;
    }
    
    void print() {
        LinkedNode* cur = head;
        while (cur != NULL) {
            cout << cur->value << " ";
            cur = cur->next;
        }
        // cout << endl;
    }

   private:

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

	LinkedNode* getNode(string str) {
		LinkedNode *cur = head;
		while(cur != NULL && cur->value != str) {
			cur = cur->next;
		}
		return cur;
	}
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
            c->list->push_back(value);
            return;
        }

        size_t hash = get_hash(key);
        if (array[hash] == NULL) {
            array[hash] = new Node;
            array[hash]->key = key;
			array[hash]->list = new LinkedList;
            array[hash]->list->push_back(value);
            array[hash]->next = NULL;
            return;
        }
        Node* cur = array[hash];
        while (cur->next != NULL && cur->next->key != key) {
            cur = cur->next;
        }
        Node* temp = new Node;
        temp->key = key;
		temp->list = new LinkedList;
        temp->list->push_back(value);
        temp->next = NULL;
        cur->next = temp;
        return;
    }

    bool exists(string key) {
        return getNode(key) == NULL ? 0 : 1;
    }

    LinkedList* get(string key) {
        Node* nd = getNode(key);
        if (nd == NULL) {
            return NULL;
        } else {
            return nd->list;
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
        node->list->remove(value);
        if (node->list->getSize() == 0) {
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
        // cerr << s << " " << x << endl;
        if (s == "put") {
            string y;
            cin >> y;
            mp.push(x, y);
        }
        if (s == "get") {
            LinkedList* list = mp.get(x);
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
