from collections import deque
import sys
from util import check_param

__author__ = 'Bartek'

class AWC:
    def __init__(self, j, k, m, initial):
        self.j = check_param(j, lambda x: x > 0, "J has to be bigger than 0")
        self.k = check_param(k, lambda x: x > j, "K has to be bigger than J")
        self.m = m
        self.initial = check_param(initial, lambda x: len(x) == k, "Have to receive K initial values")

        self.values = deque(self.initial)

        self.carry = 0

        self.current = 0

    def inner_value(self):
        return self.values[self.k - self.j] + self.values[0] + self.carry

    def get_next(self):
        if self.current < self.k:
            self.current += 1
            return self.initial[self.current - 1]
        inner_value = self.inner_value()
        self.carry = 1 if inner_value >= self.m else 0
        val = inner_value % self.m
        self.values.popleft()
        self.values.append(val)
        self.current += 1
        return val

if __name__ == '__main__':
    if len(sys.argv) != 5:
        print('Need 4 arguments, number of samples, j, k and m')
    _, n, j, k, m = sys.argv

    initial = map(int, input().split())
    generator = AWC(j, k, m, initial)
    for x in range(n):
        print(generator.get_next())
