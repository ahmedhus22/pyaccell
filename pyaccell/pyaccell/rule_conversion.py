from .pyaccell_ext import max_index
from .pyaccell_ext import get_index
from itertools import permutations

# integer partitioning algorithm: https://jeromekelleher.net/generating-integer-partitions.html
def int_partition(n, states):
    a = [0 for i in range(n + 1)]
    k = 1
    y = n - 1
    while k != 0:
        x = a[k - 1] + 1
        k -= 1
        while 2 * x <= y:
            a[k] = x
            y -= x
            k += 1
        l = k + 1
        while x <= y:
            a[k] = x
            a[l] = y
            if (len(a[:k + 2]) <= states):
                yield a[:k + 2]
            x += 1
            y -= 1
        a[k] = x + y
        y = x + y - 1
        if (len(a[:k + 1]) <= states):
            yield a[:k + 1]

# forces list l to given size by filling required no of 0's
def clamp_list(l, size):
    missing_elements = size - len(l)
    to_append = []
    if (missing_elements > 0):
        to_append = [0] * missing_elements
    return l + to_append

def get_neighbours_list(neighbours, states):
    n = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    for state in range(1, states + 1):
        n[state] = neighbours[state - 1]
    return n

def create_rule(transition, states):
    _max_index = max_index(states)
    rule = [0] * (_max_index * states)
    max_sum = 8
    possible_neighbours = map(lambda l: clamp_list(l, states), int_partition(max_sum, states))
    neighbours = set()
    for i in possible_neighbours:
        unique_neighbours = (set(permutations(i)))
        for n in unique_neighbours:
            neighbours.add((n))
    for cur_state in range(states):
        for neighbour in neighbours:
            next_state = transition(cur_state, neighbour)
            index = get_index(get_neighbours_list(neighbour, states), states)
            rule[cur_state * _max_index + index] = next_state

    return rule