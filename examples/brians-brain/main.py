'''
An Example Implementation of Brian's Brain Cellular Automata
'''
from pyaccell import Automata
from pyaccell import create_rule

def transition(state, neighbour):
    '''neighbour is a tuple with state as index'''
    off = 0
    dying = 1
    on = 2
    if (state == on):
        return dying
    if (state == dying):
        return off
    if (state == off) and neighbour[on] == 2:
        return on

    return state

states = 3
rule = create_rule(transition, states)

ca = Automata(rule, states, 2048, 2048)
ca.run()