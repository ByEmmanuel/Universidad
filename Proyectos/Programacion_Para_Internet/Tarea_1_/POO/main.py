class Coche:
    def __init__(self, color, velocidad):
        self.color = color
        self.velocidad = velocidad
    
    def acelerar(self, incremento):
        self.velocidad += incremento
        return self.velocidad
    
    def frenar(self, decremento):
        self.velocidad -= decremento
        if self.velocidad < 0:
            self.velocidad = 0
        return self.velocidad

# crear el objeto
mi_coche = Coche("azul", 50)

print(mi_coche.color)
print(mi_coche.velocidad)
mi_coche.acelerar(20)  
print(mi_coche.velocidad)
mi_coche.frenar(30)  
print(mi_coche.velocidad)  

# acceder a un atributo 

print(mi_coche.color)
print(mi_coche.velocidad)

mi_coche.color = "rojo"
mi_coche.velocidad = 100
print(mi_coche.color)   
print(mi_coche.velocidad)

# llamar a un metodo publico

print(mi_coche.velocidad)
mi_coche.acelerar(20)    
print(mi_coche.velocidad)
mi_coche.frenar(30)      
print(mi_coche.velocidad)

