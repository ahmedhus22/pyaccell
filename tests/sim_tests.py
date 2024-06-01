import pyaccell

rule = [
    0,0,0,1,0,0,0,0,0,
    0,0,1,1,0,0,0,0,0
]
states = 2
output = []
ca = pyaccell.Automata(rule, states)
ca.run(10)
print(pyaccell.vec_to_list(ca.output))