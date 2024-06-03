from pyaccell import create_rule

def transition(state, neighbour):
    '''neighbour is a tuple with state as index'''
    if (state == 1) and neighbour[1] < 2:
        return 0
    if (state == 1) and neighbour[1] > 3:
        return 0
    if (state == 0) and neighbour[1] == 3:
        return 1

    return state

rule = create_rule(transition, 2)
print((rule[:9]))
print(rule[9:])