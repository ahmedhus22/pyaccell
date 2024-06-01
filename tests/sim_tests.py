import pyaccell

rule = [
    0,0,0,1,0,0,0,0,0,
    0,0,1,1,0,0,0,0,0
]
states = 2

ca = pyaccell.Automata(rule, states)
ca.run()