# Pyaccell
A GPU Accelerated Cellular Automata Library.
Allows you to create totalistic Cellular Automatas, 
by specifiying rules of the CA.

# Installation
*Recommended Python version: 3.10 and Requires: OpenGL Core profile supported GPU*
```
pip install pyaccell
```

# Building the project from source
```
git clone --recurse-submodules https://github.com/ahmedhus22/pyaccell.git
pip install .
```
To Build wheel:
```
pip wheel .
```

# Pyaccell Documentation
Import the package as:
```
import pyaccell
```
or
```
import pyaccell as CA
```
you can now use ```>>>help(pyaccell)``` to get a brief overview of the package.

## Automata Class
This class defines methods and attributes required to create and use cellular automatas.

### Constructors:
```
CA.Automata(rule, states)
CA.Automata(rule, states, sim_width, sim_height)
```
where rule is a 1D list that defines Automatas transitions for all states and neighbours.
states is the number of states in Automata. width and height defines size of automata.

To create a rule define a transition function: 
```
def transition(state: int, neighbour: tuple):
    ...
```
state is current state and neighbour represents, neighbour count of each state.
for example: neighbour[1] = count of neighbours having state 1.

Now use the transistion function to creat rule array:
```
rule = CA.create_rule(transition, states)
```

Alternatively, you can define a rule array yourself:

The Rows represent index, use ```get_index(neighbour: list, states: int)``` function.
For 2 state CA index is just the count of neighbours having state 1.

Columns represent states, thus [state] [index] gives next state.

### Class Attributes:
- sim_width: int (default = 800)
- sim_height: int (default = 600)

Sets the width and height of the framebuffer to handle simulation, it defines the number of cells.

- input: list

It has to be of size sim_width * sim_height, otherwise the Automat runs with random inputs. It contains the initial state of automata as a list of ints.
By default it runs with random input.

- output: UIntVector

It is read only, it gives the output of cellular automata, if it is run for set number of iterations.
To read output in python list use ```vec_to_list(output)``` function.

### Class Methods:
A run() method is provied, It has 2 overloads.
- run(): Automata runs indefinitely with given input and rules in a window.
- run(iterations: int): Automata runs for set iterations and then halts. The Output is stored is output attribute of the class.

## Useful Helper Functions:
- get_index(neighbour: list, states: int) -> index: int
- vec_to_list(output) -> list

**Note** : python 3.10 is required for this function.
- create_rule(transition, states) -> list

# References
- Rule Representation of multistate Cellular Automata using combinatorial indices:
[Benjamin Mastripolito's Article](https://medium.com/@bpmw/multi-state-cellular-automata-in-webgl-2bff79bf08fb)
