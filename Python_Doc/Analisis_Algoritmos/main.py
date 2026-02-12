import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return 2*x**5 + 7*x**4 + 1/x + 2*np.log(np.abs(x)) + 16*x + 9

def f_prima(x):
    return 10*x**4 + 28*x**3 - 1/x**2 + 2/x + 16

def f_biprima(x):
    return 40*x**3 + 84*x**2 + 2/x**3 - 2/x**2

x_neg = np.arange(-10, -0.1, 0.1)
x_pos = np.arange(0.1, 10, 0.1)

plt.figure()
# f(x)
plt.plot(x_neg, f(x_neg), 'r', label='f(x)')
plt.plot(x_pos, f(x_pos), 'r')

# f'(x)
plt.plot(x_neg, f_prima(x_neg), 'b--', label="f'(x)")
plt.plot(x_pos, f_prima(x_pos), 'b--')

# f''(x)
plt.plot(x_neg, f_biprima(x_neg), 'g:', label="f''(x)")
plt.plot(x_pos, f_biprima(x_pos), 'g:')

plt.grid()
plt.legend()
plt.show()