import pyaccell

rule = [
    0,0,0,1,0,0,0,0,0,
    0,0,1,1,0,0,0,0,0
]
states = 2

pyaccell.run_ca(rule, 2)