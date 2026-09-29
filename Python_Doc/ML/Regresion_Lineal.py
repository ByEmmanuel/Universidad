import numpy as np
import matplotlib.pyplot as plt


# =================================================================
# 1. CREACIÓN DEL DATASET (Generación de datos sintéticos)
# =================================================================
def generate_data(n_samples=100):
    """
    Genera un dataset para regresión lineal: y = 3x + 5 + ruido
    """
    np.random.seed(42)
    X = 2 * np.random.rand(n_samples, 1)  # Valores de x entre 0 y 2
    y = 3 * X + 5 + np.random.randn(n_samples, 1) * 0.5  # y = 3x + 5 + ruido gaussiano
    return X, y


# =================================================================
# 2. IMPLEMENTACIÓN DE LA RED NEURONAL (Desde cero)
# =================================================================
class NeuralNetworkRegression:
    def __init__(self, input_size, hidden_size, output_size, learning_rate=0.01):
        # Inicialización de pesos y sesgos (He Initialization para ReLU)
        self.W1 = np.random.randn(input_size, hidden_size) * np.sqrt(2. / input_size)
        self.b1 = np.zeros((1, hidden_size))
        self.W2 = np.random.randn(hidden_size, output_size) * np.sqrt(2. / hidden_size)
        self.b2 = np.zeros((1, output_size))
        self.lr = learning_rate

    def relu(self, z):
        return np.maximum(0, z)

    def relu_derivative(self, z):
        return (z > 0).astype(float)

    def forward(self, X):
        """
        Propagación hacia adelante
        """
        self.z1 = np.dot(X, self.W1) + self.b1
        self.a1 = self.relu(self.z1)
        self.z2 = np.dot(self.a1, self.W2) + self.b2
        self.a2 = self.z2  # Para regresión, la salida es lineal (sin activación)
        return self.a2

    def backward(self, X, y, output):
        """
        Backpropagation (Cálculo de gradientes)
        """
        m = X.shape[0]  # Número de muestras

        # Error en la salida (Derivada de MSE respecto a la salida)
        # MSE = (1/m) * sum((y_pred - y)^2) -> d/dy_pred = 2/m * (y_pred - y)
        dz2 = 2 * (output - y) / m
        dW2 = np.dot(self.a1.T, dz2)
        db2 = np.sum(dz2, axis=0, keepdims=True)

        # Error en la capa oculta (Backpropagating el error)
        da1 = np.dot(dz2, self.W2.T)
        dz1 = da1 * self.relu_derivative(self.z1)
        dW1 = np.dot(X.T, dz1)
        db1 = np.sum(dz1, axis=0, keepdims=True)

        # Actualización de pesos (Descenso de Gradiente)
        self.W2 -= self.lr * dW2
        self.b2 -= self.lr * db2
        self.W1 -= self.lr * dW1
        self.b1 -= self.lr * db1

    def train(self, X, y, epochs=1000):
        losses = []
        for i in range(epochs):
            output = self.forward(X)
            loss = np.mean((output - y) ** 2)  # Mean Squared Error
            self.backward(X, y, output)
            losses.append(loss)

            if i % 100 == 0:
                print(f"Época {i}/{epochs} - Pérdida (MSE): {loss:.4f}")
        return losses


# =================================================================
# 3. EJECUCIÓN DEL PROGRAMA
# =================================================================

# 1. Preparar datos
X, y = generate_data(100)

# 2. Configurar la red:
# Entrada: 1 (x) | Oculta: 4 neuronas | Salida: 1 (y)
nn = NeuralNetworkRegression(input_size=1, hidden_size=4, output_size=1, learning_rate=0.05)

# 3. Entrenar
print("Iniciando entrenamiento...")
history = nn.train(X, y, epochs=1000)

# 4. Predicción para visualización
X_range = np.linspace(0, 2, 100).reshape(-1, 1)
y_pred = nn.forward(X_range)

# 5. Visualización de resultados
plt.figure(figsize=(12, 5))

# Gráfico de pérdida
plt.subplot(1, 2, 1)
plt.plot(history)
plt.title("Curva de Aprendizaje (Loss)")
plt.xlabel("Épocas")
plt.ylabel("MSE")

# Gráfico de regresión
plt.subplot(1, 2, 2)
plt.scatter(X, y, color='blue', label='Datos Reales (con ruido)')
plt.plot(X_range, y_pred, color='red', linewidth=3, label='Predicción NN')
plt.title("Regresión Lineal con Red Neuronal")
plt.xlabel("X")
plt.ylabel("y")
plt.legend()

plt.tight_layout()
plt.show()
