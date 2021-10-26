#include <iostream>
using namespace std;

#define pb push_back
#define f first
#define s second
#define mp make_pair
#define ll long long
 
#define MAXN 200005
#define INF 1000000009
#define MOD 1000000007
 
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

	bool empty() {
		return cur == NULL;
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

	int top() {
		return cur->value;
	}

	int pop() {
		int out = cur->value;

		if(cur->next != NULL)
			cur = cur->next;
		else
			cur = NULL;

		// cerr << "st.pop() = " << out << endl;
		return out;
	}
};

void solve(){
	char c;
	stack st;
	while (cin >> c) {
		if (c == '*') {			
			st.push(st.pop() * st.pop());
		} else if (c == '-') {
			int a = st.pop();
			st.push(st.pop() - a);
		} else if (c == '+') {
			st.push(st.pop() + st.pop());
		} else {
			st.push(c - '0');
		}
	}

	cout << st.pop() << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int tests = 1;

	freopen("postfix.in", "r", stdin);
	freopen("postfix.out", "w", stdout);

	while(tests--)
		solve();
}