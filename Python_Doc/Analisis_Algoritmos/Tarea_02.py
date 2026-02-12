import numpy as np
import matplotlib.pyplot as plt

def decimal_01(x):
    return 4*x + np.log2(16)*(3 + 2 + 2 + 1)*x + 9*x

def decimal_02(x):
    return np.where(x > 0, 6 * np.log2(x) + 4, 0)

def decimal_03(x):
    return np.where(x > 0, 7 * np.log2(x) + 3, 0)

# Menos puntos = más rápido
x = np.linspace(0.1, 100, 100)


plt.figure(figsize=(10, 6))

plt.plot(x, decimal_01(x), 'r', label='Primero', linewidth=2)
plt.plot(x, decimal_02(x), 'g', label='Segundo', linewidth=2)
plt.plot(x, decimal_03(x), 'b', label='Tercero', linewidth=2)

plt.axhline(y=0, color='k', linestyle='-', linewidth=0.5)
plt.axvline(x=0, color='k', linestyle='-', linewidth=0.5)
plt.grid(True, alpha=0.3)
plt.legend()
plt.xlabel('x')
plt.ylabel('f(x)')

plt.show()