REALLY_BIG_NUMBER = 18446744073709551615

class Equation():
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __str__(self):
        return f'{self.a}ai {"+" if self.b >= 0 else "-"} {abs(self.b)}'
    
    def __repr__(self):
        return self.__str__()
    
    def __add__(self, other):
        a = self.a + other.a
        b = self.b + other.b
        return Equation(a, b)
    
    def __sub__(self, other):
        a = self.a - other.a
        b = self.b - other.b
        return Equation(a, b)
    
    def mult(self, k: int):
        a = self.a * k
        b = self.b * k
        return Equation(a, b)

def get_reversed_equations(n):
    n-= 2
    a = [
    Equation(1, 0),
    Equation(2, 2)
    ]
    while n:
        a.append((a[-1] + Equation(0, 1)).mult(2) - a[-2])
        n-= 1
    return a

def get_equations(n):
    n-= 2
    a = [
        Equation(1, 0),
        Equation(0, 0)
    ]
    while n: 
        a.append((a[-1] + Equation(0, 1)).mult(2) - a[-2])
        n-= 1
    return a

def get_ai(h, eq):
    return (h - eq.b) / eq.a

def get_height(ai, eq):
    return ai * eq.a + eq.b

def get_final_height(n, h, zero_pointer, reqs, eqs):
    ai = get_ai(h, reqs[zero_pointer - 1])
    if is_cells_near_zero_negative(ai):
        return get_height(ai, eqs[n - zero_pointer])
    else:
        return REALLY_BIG_NUMBER if ai < 0 else -REALLY_BIG_NUMBER

def is_cells_near_zero_negative(ai):
    return (2 - ai) >= 0 and ai >= 0
    
n, h = open("garland.in", "r").read().replace('\n', '').split(' ')
n = int(n)
h = float(h)

reqs = get_reversed_equations(n)
eqs = get_equations(n)

# for i in range(1, n - 1):
#     print(i, get_final_height(n, h, i, reqs, eqs))
    
l = 1
r = n-2
while l < r:
    mid = (l+r)//2
    res = get_final_height(n, h, mid, reqs, eqs)
    if res == -REALLY_BIG_NUMBER:
        l = mid
    elif res == REALLY_BIG_NUMBER:
        r = mid
    else:
        r = mid
        l = mid
        
        
open('garland.out', 'w').write(str(get_final_height(n, h, l, reqs, eqs)))