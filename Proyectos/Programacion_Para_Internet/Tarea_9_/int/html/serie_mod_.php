<?php
include("ConexionBD.php");

$query = "UPDATE serie SET ser_nombre = '".$_POST['nombre']."', ser_fecha_ini = '".$_POST['inicio']."', 
ser_fecha_fin = '".$_POST['fin']."' where ser_id = ".$_POST['id'];

$resultado = $mysqli->query($query);


if($resultado){
    echo "<h1 style=\"color:green;\">La modificacion fue exitosa</h1>";
    echo "<input type='button' value='Regresar' onclick=\"location.href='serie_cst.php'\"/>";
}else{
    echo "<h1 style=\"color:red;\">Ocurrió un error al modificar</h1>";
    echo "<p>Error: ".$mysqli->error."</p>";
    echo "<input type='button' value='Regresar' onclick=\"history.back()\"/>";
}
?>
