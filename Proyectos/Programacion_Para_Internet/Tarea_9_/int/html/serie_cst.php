<?php
	require_once ("ConexionBD.php");
	$result = $mysqli->query("SELECT ser_nombre, ser_id FROM serie");
	echo "<input type=\"button\" value=\"Agregar\" onclick=\"location.href='serie_alt_dlg.php'\"/>";
	echo "<table border='1' cellspacing='0' cellpadding='5'>";
	echo "<tr><th>ID</th><th>Nombre</th><th>Acciones</th></tr>";

	$contador = 0;
	while($row = $result->fetch_object()){
		$contador++;
		if($contador % 2 == 0){
			echo "<tr style='background-color:white;'>";
		}else{
			echo "<tr style='background-color:lightgreen;'>";
		}

		echo "<td>".$row->ser_id."</td>";
		echo "<td>".$row->ser_nombre."</td>";
		echo "<td>
				<button onclick=\"location.href='serie_mod_dlg.php?id=".$row->ser_id."'\">
					<img src='../img/edit.png' width='20' height='20'>
				</button>
				<button>
					<img src='../img/delete.png' width='20' height='20'>
				</button>
			  </td>";
		echo "</tr>";
	}

	echo "</table>";
?>

