#!/bin/sh

echo ">> Introduce el nombre de tu carpeta a crear"
read dir_name 

nuevo_dir=$(printf '%s\n' "$dir_name" | tr ' ' '_')

echo ">> tu nuevo directorio es: $nuevo_dir"

mkdir "$dir_name"

cd "$dir_name"

echo ">> Escribe 1 para el siguiente proceso, cualquier otro para terminar"

read numero

if [ "$numero" -eq 1 ]; then
    echo ">> Escribe algo"
    read algo
    echo "$algo" > texto.txt

else
exit 0
fi

echo ">> Quieres ver lo que escribiste? "
read numero_2 
if [ "$numero_2" -eq 1 ]; then
    cat texto.txt
    exit 0
fi
