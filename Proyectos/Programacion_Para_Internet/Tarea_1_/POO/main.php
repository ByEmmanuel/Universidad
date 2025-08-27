<?php
class Coche {
    public $color;
    public $velocidad;
    
    public function __construct($color, $velocidad) {
        $this->color = $color;
        $this->velocidad = $velocidad;
    }
    
    public function acelerar($incremento) {
        $this->velocidad += $incremento;
        return $this->velocidad;
    }
    
    public function frenar($decremento) {
        $this->velocidad -= $decremento;
        if ($this->velocidad < 0) {
            $this->velocidad = 0;
        }
        return $this->velocidad;
    }
}


// Crear el objeto
$mi_coche = new Coche("azul", 50);

echo $mi_coche->color . "\n";  
echo $mi_coche->velocidad . "\n";
$mi_coche->acelerar(20);  
echo $mi_coche->velocidad . "\n";
$mi_coche->frenar(30);
echo $mi_coche->velocidad . "\n";

// acceder a un atributo

echo $mi_coche->color . "\n";
echo $mi_coche->velocidad . "\n";

$mi_coche->color = "rojo";
$mi_coche->velocidad = 100;
echo $mi_coche->color . "\n";
echo $mi_coche->velocidad . "\n";

// llamar a un metodo publico

echo $mi_coche->velocidad . "\n";  
$mi_coche->acelerar(20);           
echo $mi_coche->velocidad . "\n";  
$mi_coche->frenar(30);             
echo $mi_coche->velocidad . "\n";  

?>

