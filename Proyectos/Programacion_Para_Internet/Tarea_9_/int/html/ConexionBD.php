<?php 

$mysqli = new mysqli("localhost", "root", "", "progra_internet", "33061");
if($mysqli -> connect_errno){
    echo "Fallo la conexion Mysql: (". 
    $mysqli->connect_errno  . ") " . 
    $mysqli->connect_error;

}

?>

