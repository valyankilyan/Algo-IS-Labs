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

struct punit {
    int value;
    int index;

	punit() {
		value = 0;
		index = 0;
	}

	punit (int v, int i) {
		value = v;
		index = i;
	}
};

bool operator<(punit a, punit b) {
    if (a.value != b.value) {
        return a.value < b.value;
    } else {
        return a.index < b.index;
    }
}

bool operator>(punit a, punit b) {
    if (a.value != b.value) {
        return a.value > b.value;
    } else {
        return a.index > b.index;
    }
}

bool operator==(punit a, punit b) {
	return a.value == b.value && a.index == b.index;
}

ostream& operator<<(ostream& out, const punit& p) {
    out << "<" << p.value << ", " << p.index << ">";
	return out;	
}

class pqueue {
   private:
    punit* array;
    int capacity, cur;
    int* queue_index;
    int qicapacity, qicur;

    void decrease_if_needs() {
        if ((cur + 1) * 2 == capacity) {
            capacity /= 2;
            punit* new_array = new punit[capacity];
            for (int i = 0; i < cur; i++) {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
        }
    }

    void increase_if_needs() {
        if (capacity == cur) {
            capacity *= 2;
            punit* new_array = new punit[capacity];
            for (int i = 0; i < cur; i++) {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
        }

        if (qicapacity == qicur) {
            qicapacity *= 2;
            int* new_array = new int[qicapacity];
            for (int i = 0; i < qicur; i++) {
                new_array[i] = queue_index[i];
            }
            delete[] queue_index;
            queue_index = new_array;
        }
    }

    void _swap(int a, int b) {
        if (a == b)
            return;
        swap(array[a], array[b]);
        swap(queue_index[array[a].index], queue_index[array[b].index]);
    }

    void heapify_upwards(int n) {
        if (n == 0)
            return;

        int parent = (n - 1) / 2;
        if (array[parent] > array[n]) {
            _swap(parent, n);
            heapify_upwards(parent);
        }
    }

    void heapify_downwards(int n) {		
        if (cur == 0)
            return;
        int smallest = n;
        for (int i = 1; i <= 2 && n * 2 + i < cur; i++)
            if (array[smallest] > array[n * 2 + i])
                smallest = n * 2 + i;

        if (smallest != n) {
            _swap(n, smallest);
            heapify_downwards(smallest);
        }
    }

   public:
    pqueue() {
        capacity = 1;
        cur = 0;
        array = new punit[capacity];
        qicapacity = 1;
        qicur = 0;
        queue_index = new int[qicapacity];
    }

    void push(int in) {
        increase_if_needs();

        array[cur] = punit(in, qicur);
        queue_index[(qicur++)] = (cur++);

        heapify_upwards(cur - 1);
    }

    void extract_and_print_min() {
        if (cur == 0) {
            cout << "*";
            return;
        }
        _swap(0, (--cur));
        heapify_downwards(0);
        cout << array[cur].value;
        decrease_if_needs();
    }

    void decrease_key(int i, int new_value) {
        array[queue_index[i]].value = new_value;
        heapify_upwards(queue_index[i]);
    }

    void print_variables() {
        cerr << cur << "-" << capacity << " " << qicur << "-" << qicapacity << " -- ";
    }

    void print_array() {
        for (int i = 0; i < cur; i++) {
            cerr << array[i] << " ";
        }
        cerr << endl;
    }
};

void solve() {
    string command;
    pqueue q;

    int pushed = 0;
    vector<int> number_of_push;

    while (cin >> command) {
        number_of_push.pb(-1);

        // cerr << command << " : ";
        // q.print_variables();

        if (command == "push") {
            int in;
            cin >> in;
            q.push(in);
            number_of_push[number_of_push.size() - 1] = (pushed++);
        }

        if (command == "extract-min") {
            q.extract_and_print_min();
            cout << endl;
        }

        if (command == "decrease-key") {
            int key, value;
            cin >> key >> value;
            q.decrease_key(number_of_push[key - 1], value);
        }

        // q.print_array();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tests = 1;

    freopen("priorityqueue.in", "r", stdin);
    freopen("priorityqueue.out", "w", stdout);

    while (tests--)
        solve();
}