#include <iostream>
using namespace std;

struct edge {
	int value;
	struct edge *next;
};

class stack {
	edge *cur;

 public:
	stack() {
		cur = NULL;
	}

	void push(int in) {
		if(cur == NULL) {
			edge *tmp = new edge;
			tmp->value = in;
			tmp->next = NULL;
			cur = tmp;
			return;
		}

		edge *_next = new edge;

		_next->value = cur->value;
		_next->next = cur->next;

		cur->value = in;
		cur->next = _next;
	}

	int pop() {
		int out = cur->value;

		if(cur->next != NULL)
			cur = cur->next;
		else
			cur = NULL;

		return out;
	}
};

void solve() {
	stack st;
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		char c;
		cin >> c;
		if(c == '-') {
			cout << st.pop() << endl;
		} else {
			int in;
			cin >> in;
			st.push(in);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 1;

	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);

	while(n--)
		solve();
}
