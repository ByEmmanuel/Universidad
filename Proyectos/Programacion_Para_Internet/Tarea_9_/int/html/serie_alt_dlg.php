<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="utf-8">
        <title>mi primera pagina web</title>
    </head>
    <body>
        <h1>Formulario Serie Alt</h1>
        <form action="serie_alt_.php" method="post">
		<div>
        <label>Nombre</label>
        <input type="text" name="ser_nombre" id="ser_nombre" placeholder="Nombre Serie">
        </div>
        <br>
        <div>
        <label>Fecha inicio</label>
        <input type="date" name="ser_fecha_ini" id="ser_fecha_ini">
        </div>
        <br>

        <br>
        <div>
        <label>Fecha final</label>
        <input type="date" name="ser_fecha_fin" id="ser_fecha_fin">
        </div>
        <br>
        <div>
        <input type="submit" value="Enviar">
        </div>
        </form>
    </body>
</html>
