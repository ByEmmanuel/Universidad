class Coche {
    constructor(color, velocidad) {
        this.color = color;
        this.velocidad = velocidad;
    }
    
    acelerar(incremento) {
        this.velocidad += incremento;
        return this.velocidad;
    }
    
    frenar(decremento) {
        this.velocidad -= decremento;
        if (this.velocidad < 0) {
            this.velocidad = 0;
        }
        return this.velocidad;
    }
}

// Crear el objeto
const miCoche = new Coche("azul", 50);

console.log(miCoche.color);  
console.log(miCoche.velocidad);
miCoche.acelerar(20);
console.log(miCoche.velocidad);
miCoche.frenar(30);
console.log(miCoche.velocidad);


// acceder a un atributo
console.log(miCoche.color);
console.log(miCoche.velocidad);

miCoche.color = "rojo";
miCoche.velocidad = 100;
console.log(miCoche.color);      
console.log(miCoche.velocidad);

// llamar a un metodo publico
console.log(miCoche.velocidad);
miCoche.acelerar(20);          
console.log(miCoche.velocidad);
miCoche.frenar(30);            
console.log(miCoche.velocidad);

