import tkinter as tk
from tkinter import messagebox
import re

root = tk.Tk()
root.title("Interfaz - Regex & IMC")
root.geometry("500x600")

# EXPRESIONES REGULARES

tk.Label(root, text="EXPRESIONES REGULARES", font=("Arial", 12, "bold")).pack(pady=(15,5))
tk.Label(root, text="Instrucciones: ingresa un valor y presiona el botón para validarlo.",
         wraplength=460).pack()

# Email
tk.Label(root, text="Correo electrónico:").pack(anchor="w", padx=20, pady=(10,0))
entry_email = tk.Entry(root, width=50)
entry_email.pack(padx=20)

def validar_email():
    val = entry_email.get()
    if re.fullmatch(r"[a-zA-Z0-9._%+\-]+@[a-zA-Z0-9.\-]+\.[a-zA-Z]{2,}", val):
        messagebox.showinfo("Resultado", "Correo válido")
    else:
        messagebox.showerror("Resultado", "Correo inválido\nEjemplo: usuario@dominio.com")

tk.Button(root, text="Validar correo", command=validar_email).pack(pady=4)

tk.Frame(root, height=2, bd=1, relief="sunken").pack(fill="x", padx=20, pady=15)

# IMC

tk.Label(root, text="CALCULADORA DE IMC", font=("Arial", 12, "bold")).pack(pady=(0,5))
tk.Label(root, text="Instrucciones: ingresa tu peso en kg y estatura en metros.").pack()

tk.Label(root, text="Peso KG:").pack(anchor="w", padx=20, pady=(10,0))
entry_peso = tk.Entry(root, width=50)
entry_peso.pack(padx=20)

tk.Label(root, text="Estatura (m):").pack(anchor="w", padx=20, pady=(8,0))
entry_altura = tk.Entry(root, width=50)
entry_altura.pack(padx=20)

lbl_resultado_imc = tk.Label(root, text="", font=("Arial", 10))
lbl_resultado_imc.pack(pady=6)

def calcular_imc():
    try:
        peso   = float(entry_peso.get())
        altura = float(entry_altura.get())
        if peso <= 0 or altura <= 0:
            raise ValueError
        imc = peso / (altura ** 2)
        if imc < 18.5:
            categoria = "Bajo peso"
        elif imc < 25:
            categoria = "Peso normal"
        elif imc < 30:
            categoria = "Sobrepeso"
        else:
            categoria = "Obesidad"
        lbl_resultado_imc.config(text=f"IMC: {imc:.2f}  →  {categoria}")
    except ValueError:
        messagebox.showerror("Error", "Ingresa valores numéricos válidos y positivos.")

tk.Button(root, text="Calcular IMC", command=calcular_imc).pack(pady=6)

root.mainloop()