import numpy as np
import matplotlib.pyplot as plt

class Perceptron:
  # lesrning rate = eta
  def __init__(self, n_inputs, learning_rate=0.1) :
    self.w = -1  + 2 * np.random.rand(n_inputs)
    self.b = -1 + 2 * np.random.rand()
    self.eta = learning_rate

  def predict(self, X):
    p = X.shape[1]
    y_est = np.zeros(p)
    for i in range(p):
      z = np.dot(self.w, X[:,i]) + self.b
      if z >= 0:
        y_est[i] = 1
      else:
        y_est[i] = 0

    return y_est

  def fit (self,X,Y, epochs = 1000):
    p = X.shape[1]
    for _ in range(epochs):
      for i in range(p):
        y_est = self.predict(X[:, i].reshape(-1, 1))
        self.w += self.eta * (Y[i] - y_est) * X[:, i]
        self.b += self.eta * (Y[i] - y_est)


def draw_2d_perceptron (model) :
  w1, w2, b = model.w[0], model.w[1], model.b
  plt.plot([-2,2], [(1/w2)*( -w1*(-2)-b), (1/w2)*(-w1* (2)-b)])

# AND
#X = np.array([[0,1,0,1],[0,0,1,1]])
#Y = np.array( [0,0,0,1])


# OR
#X = np.array([[0,1,0,1],[0,0,1,1]])
#Y = np.array( [0,1,1,1] )

# XOR
X = np.array([[0,1,0,1],[0,0,1,1]])
Y = np.array( [0,1,1,0] )

model = Perceptron(2)
model.fit(X,Y)
print(model.predict(X))

# dibujo
p = X.shape[1]
for i in range(p):
  if Y[i] == 0:
    plt.plot(X[0,i], X[1,i], "or")
  else:
    plt.plot(X[0,i], X[1,i], 'ob')

plt. title('Perceptron')
plt.grid(True)
plt.xlim([-2,2])
plt.ylim([-2,2])
plt.xlabel(r'$x_1$')
plt.ylabel(r'$x_2$')
draw_2d_perceptron (model)
plt.show()