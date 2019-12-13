#!/bin/bash

#La idea de este script es la de juntar un programa dividido en varios archivos para así crear un único script que distribuir
#Al trabajar con archivos divididos es más simple y limpio, ya que facilita la organización

#El script por defecto trabjará con 2 archivos llamados:
	'cabecera'
	'main'
#ambos archivos contienen la cabecera del programa y la función main que llama a las diversas funciones
#al final del archivo se imprimirá la llamada a la función main.

llamadaMain='main'


if [[ -f "main.sh" ]] || [[ -f "main" ]]; then
	echo "Existe un archivo main"
	mainExiste=true
else
	echo "Archivo main no encontrado"
	echo "Si quiere utilizar un archivo main asegurse que se llama"
	echo "	-main"
	echo "	-main.sh"
	mainExiste=false
fi


if [[ -f "cabecera" ]] || [[ -f "cabercera.txt" ]]; then
	echo "Existe un archivo cabecera"
	cabeceraExiste=true
else
	echo "Si quiere utilizar un archivo cabecera asegurse que se llama"
	echo "	-cabecera"
	echo "	-cabecera.sh"
fi

fi


