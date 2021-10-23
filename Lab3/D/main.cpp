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

class pqueue {
   private:
    pair<int, int>* array;
    int capacity, cur;
    int* queue_index;
    int qicapacity, qicur;

    void decrease_if_needs() {
        if ((cur + 1) * 2 == capacity) {
            capacity /= 2;
            pair<int, int> new_array[capacity];
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
            pair<int, int>* new_array = new pair<int, int>[capacity];
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
		// if (a == b)
		// 	return;
        swap(array[a], array[b]);
        swap(queue_index[array[a].s], queue_index[array[b].s]);
    }

    void heapify_upwards(int n) {
        if (n == 0)
            return;

        int parent = (n - 1) / 2;
        if (array[parent].f > array[n].f) {
            _swap(parent, n);
            heapify_upwards(parent);
        }
    }

    void heapify_downwards(int n) {
		// if (n == cur)
		// 	return;
        int smallest = n;
        for (int i = 1; i <= 2 && n * 2 + i < cur; i++)
            if (array[n].f > array[n * 2 + i].f)
                smallest = n * 2 + i;

		cerr << "hd = " << (smallest != n) << " ";

        if (smallest != n) {
            _swap(n, smallest);
            heapify_downwards(smallest);
        }
    }

   public:
    pqueue() {
        capacity = 1;
        cur = 0;
        array = new pair<int, int>[capacity];
        qicapacity = 1;
        qicur = 0;
        queue_index = new int[qicapacity];
    }

    void push(int in) {
        increase_if_needs();
        print_variables();

        array[cur] = mp(in, qicur);
        queue_index[(qicur++)] = (cur++);

        heapify_upwards(cur - 1);
    }

    void extract_and_print_min() {
		print_variables();
        if (cur == 0) {
            cout << "*";
            return;
        }

        _swap(0, (--cur));
        heapify_downwards(0);
        cout << array[cur].f;
        decrease_if_needs();
		cerr << "okay " << cur << " ";
    }

    void decrease_key(int i, int new_value) {
        array[queue_index[i]].f = new_value;
        heapify_upwards(queue_index[i]);
    }

    void print_variables() {
        cerr << cur << "-" << capacity << " " << qicur << "-" << qicapacity << " -- ";
    }

    void print_array() {
        for (int i = 0; i < cur; i++) {
            cerr << "<" << array[i].f << ", " << array[i].s << "> ";
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

		cerr << command << " : ";

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
			cerr << "number_of_push = " << number_of_push[key-1] << " | ";
            q.decrease_key(number_of_push[key-1], value);
        }

        q.print_array();
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