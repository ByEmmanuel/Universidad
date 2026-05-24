"""
Logica Difusa - Calculo de Propina
Entradas: servicio, comida, ambiente  [0, 10]
Salida:   propina                     [0, 30] %
Defuzzificacion: Centroide (CoA)
"""

import numpy as np
import skfuzzy as fuzz
from skfuzzy import control as ctrl
import matplotlib.pyplot as plt

# Universos
servicio = ctrl.Antecedent(np.arange(0, 11, 0.1), 'servicio')
comida   = ctrl.Antecedent(np.arange(0, 11, 0.1), 'comida')
ambiente = ctrl.Antecedent(np.arange(0, 11, 0.1), 'ambiente')
propina  = ctrl.Consequent(np.arange(0, 31, 0.1), 'propina')

# Funciones de membresia
servicio['malo']      = fuzz.trapmf(servicio.universe, [0, 0, 2, 4])
servicio['regular']   = fuzz.trimf(servicio.universe,  [2, 4, 6])
servicio['bueno']     = fuzz.trimf(servicio.universe,  [4, 7, 9])
servicio['excelente'] = fuzz.trapmf(servicio.universe, [7, 9, 10, 10])

comida['mala']       = fuzz.trapmf(comida.universe, [0, 0, 2, 4])
comida['aceptable']  = fuzz.trimf(comida.universe,  [2, 4, 6])
comida['buena']      = fuzz.trimf(comida.universe,  [4, 7, 9])
comida['deliciosa']  = fuzz.trapmf(comida.universe, [7, 9, 10, 10])

ambiente['incomodo']  = fuzz.trapmf(ambiente.universe, [0, 0, 2, 4])
ambiente['neutro']    = fuzz.trimf(ambiente.universe,  [2, 4, 6])
ambiente['agradable'] = fuzz.trimf(ambiente.universe,  [4, 7, 9])
ambiente['lujoso']    = fuzz.trapmf(ambiente.universe, [7, 9, 10, 10])

propina['baja']     = fuzz.trapmf(propina.universe, [0, 0, 5, 10])
propina['media']    = fuzz.trimf(propina.universe,  [5, 12, 18])
propina['alta']     = fuzz.trimf(propina.universe,  [15, 20, 25])
propina['generosa'] = fuzz.trapmf(propina.universe, [22, 26, 30, 30])

# Reglas
reglas = [
    ctrl.Rule(servicio['malo']      & comida['mala']      & ambiente['incomodo'],  propina['baja']),
    ctrl.Rule(servicio['malo']      & comida['aceptable'] & ambiente['incomodo'],  propina['baja']),
    ctrl.Rule(servicio['malo']      & comida['deliciosa'] & ambiente['lujoso'],    propina['media']),
    ctrl.Rule(servicio['regular']   & comida['mala']      & ambiente['incomodo'],  propina['baja']),
    ctrl.Rule(servicio['regular']   & comida['aceptable'] & ambiente['neutro'],    propina['media']),
    ctrl.Rule(servicio['regular']   & comida['deliciosa'] & ambiente['lujoso'],    propina['alta']),
    ctrl.Rule(servicio['bueno']     & comida['buena']     & ambiente['agradable'], propina['alta']),
    ctrl.Rule(servicio['bueno']     & comida['deliciosa'] & ambiente['lujoso'],    propina['generosa']),
    ctrl.Rule(servicio['excelente'] & comida['mala']      & ambiente['neutro'],    propina['media']),
    ctrl.Rule(servicio['excelente'] & comida['buena']     & ambiente['agradable'], propina['alta']),
    ctrl.Rule(servicio['excelente'] & comida['deliciosa'] & ambiente['lujoso'],    propina['generosa']),
]

# Simulacion
sistema = ctrl.ControlSystem(reglas)
sim     = ctrl.ControlSystemSimulation(sistema)

val_servicio = 7.5
val_comida   = 8.0
val_ambiente = 6.5

sim.input['servicio'] = val_servicio
sim.input['comida']   = val_comida
sim.input['ambiente'] = val_ambiente
sim.compute()

resultado = sim.output['propina']
print(f"Servicio : {val_servicio} | Comida : {val_comida} | Ambiente : {val_ambiente}")
print(f"Propina  : {resultado:.2f} %")

# Paleta: negro + 3 grises + rojo para la linea de entrada
LINEAS = ['black', '#444444', '#888888', '#bbbbbb']
OUT    = '/home/byemmanuel/Escritorio/Workspace/Universidad/Python_Doc/'

def graficar(universo, var, terminos, valor, titulo, xlabel, fname):
    fig, ax = plt.subplots(figsize=(7, 4))
    for i, t in enumerate(terminos):
        ax.plot(universo, var[t].mf, color=LINEAS[i], linewidth=2, label=t)
    ax.axvline(valor, color='red', linestyle='--', linewidth=1.5,
               label=f'entrada = {valor}')
    ax.set_title(titulo)
    ax.set_xlabel(xlabel)
    ax.set_ylabel('μ(x)')
    ax.set_ylim(-0.05, 1.1)
    ax.legend(fontsize=9)
    ax.grid(True, linestyle=':', color='#cccccc')
    fig.tight_layout()
    fig.savefig(fname, dpi=120)
    plt.close(fig)
    print(f"Guardada: {fname}")

graficar(servicio.universe, servicio,
         ['malo', 'regular', 'bueno', 'excelente'],
         val_servicio, 'Servicio', 'Calidad del servicio',
         OUT + 'var_servicio.png')

graficar(comida.universe, comida,
         ['mala', 'aceptable', 'buena', 'deliciosa'],
         val_comida, 'Comida', 'Calidad de la comida',
         OUT + 'var_comida.png')

graficar(ambiente.universe, ambiente,
         ['incomodo', 'neutro', 'agradable', 'lujoso'],
         val_ambiente, 'Ambiente', 'Calidad del ambiente',
         OUT + 'var_ambiente.png')

graficar(propina.universe, propina,
         ['baja', 'media', 'alta', 'generosa'],
         resultado, 'Propina (%)', 'Propina (%)',
         OUT + 'var_propina.png')