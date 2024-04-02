
from random import randint

if __name__ == '__main__':
    node = 5000
    edge = 100000
    k = 1
    ran = 100
    print(node, end=' ')
    print(edge, end = ' ')
    print(k)
    for i in range(edge):
        a = randint(1, node)
        print(a, end=' ')
        b = randint(1, node)
        while (b == a):
            b = randint(1, node)
        print(b, end=' ')
        c = randint(1, ran)
        print(c)
