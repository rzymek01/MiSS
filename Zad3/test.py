from collections import Counter
from statistics import mean, pvariance
from awc import AWC
from fibadd import FibAdd
from mixedxor import MixedXor

__author__ = 'Bartek'


def get_n_values(generator, count):
    l = [generator.get_next() for _ in range(count)]
    return l[k:]

def print_stats(l):
    c = Counter(l)
    print(c)
    print('mean', mean(l))
    print('variance', pvariance(l))
    print('cycle_len', findCycle(l))

def findCycle(l):
    for x in range(1, len(l)):
        if has_cycle_of_length(l, x):
            return x
    return None

def has_cycle_of_length(l, cycle_length):
    end = len(l)

    for current in range(end):
        if current + cycle_length >= end:
            return True

        if l[current] != l[current+cycle_length]:
            return False


j = 7
seed = list(range(1,11))
k = len(seed)
m = 2**32

for g in (FibAdd,):
    generator = g(j, k, m, seed)
    l = get_n_values(generator, 1000000)
    #print(l)
    print_stats(l)



#generator = MixedXor(2, k, 7, seed, 2, k, 7, seed)
#l = get_n_values(generator, 100000)
#print_stats(l)


