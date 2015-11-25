import sys
from awc import AWC
from fibadd import FibAdd

__author__ = 'Bartek'

class MixedXor:
    def __init__(self, j, k, m, initial, j2, k2, m2, initial2):
        self.first = AWC(j, k, m, initial)
        self.second = FibAdd(j2, k2, m2, initial2)

    def get_next(self):
        return self.first.get_next() ^ self.second.get_next()

def run():
    if len(sys.argv) != 8:
        print('Need 7 arguments, number of samples, j, k and m, and j2, k2, and m2')
        return
    n, j, k, m, j2, k2, m2 = map(int, sys.argv[1:])

    initials = map(int, raw_input().split())
    initial = initials[:k]
    initial2 = initials[k:]

    generator = MixedXor(j, k, m, initial, j2, k2, m2, initial2)
    for x in range(n):
        print(generator.get_next())


if __name__ == '__main__':
    run()
