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

#define SET_SIZE 1000001

struct Node {
    int value;
    Node* next;
};

class Set {
    Node** array;

   public:
    Set() {
        array = new Node*[SET_SIZE];
    }

    void push(int value) {
        if (exists(value)) {
            return;
        }
        size_t hash = get_hash(value);
        if (array[hash] == NULL) {
            array[hash] = new Node;
            array[hash]->value = value;
            array[hash]->next = NULL;
            return;
        }
        Node* cur = array[hash];
        while (cur->next != NULL && cur->next->value != value) {
            cur = cur->next;
        }
        Node* temp = new Node;
        temp->value = value;
        temp->next = NULL;
        cur->next = temp;
        return;
    }

    bool exists(int value) {
        size_t hash = get_hash(value);
        if (array[hash] == NULL) {
            return 0;
        }
        Node* cur = array[hash];
        while (cur != NULL && cur->value != value) {
            cur = cur->next;
        }
        if (cur != NULL && cur->value == value) {
            return 1;
        }
        return 0;
    }

    void remove(int value) {
        if (!exists(value)) {
            return;
        }
        size_t hash = get_hash(value);
        Node* cur = array[hash];
        if (cur->value == value) {
            Node* temp = cur->next;
            delete cur;
            array[hash] = temp;
            return;
        }
        while (cur->next->value != value) {
            cur = cur->next;
        }

        Node* del = cur->next;
        cur->next = del->next;
        delete del;
    }

   private:
    size_t get_hash(int value) {        
        return abs(value % SET_SIZE);
    }
};

void solve() {
    string s;
    Set st;
    while (cin >> s) {
        int x;
        cin >> x;        
        if (s == "insert") {
            st.push(x);
        }
        if (s == "exists") {
            cout << (st.exists(x) ? "true" : "false") << "\n";
        }
        if (s == "delete") {
            st.remove(x);
        }
    }    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);

    while (tests--)
        solve();
}
