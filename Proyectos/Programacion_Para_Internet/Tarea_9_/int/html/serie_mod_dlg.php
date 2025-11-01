<?php 
$mysqli = mysqli_connect("localhost", "root", "","progra_internet", "33061");
require_once("ConexionBD.php");

/**
$query = "
    SELECT ser_nombre, ser_id
    from serie
    where ser_id=".$_GET['id']; 
*/
$query = "SELECT * FROM serie where ser_id=".$_GET['id'];
$result=$mysqli->query($query);
$row=$result->fetch_object();

?>

<form action = "serie_mod_.php" method="post">
   Nombre
<input type="text" value = "<?php echo $row->ser_nombre?>" name ="nombre"/><br/>
Fecha inicio
<input type="date" value = "<?php echo $row->ser_fecha_ini?>" name ="inicio"/><br/>
Fecha final
<input type="date" value = "<?php echo $row->ser_fecha_fin?>" name ="fin"/><br/>
<input type="hidden" value = "<?php echo $row->ser_id?>" name ="id"/>
<input type="submit" value = "Modificar"><br/>
<input tyoe="hidden" value="1"/>
</form>
