#include <iostream>
#include <map>
using namespace std;

#define MOD 65536

class vector {
  string *array;
  int capacity, cur;

 public:
  vector() {
    array = new string[1];
    capacity = 1;
    cur = 0;
  }

  void push(string in) {
    if (cur == capacity) {  // Если вектор уже совсем вырос
      capacity *= 2;  // Переселяем его в массив по-больше
      string *new_array = new string[capacity];
      for (int i = 0; i < cur; i++) new_array[i] = array[i];
      delete[] array;
      array = new_array;
    }

    array[cur] = in;
    cur++;
  }

  string pop() {
    if (cur == 0)  // Если вектор закончился
      return "";

    cur--;

    string out = array[cur];

    if (cur < capacity / 2 &&
        cur != 0) {  // Если вектор уже меньше, чем половина занимаемой памяти.
      capacity /= 2;  // Переселяем его в массив по-меньше
      string *new_array = new string[capacity];
      for (int i = 0; i <= cur; i++) new_array[i] = array[i];
      delete[] array;
      array = new_array;
    }

    return out;
  }

  int size() { return cur; }

  int getCapacity() { return capacity; }

  string get(int i) { return array[i]; }
};

struct unit {
  int value;
  struct unit *next;

  unit() {}

  unit(int v) {
    value = v;
    next = NULL;
  }

  ~unit() {}
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

    if (head == tail) {
      unit *new_tail = new unit;
      new_tail->value = in;
      new_tail->next = NULL;
      tail = new_tail;

      unit *new_head = new unit;
      new_head->value = head->value;
      new_head->next = tail;
      head = new_head;
      return;
    }

    unit *new_tail = new unit;
    new_tail->value = in;
    new_tail->next = NULL;
    tail->next = new_tail;
    tail = new_tail;
  }

  int pop() {
    if (head == NULL) return 0;

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

queue q;
int a['z' - 'a' + 1];

void input(string s) {
  int in = 0, st = 1;
  for (int i = s.size() - 1; i >= 0; i--) {
    in += (s[i] - '0') * st;
    st *= 10;
  }
  q.push(in % MOD);
}

void _plus() { q.push((q.pop() + q.pop()) % MOD); }

void _minus() { q.push((q.pop() - q.pop()) % MOD); }

void multiply() { q.push((q.pop() * q.pop()) % MOD); }

void div() {
  int aa = q.pop(), bb = q.pop();
  if (bb == 0 || aa == 0) {
    aa = 0;
    bb = 1;
  }
  aa /= bb;
  aa %= MOD;
  q.push(aa);
}

void mod() {
  int aa = q.pop(), bb = q.pop();
  if (bb == 0 || aa == 0) {
    aa = 0;
    bb = 1;
  }
  aa %= bb;
  aa %= MOD;
  q.push(aa);
}

void reg_get(char c) { q.push(a[c - 'a'] % MOD); }

void reg_put(char c) { a[c - 'a'] = q.pop(); }

void print() { cout << q.pop() << (char)10; }

void print(char c) { cout << a[c - 'a'] << (char)10; }

void cprint() { cout << (char)q.pop(); }

void cprint(char c) { cout << (char)a[c - 'a']; }

bool isZero(char c) { return a[c - 'a'] == 0; }

bool isEqual(char c1, char c2) { return a[c1 - 'a'] == a[c2 - 'a']; }

bool isGreater(char c1, char c2) { return a[c1 - 'a'] > a[c2 - 'a']; }

void solve() {
  bool prog_end = 0;
  int line = 0;
  vector command;
  map<string, int> labels;
  string s;

  while (cin >> s) {
    command.push(s);
    if (s[0] == ':') labels[s.substr(1)] = command.size() - 1;
  }

  while (!prog_end) {
    s = command.get(line);

    if (s[0] >= '0' && s[0] <= '9') {
      input(s);
    } else {
      switch (s[0]) {
        case '+':
          _plus();
          break;
        case '-':
          _minus();
          break;
        case '*':
          multiply();
          break;
        case '/':
          div();
          break;
        case '%':
          mod();
          break;
        case '>':
          reg_put(s[1]);
          break;
        case '<':
          reg_get(s[1]);
          break;
        case 'P':
          if (s.size() == 1)
            print();
          else
            print(s[1]);
          break;
        case 'C':
          if (s.size() == 1)
            cprint();
          else
            cprint(s[1]);
          break;
        case ':':
          break;
        case 'J':
          line = labels[s.substr(1)];
          break;
        case 'Z':
          line = (isZero(s[1]) ? labels[s.substr(2)] : line);
          break;
        case 'E':
          line = (isEqual(s[1], s[2]) ? labels[s.substr(3)] : line);
          break;
        case 'G':
          line = (isGreater(s[1], s[2]) ? labels[s.substr(3)] : line);
          break;
        case 'Q':
          prog_end = 1;
          break;
        default:
          break;
      }
    }
    line++;
    if (line >= command.size()) prog_end = 1;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n = 1;

  freopen("quack.in", "r", stdin);
  freopen("quack.out", "w", stdout);
#ifdef LOCAL
  // cin >> n;
#endif

  while (n--) solve();
}
