<?php 

print_r($_POST);
$imc = $_POST['peso']/($_POST['altura']*$_POST['altura']);
echo "<h1> tu imc es <span style=\"color:red;\"> $imc</span></h1>";

if($imc < 18.49){
// foto de un wey flaco
echo "<img src='../img/bob_flaco.webp' >";
}else if($imc >= 18.49 && $imc < 25){
// foto de alguien normal
echo "<img size='60px' src='../img/lecle.webp' >";
}else if($imc >= 25 && $imc < 30){
// foto de alguien masomenos
echo "<img src='../img/la_piedra.webp' >";
}else if($imc >= 30){
// foto de alguien pesadito
echo "<img src='../img/patricio.webp' >";
}


?>