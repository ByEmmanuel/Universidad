<?php 

echo "HASHKJDgjasvdjh";
$varInt = "Text0";

echo "<br>" . $varInt . "<br>" . "Hola mundo";

$var_altura = 10;
$var_base = 21.23;
$area = $var_altura * $var_base;

echo "<br> el area es " . $area . "<br>";

echo "el area es  {$area} <br/>";


$var1 = 1000;

$texto = "var1";

echo "la variable var1 tiene " . ${$texto};

$cal1 = 5;
$cal2 = 3;
$cal3 = 10;
$i = 0;
while($i < 3){
    echo "<br>" . ${"cal".($i+1)} ;
    $i++;
}
?>