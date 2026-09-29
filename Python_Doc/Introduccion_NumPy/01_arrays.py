import numpy as np
from numpy.ma.core import ndim

a = np.array([1,3,4,5,6])

b = np.array(([1,3,4,5,6],
              [22,42,0,213,2]))

c = np.array((["s","2"],
              ["2","d"]))

print(a)
print("Dimension del array: ", ndim(a))

print(b)
print("Dimension del array: ", ndim(b))

print("Tipo de dato del array:", a.dtype)
print(c)
print("Tipo de dato del array:", c.dtype)