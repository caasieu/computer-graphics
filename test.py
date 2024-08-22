import numpy as np
import matplotlib.pyplot as plt

# Função para rotacionar um ponto
def rotate_point(x, y, theta):
    # Converte o ângulo para radianos
    theta_rad = np.radians(theta)
    # Aplica as fórmulas de rotação
    x_prime = x * np.cos(theta_rad) - y * np.sin(theta_rad)
    y_prime = x * np.sin(theta_rad) + y * np.cos(theta_rad)
    return x_prime, y_prime

# Ponto original
x, y = 3, 4

# Ângulo de rotação
theta = 45

# Ponto após a rotação
x_prime, y_prime = rotate_point(x, y, theta)

# Gráfico
plt.figure(figsize=(8, 8))

# Eixos principais
plt.axhline(0, color='black',linewidth=0.5)
plt.axvline(0, color='black',linewidth=0.5)

# Triângulo original
plt.plot([0, x], [0, y], 'bo-', label='Original P(3,4)')

# Triângulo rotacionado
plt.plot([0, x_prime], [0, y_prime], 'ro-', label=f'Rotated P\'({x_prime:.2f},{y_prime:.2f})')

# Linhas da hipotenusa original e rotacionada
plt.plot([0, x_prime], [0, y_prime], 'r--', label='Hipotenusa Rotacionada')
plt.plot([0, x], [0, y], 'b--', label='Hipotenusa Original')

# Ajustes do gráfico
plt.xlim(-5, 5)
plt.ylim(-5, 5)
plt.grid(True)
plt.legend()
plt.title(f'Rotação de um Ponto (Ângulo: {theta}°)')
plt.xlabel('X')
plt.ylabel('Y')

# Exibe o gráfico
plt.show()
