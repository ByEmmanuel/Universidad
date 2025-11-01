<?php
	include("ConexionBD.php");

	$query = "INSERT INTO serie (ser_nombre, ser_fecha_ini, ser_fecha_fin)
	VALUES ('".$_POST['ser_nombre']."','".$_POST['ser_fecha_ini']."','".$_POST['ser_fecha_fin']."')";

	$resultado = $mysqli->query($query);

	if($resultado){
		echo "<h1 style=\"color:green;\">El alta fue exitosa</h1>";
		echo "<input type=\"button\" value=\"Regresar\" onclick=\"location.href='serie_cst.php'\"/>";
	}else{
		echo "<h1 style=\"color:red;\">Ocurrio una falla en el alta</h1>";
		echo "<input type=\"button\" value=\"Regresar\" onclick=\"history.back()\"/>";
	}
?>
