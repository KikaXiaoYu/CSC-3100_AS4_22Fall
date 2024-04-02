
from random import randint

if __name__ == '__main__':
    node = 50
    print(node, end=' ')
    print(node*5, end = ' ')
    print(0)
    for i in range(node*5):
        a = randint(1, node)
        print(a, end=' ')
        b = randint(1, node)
        while (b == a):
            b = randint(1, node)
        print(b, end=' ')
        c = randint(1, 3)
        print(c)
