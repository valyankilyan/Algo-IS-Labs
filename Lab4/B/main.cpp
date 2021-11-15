#include <iostream>
using namespace std;

struct unit {
    int value;
    struct unit *next;
};

class queue {
    unit *head, *tail;

   public:
    queue() {
        head = NULL;
        tail = NULL;
    }

    void push(int in) {
        if (head == NULL && tail == NULL) {
            unit *tmp = new unit;
            tmp->value = in;
            tmp->next = NULL;
            head = tmp;
            tail = tmp;
            return;
        }

        // if (head == tail) {
        //     unit *new_tail = new unit;
        //     new_tail->value = in;
        //     new_tail->next = NULL;
        //     tail = new_tail;

        //     unit *new_head = new unit;
        //     new_head->value = head->value;
        //     new_head->next = tail;
        //     head = new_head;
        //     return;
        // }

        unit *new_tail = new unit;
        new_tail->value = in;
        new_tail->next = NULL;
        tail->next = new_tail;
        tail = new_tail;
    }

    int pop() {
        if (head == NULL)
            return -__INT32_MAX__;
        int out = head->value;

        if (head->next != NULL) {
            head = head->next;
        } else {
            head = NULL;
            tail = NULL;
        }
        return out;
    }
};

void solve() {
    queue q;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '-') {
            cout << q.pop() << endl;
        } else {
            int in;
            cin >> in;
            q.push(in);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 1;

    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);

    while (n--) solve();
}
