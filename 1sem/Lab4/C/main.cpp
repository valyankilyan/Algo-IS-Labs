#include <iostream>
using namespace std;

struct edge {
	char value;
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

	char top() {
		return cur->value;
	}

	char pop() {
		char out = cur->value;

		if(cur->next != NULL)
			cur = cur->next;
		else
			cur = NULL;

		return out;
	}
};

bool isLeftBracket(char b) {
	return (b == '(') || (b == '[');
}

bool isFit(char l, char r) {
	return (l == '[' && r == ']') || (l == '(' && r == ')');
}

void solve() {
    string s;    

    while (cin >> s) {
        stack st;
		bool ans = 1;
        for (int i = 0; ans && i < s.size(); i++) {
            if (isLeftBracket(s[i])) {
				st.push(s[i]);
			} else if (st.empty() || !isFit(st.top(), s[i])) {
				ans = 0;
			} else {
				st.pop();
			}
        }
		cout << (ans && st.empty() ? "YES" : "NO") << endl;
    }

}

int main() {    
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 1;

    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);

    while (n--)
        solve();
}
