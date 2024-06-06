from pyaccell import Automata
from pyaccell import create_rule
from pyaccell import vec_to_list
from sys import argv
from math import log2

def transition(state, neighbour):
    if (state == 1) and neighbour[1] < 2:
        return 0
    if (state == 1) and neighbour[1] > 3:
        return 0
    if (state == 0) and neighbour[1] == 3:
        return 1

    return state


def random(max):
    states = 2
    rule = create_rule(transition, states)
    ca = Automata(rule, states)
    if (max > ca.sim_width * ca.sim_height):
        ca = Automata(rule, states, max / 1024, 1024)
    ca.run(3)
    output = vec_to_list(ca.output)
    binary = ''.join(map(str, output))
    num = int(binary, 2)
    return (num % max)

if __name__ == '__main__':
    if len(argv) != 2:
        print("Usage: main.py <maximum value>")
        exit(1)
    _max = int(argv[1])
    n = random(_max)
    print(n)
