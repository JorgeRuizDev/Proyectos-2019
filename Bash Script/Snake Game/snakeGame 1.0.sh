#!/bin/bash

#argumentosDeEjecución
argExe1=$1
argDebug=$2



#Colores:
blue='\e[104m'
red='\e[41m'
green='\e[102m'
white='\e[107m'
magenta='\e[45m'
cyan='\e[46m'
lightYellow='\e[102'
lightGreen='\e[103'
default='\e[49m'
yellow='\e[43m'

verde="$green $default"
rojo="$red $default"
azul="$blue $default"
blanco="$white $default"
magentaB="$magenta $default"
cyanB="$cyan $default"
amarilloBrillante="$lightYellow $default"
amarillo="$yellow $default"



#Configuración
velocidadJuego=0.06 #default 0.06
cabezaSerpiente=$verde$verde
cuerpoSerpienteColor=$amarillo$amarillo #$rojo$rojo
borde1=$cyanB$cyanB
borde2=$verde$verde


alto=21
ancho=21



#Arrays Locales
declare -a arraySnake
declare -a arraySnakeCabeza


main(){

	
	argumentosEjecución
	f_clear
	inicio
	cabecera
	gameLoop&
	loop_PID=$!
	echo $loop_PID > cfg/loop_PID

	userInput

}








#  ███████╗     ██╗███████╗ ██████╗██╗   ██╗ ██████╗██╗ ██████╗ ███╗   ██╗███████╗███████╗    ██╗   ██╗███╗   ██╗██╗ ██████╗ █████╗ ███████╗
#  ██╔════╝     ██║██╔════╝██╔════╝██║   ██║██╔════╝██║██╔═══██╗████╗  ██║██╔════╝██╔════╝    ██║   ██║████╗  ██║██║██╔════╝██╔══██╗██╔════╝
#  █████╗       ██║█████╗  ██║     ██║   ██║██║     ██║██║   ██║██╔██╗ ██║█████╗  ███████╗    ██║   ██║██╔██╗ ██║██║██║     ███████║███████╗
#  ██╔══╝  ██   ██║██╔══╝  ██║     ██║   ██║██║     ██║██║   ██║██║╚██╗██║██╔══╝  ╚════██║    ██║   ██║██║╚██╗██║██║██║     ██╔══██║╚════██║
#  ███████╗╚█████╔╝███████╗╚██████╗╚██████╔╝╚██████╗██║╚██████╔╝██║ ╚████║███████╗███████║    ╚██████╔╝██║ ╚████║██║╚██████╗██║  ██║███████║
#  ╚══════╝ ╚════╝ ╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚══════╝     ╚═════╝ ╚═╝  ╚═══╝╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝
#

inicio(){
	declare -Ag grid
	#atributos y configuración de inicio
		if [[ -d cfg ]]; then
		rm -r cfg
		mkdir cfg
		
	else
		mkdir cfg
	fi

	if [[ -d cfg ]]; then
		echo -n
	else
		echo -e "No se ha podido crear el directorio cfg\nCompruebe los permisos de la carpeta y del usuario\nDeteniendo la ejecución..."
		exit 0
	fi
	echo "false" > ./cfg/status

	#Variables Globales
	loopsPrint=0
	puntuacion=0

	SnakePosInicial
	gridBorders
	gridManzana

}

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------


gridBorders(){

	bordeAlto=$((alto+1))
	bordeAncho=$((ancho+1))


	#la siguiente función y variable generarán un tablero de ajedrez, con un color para cada cuadrado.
	#esto nos ayudará a generar unos bordes de cada color, y luego limpiaremos con otra función el interior del array
	#Atención: Los bordes laterales serán alternos sólo si el tamaño del área de juego es IMPAR
	local alternar=1

	for ((i=0; i<=$bordeAncho; i++)); do
		for ((j=0; j<=$bordeAlto;j++)); do

			if (( ((alternar%2))==0 ))
				then
					grid[$i,$j]=$verde$verde
				else
					grid[$i,$j]=$cyanB$cyanB
				fi
					((alternar++))
		done #jota
	done #i

	#el siguiente bucle borrará el interior del tablero y dejará sólo los bordes
	for ((i=1; i<$bordeAncho; i++)); do
		for ((j=1; j<$bordeAlto;j++)); do

				grid[$i,$j]="  "


			
		done #jota
	done #i

}

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------



SnakePosInicial(){

	#define la posición inicial de la serpiente
	#crearemos 3 varaibles. eje x, eje y, y dirección a la que mira

	cabezaX=5
	cabezaY=8
	cabezaZ=R #U,D,L,R // Up, Down, left, right

	cuerpoX=$cabezaX
	cuerpoY=$cabezaY
	snakeLongitudInicial=4
	snakeLongitud=$snakeLongitudInicial		#Esta variable se usa SOLO con la primera vez que se dibuja la serpiente. Luego baja a 2 para ayudar a dibujar el cuerpo
	snakeLongitudArray=$snakeLongitudInicial #Esta variable es necesaria para usarla como el número de posiciones del array que guarda cada coordenada en la que ha estado la serpiente en el que se encuentra la cola
												#Cada vez que coma se incrementará
}


#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------


f_clear(){


	if [[ $atributoClear == false ]]; then
		atributoClear=true
	else
		clear
	fi


	echo "$0 -h para más información"
	echo
	echo

}



























#  ██╗      ██████╗  ██████╗ ██████╗ ███████╗    ██╗   ██╗     ██████╗ ██████╗ ███╗   ███╗██████╗ ██████╗  ██████╗ ██████╗  █████╗  ██████╗██╗ ██████╗ ███╗   ██╗███████╗███████╗
#  ██║     ██╔═══██╗██╔═══██╗██╔══██╗██╔════╝    ╚██╗ ██╔╝    ██╔════╝██╔═══██╗████╗ ████║██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔════╝██║██╔═══██╗████╗  ██║██╔════╝██╔════╝
#  ██║     ██║   ██║██║   ██║██████╔╝███████╗     ╚████╔╝     ██║     ██║   ██║██╔████╔██║██████╔╝██████╔╝██║   ██║██████╔╝███████║██║     ██║██║   ██║██╔██╗ ██║█████╗  ███████╗
#  ██║     ██║   ██║██║   ██║██╔═══╝ ╚════██║      ╚██╔╝      ██║     ██║   ██║██║╚██╔╝██║██╔═══╝ ██╔══██╗██║   ██║██╔══██╗██╔══██║██║     ██║██║   ██║██║╚██╗██║██╔══╝  ╚════██║
#  ███████╗╚██████╔╝╚██████╔╝██║     ███████║       ██║       ╚██████╗╚██████╔╝██║ ╚═╝ ██║██║     ██║  ██║╚██████╔╝██████╔╝██║  ██║╚██████╗██║╚██████╔╝██║ ╚████║███████╗███████║
#  ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝     ╚══════╝       ╚═╝        ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚══════╝
#

gameLoop(){

for ((;;)); do
	sleep $velocidadJuego
	#statements
	empezarJuego=$(cat ./cfg/status)

	#el siguiente statement lee si el juego está en funcinamiento o en pausa (por defecto en pausa)
	until [[ $empezarJuego == true ]]; do
		empezarJuego=$(cat ./cfg/status)
	done

	moverSerpiente
	esSerpiente
	sonBordes
	
	gridSnake
	gridPrint
	comerManzana
done
}

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------


sonBordes(){

	#esta funcion comprueba si la cabeza se encuentra en un borde, si es así, piedes el juego

	#Se utiliza un sistema de oportunidades para evitar falsos positivos

	if (((cabezaX<=0)||cabezaX>=$((alto+1)) ))
	then
		((chances++))
		
	elif (( cabezaY <= 0 || cabezaY >= $((ancho+1)) ))
	then
		((chances++))
		
	else
		chances=0
	fi


	if ((chances == 2))
	then
		gameOver
	fi
}

esSerpiente(){

	cuadranteCabeza=${grid[$cabezaY,$cabezaX]}

	if [[ "$cuadranteCabeza" == "$cuerpoSerpienteColor" ]]; then
		gameOver
	fi
}












































#  ██████╗ ██╗███╗   ██╗████████╗ █████╗ ██████╗     
#  ██╔══██╗██║████╗  ██║╚══██╔══╝██╔══██╗██╔══██╗    
#  ██████╔╝██║██╔██╗ ██║   ██║   ███████║██████╔╝    
#  ██╔═══╝ ██║██║╚██╗██║   ██║   ██╔══██║██╔══██╗    
#  ██║     ██║██║ ╚████║   ██║   ██║  ██║██║  ██║    
#  ╚═╝     ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝    
# 


gridPrint(){
	((loopsPrint++))
	clear
	for ((i=0;i<=bordeAncho;i++)); do
		for((j=0; j<=bordeAlto;j++));do
			echo -ne "${grid[$i,$j]}"
				#**************DEBUG**************					
				if [[ $debugPrint1 == true ]]; then

				echo -ne $i,$j 

				fi
				#**************DEBUG**************	


		done
			echo
	done



	#**************DEBUG**************					
	if [[ $debugPrint2 == true ]]; then
	echo -e "cabezaX: $cabezaX CabezaY: $cabezaY \n tecla leida: $mov dir Actual Cabeza: $cabezaZ"
	printf "Loops: %d \n" $loopsPrint
	echo x/y cabeza//manzana//cola $cabezaX $cabezaY // $manzanaX $manzanaY //$colaX $colaY

	echo -e "\nQué hay en el cuadrante en el que está la cabeza?: cuadranteCabeza=$cuadranteCabeza."
	fi
	#**************DEBUG**************	
	
	echo -e "\nPuntuación: $puntuacion"

}


gridSnake(){

	
 	#Definimos un nuevo array en el que la posición 0 sea la posición actual de la cabeza de la serpiente.
	#añade a la serpiente al array
	grid[$cabezaY,$cabezaX]=$cabezaSerpiente
	cuerpoX=$cabezaX
	cuerpoY=$cabezaY

	elementosAborrarDelArray=1 #Esta variable almacena los elementos que vamos a borrar del array en cada movimiento
	#La idea es que esta vairable varíe entre 0 y 1, quitando o no elementos del array (que copie todo un array, o que copie todo el array menos 1 posición)
	#Se utilizará para cambiar el array cuando se come una manzana o no. es decir, para borrar el último elemento (la colo), o cualquier otra cosa


		if [[ "$primeraEjecucion" != "false" ]]; then
			arraySnake[0]=$cabezaY,$cabezaX
			echo otra ejecución
		fi

	
		for ((i=1;i<snakeLongitud;i++)); do
			case $cabezaZ in
				U)
				((cuerpoY++))
				grid[$cuerpoY,$cuerpoX]=$cuerpoSerpienteColor

				;;
				D)
				((cuerpoY--))
				grid[$cuerpoY,$cuerpoX]=$cuerpoSerpienteColor
				;;
				L)
				((cuerpoX++))
				grid[$cuerpoY,$cuerpoX]=$cuerpoSerpienteColor
				;;
				R)
				((cuerpoX--))
				grid[$cuerpoY,$cuerpoX]=$cuerpoSerpienteColor

					#**************DEBUG**************					
					if [[ $debugGridSnake == true ]]; then

					echo -n $cuerpoX,$cuerpoY 
					echo
					fi
					#**************DEBUG**************				
				;;
			esac
			if [[ "$primeraEjecucion" != "false" ]]; then

				arraySnake[i]=$cuerpoY,$cuerpoX
				
			fi

		done
			snakeLongitud=2 #Hace que sólo se imprima 1 vez para que sustituya la cabeza por el cuerpo
			primeraEjecucion=false


		
#idea de como mantener la cola de la serpiente, que crezca, y borrar la cola a la hora de generar movimiento:
#crear un array que contenga en la primera posición la cabeza, y en las siguientes posiciones, el cuerpo ordenado hasta la cola
#cuando se mueve la serpiente, colocar la nueva cabeza en la posición 1 del array (un nuevo array), copiar el viejo array al nuevo (ahora la posicion 1, que era la cabeza, es parte del cuerpo), y borrar la última posición del array, la cola.
#Los arrays tienen las COORDENADAS de la serpiente, por lo que es sustituir la coordenada equivalente a la cola por "  "

#si se come, se omite borrar la última posición de la serpiente en ese momento
	

		

		#Implementación: No ha sido posible usar la correctamente la longitud del array (ya que cuenta casillas vacía como miembros del array)

		#Por ello, hemos utilizado la variable: snakeLongitudArray como el limitador del tamaño del array
		#esta variable indicará la posición de la cola en el array, cuenta la cabeza como la posición 0, y suma $snakeLongitudArray como el tamaño del cuerpo

		#Si se come una manzana, la variable incrementará, idicando la posición de la cola como la siguiente posición almacenada en el array





		#**************DEBUG**************					
		if [[ $debugPrint3 == true ]]; then

		echo El array mide $long_arraySnake de ${#arraySnake[*]}


		fi
		#**************DEBUG**************	

		#Si NO se ha comido una manzana, se pinta en la posición de la cola (En este caso, la de la previa ejecución ya que no hemos asignado una al inicio) un espacio en blanco
		if [[ $crecimiento == true ]]; then
			echo -n

		else
			#por como funciona la sintaxis de este lenguaje, necesitamos extrar los dos valores que se encuentran en la última posición del array
			#y guardarlos en 2 variables distintas para así poder modificar el array original.
			

			c=${arraySnake[snakeLongitudArray]}

			#debug
			
			a=$(echo $c | cut -d "," -f 1)
			b=$(echo $c | cut -d "," -f 2)
			
			grid[$a,$b]="  "


			#**************DEBUG**************					
			if [[ $debugPrint3 == true ]]; then

			echo cola y,x: $c
			#Si tenemos el modo debug activo, se nos marcará el recorrido de la serpiente con xx
			grid[$a,$b]="xx"


			fi
			#**************DEBUG**************	
		fi



#Definimos un nuevo array en el que la posición 0 sea la posición actual de la cabeza de la serpiente.

		arraySnakeCabeza[0]=$cabezaY,$cabezaX

#Ahora copiamos todos los elementos del array viejo al nuevo, pero en otras posiciones
#Vamos a requerir dos variables. Una en la que seleccionemos las posiciones del array cabeza a partir de 1
#otra en la que seleccionemos las posiciones del primer array desde la posición 0


		long_arraySnake=$snakeLongitudArray

#Con el siguiente bucle copiaremos los elementos del array antiguo (desde 0 hasta la longitud de la serpiente)
#En el nuevo (A partir de la posición 1, porque la 0 incluye la posición de la cabeza tras moverse)
		j=1
		for (( i = 0; i < long_arraySnake; i++ )); do

			
			arraySnakeCabeza[j]=${arraySnake[i]}

			#**************DEBUG**************					
				if [[ $debugPrint3 == true ]]; then
					echo $i:
					echo Array Snake ${arraySnake[i]}
					echo Array Snake Cabeza ${arraySnakeCabeza[j]}
				fi
			#**************DEBUG**************	

			((j++))
		done


		#Si no se ha comido la manzana, se borrará la última posición copiada en el array
		#Si se ha comido, no se hace nada, manteniendo la posición
		if [[ crecimiento==true ]]; then
			crecimiento=false
		else
			unset arraySnakeCabeza[-1]
		fi


		for (( i = 0; i <= long_arraySnake; i++ )); do
			arraySnake[i]=${arraySnakeCabeza[i]}

			#**************DEBUG**************					
				if [[ $debugPrint3 == true ]]; then
					echo $i: nuevo array snake: ${arraySnake[i]} de ${arraySnakeCabeza[i]}
				fi
			#**************DEBUG**************

		done



	#**************DEBUG**************					
		if [[ $debugPrint3 == true ]]; then
			#esperamos para poder leer los datos
			sleep 1
		fi
	#**************DEBUG**************
		

}



















#  ███╗   ███╗ █████╗ ███╗   ██╗███████╗ █████╗ ███╗   ██╗ █████╗ 
#  ████╗ ████║██╔══██╗████╗  ██║╚══███╔╝██╔══██╗████╗  ██║██╔══██╗
#  ██╔████╔██║███████║██╔██╗ ██║  ███╔╝ ███████║██╔██╗ ██║███████║
#  ██║╚██╔╝██║██╔══██║██║╚██╗██║ ███╔╝  ██╔══██║██║╚██╗██║██╔══██║
#  ██║ ╚═╝ ██║██║  ██║██║ ╚████║███████╗██║  ██║██║ ╚████║██║  ██║
#  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝
#

gridManzana(){


	hayManzana=false

	until [[ $hayManzana == true ]]; do
		manzanaX=$(( $RANDOM % $ancho + 1 ))
		manzanaY=$(( $RANDOM % $alto + 1 ))


		cuadranteLeido=${grid[$manzanaX,$manzanaY]}
		#comprbamos que no hay un color esa coordenada, significará que está vacía y puede aparecer
		if [[ ${cuadranteLeido:0:1} == '\' ]]; then
			hayManzana=false
		else
			hayManzana=true
		fi

	done

	grid[$manzanaX,$manzanaY]=$rojo$rojo
}

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

comerManzana(){
	#esta función comprobará a partir de la posición actual de la cabeza, y su orientación, si el cuadrado al
	#que está apuntando la serpiente es una manzana, y si es así, se aumentará en 1 el tamaño (no se borrará su cola)
	#se sumará 1 punto, y se spawneará otra manzana

	if (((cabezaX == manzanaY) && (cabezaY==manzanaX)))
	then
		
		((puntuacion++))
		gridManzana
		crecimiento=true
		((snakeLongitudArray++))
	fi

}










































#  ███╗   ███╗ ██████╗ ██╗   ██╗██╗███╗   ███╗██╗███████╗███╗   ██╗████████╗ ██████╗ 
#  ████╗ ████║██╔═══██╗██║   ██║██║████╗ ████║██║██╔════╝████╗  ██║╚══██╔══╝██╔═══██╗
#  ██╔████╔██║██║   ██║██║   ██║██║██╔████╔██║██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║
#  ██║╚██╔╝██║██║   ██║╚██╗ ██╔╝██║██║╚██╔╝██║██║██╔══╝  ██║╚██╗██║   ██║   ██║   ██║
#  ██║ ╚═╝ ██║╚██████╔╝ ╚████╔╝ ██║██║ ╚═╝ ██║██║███████╗██║ ╚████║   ██║   ╚██████╔╝
#  ╚═╝     ╚═╝ ╚═════╝   ╚═══╝  ╚═╝╚═╝     ╚═╝╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝


userInput(){

	for((;;)); do
		#statements
	
	read -s -n 1 entradaUsuario
		
	echo "false" > ./cfg/status

	case $entradaUsuario in
		w|W) 
		mov=U
		echo "true" > ./cfg/status
		;;

		a|A) 
		mov=L
		echo "true" > ./cfg/status
		;;

		s|S)
		mov=D
		echo "true" > ./cfg/status
		;; 

		d|D)
		mov=R
		echo "true" > ./cfg/status
		;;

		x|X)
		echo -e "Saliendo..."

		kill $loop_PID
		rm -r cfg
		sleep 0.5
		exit 0
		
		;;
		p|P)
		pausar
		;;
		*)
		echo -n
		;;
	esac
	
	echo "$mov" > ./cfg/input
	export mov=$mov
	
done


}

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

moverSerpiente(){

	#Leemos el Input (la forma más sencilla de leer variables de otros procesos es mediante la lectura de archivos.)
	mov=$(cat ./cfg/input)

	#incrementamos la posición de la cabeza y guardamos la dirección a la que está mirando.
	#Si la dirección no es válida, se ejecuta "ultimoMovimiento" que continua el movimineto de la serpiente en la dirección a la que mira (CabezaZ)
	case $mov in
		U)
		if [[ $cabezaZ != D ]]; then
			((cabezaY--))
			cabezaZ=$mov
		else
			ultimoMovimiento
		fi
	
		;;
		D)
		if [[ $cabezaZ != U ]]; then
			((cabezaY++))
			cabezaZ=$mov
		else
			ultimoMovimiento
		fi
		;;

		L)
		if [[ $cabezaZ != R ]]; then
			((cabezaX--))
			cabezaZ=$mov	
		else
			ultimoMovimiento
		fi
		;;

		R)
		if [[ $cabezaZ != L ]]; then
			((cabezaX++))
			cabezaZ=$mov
		else
			ultimoMovimiento
		fi
		;;
	esac

}

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

ultimoMovimiento(){

	#Esta función ejecuta el último movimiento asignado (es decir, la serpiente se mueve en la dirección en la que apunta su cabeza [cabezaZ])

		case $cabezaZ in
		U)
		if [[ $cabezaZ != D ]]; then
			((cabezaY--))

		fi
	
		;;
		D)
		if [[ $cabezaZ != U ]]; then
			((cabezaY++))
		fi
		;;

		L)
		if [[ $cabezaZ != R ]]; then
			((cabezaX--))
		fi
		;;

		R)
		if [[ $cabezaZ != L ]]; then
			((cabezaX++))

		fi
		;;
	esac
}

























#  ████████╗███████╗██╗  ██╗████████╗ ██████╗ ███████╗
#  ╚══██╔══╝██╔════╝╚██╗██╔╝╚══██╔══╝██╔═══██╗██╔════╝
#     ██║   █████╗   ╚███╔╝    ██║   ██║   ██║███████╗
#     ██║   ██╔══╝   ██╔██╗    ██║   ██║   ██║╚════██║
#     ██║   ███████╗██╔╝ ██╗   ██║   ╚██████╔╝███████║
#     ╚═╝   ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚══════╝
#

cabecera(){
	echo -e "
	\e[32m
	███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗      ██████╗  █████╗ ███████╗██╗  ██╗
	██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝      ██╔══██╗██╔══██╗██╔════╝██║  ██║
	███████╗██╔██╗ ██║███████║█████╔╝ █████╗  █████╗██████╔╝███████║███████╗███████║
	╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  ╚════╝██╔══██╗██╔══██║╚════██║██╔══██║
	███████║██║ ╚████║██║  ██║██║  ██╗███████╗      ██████╔╝██║  ██║███████║██║  ██║
	╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝
                                                                     Version 1.0!
	\e[35m                                                                                  
	     _                        ___        _        ___   //                   
	  _ | | ___  _ _  __ _  ___  | _ \ _  _ (_) ___  / __| ___  _ __   ___  ___
	 | || |/ _ \| '_|/ _  |/ -_) |   /| || || ||_ / | (_ |/ _ \| '  \ / -_)|_ /
	  \__/ \___/|_|  \__, |\___| |_|_\ \_,_||_|/__|  \___|\___/|_|_|_|\___|/__|
	                 |___/                                                     
	                                                                   
	\e[39m


	"
	echo "W) Arriba"
	echo "S) Abajo"
	echo "A) Izquierda"
	echo "D) Derecha"
	echo
	echo "P) Pausa"
	echo "X) Salir"

}

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

gameOver(){
	clear


	echo -e "\e[95m
   ▄██████▄     ▄████████   ▄▄▄▄███▄▄▄▄      ▄████████       ▄██████▄   ▄█    █▄     ▄████████    ▄████████ 
  ███    ███   ███    ███ ▄██▀▀▀███▀▀▀██▄   ███    ███      ███    ███ ███    ███   ███    ███   ███    ███ 
  ███    █▀    ███    ███ ███   ███   ███   ███    █▀       ███    ███ ███    ███   ███    █▀    ███    ███ 
 ▄███          ███    ███ ███   ███   ███  ▄███▄▄▄          ███    ███ ███    ███  ▄███▄▄▄      ▄███▄▄▄▄██▀ 
▀▀███ ████▄  ▀███████████ ███   ███   ███ ▀▀███▀▀▀          ███    ███ ███    ███ ▀▀███▀▀▀     ▀▀███▀▀▀▀▀   
  ███    ███   ███    ███ ███   ███   ███   ███    █▄       ███    ███ ███    ███   ███    █▄  ▀███████████ 
  ███    ███   ███    ███ ███   ███   ███   ███    ███      ███    ███ ███    ███   ███    ███   ███    ███ 
  ████████▀    ███    █▀   ▀█   ███   █▀    ██████████       ▀██████▀   ▀██████▀    ██████████   ███    ███ 
                                                                                                 ███    ███ 
                                                                                                 \e[39m
"


	echo "Tu Puntuación: $puntuacion"


	echo "Pulse [X] para salir"
	exit 0


}

#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

pausar(){
	sleep 0.5
	echo
	echo "
  ██████╗  █████╗ ██╗   ██╗███████╗ █████╗ 
  ██╔══██╗██╔══██╗██║   ██║██╔════╝██╔══██╗
  ██████╔╝███████║██║   ██║███████╗███████║
  ██╔═══╝ ██╔══██║██║   ██║╚════██║██╔══██║
  ██║     ██║  ██║╚██████╔╝███████║██║  ██║
  ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
  
 "	echo Pulse [Enter] para continuar
	echo "false" > ./cfg/status
	read hola
	echo "true" > ./cfg/status
}




























#   █████╗ ██████╗  ██████╗ ██╗   ██╗███╗   ███╗███████╗███╗   ██╗████████╗ ██████╗ ███████╗    ██████╗ ███████╗    ███████╗     ██╗███████╗ ██████╗██╗   ██╗ ██████╗██╗ ██████╗ ███╗   ██╗
#  ██╔══██╗██╔══██╗██╔════╝ ██║   ██║████╗ ████║██╔════╝████╗  ██║╚══██╔══╝██╔═══██╗██╔════╝    ██╔══██╗██╔════╝    ██╔════╝     ██║██╔════╝██╔════╝██║   ██║██╔════╝██║██╔═══██╗████╗  ██║
#  ███████║██████╔╝██║  ███╗██║   ██║██╔████╔██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║███████╗    ██║  ██║█████╗      █████╗       ██║█████╗  ██║     ██║   ██║██║     ██║██║   ██║██╔██╗ ██║
#  ██╔══██║██╔══██╗██║   ██║██║   ██║██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║   ██║   ██║╚════██║    ██║  ██║██╔══╝      ██╔══╝  ██   ██║██╔══╝  ██║     ██║   ██║██║     ██║██║   ██║██║╚██╗██║
#  ██║  ██║██║  ██║╚██████╔╝╚██████╔╝██║ ╚═╝ ██║███████╗██║ ╚████║   ██║   ╚██████╔╝███████║    ██████╔╝███████╗    ███████╗╚█████╔╝███████╗╚██████╗╚██████╔╝╚██████╗██║╚██████╔╝██║ ╚████║
#  ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚══════╝    ╚═════╝ ╚══════╝    ╚══════╝ ╚════╝ ╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝
#                                                                                                                                                                                         

argumentosEjecución(){


	if [[ $(echo $argExe1 | cut -c 1 ) == "-" ]]
	then

	hayParametro=true

	numeroDeParametrosIntroducidos=$(( $(echo $argExe1 | wc -c)-1))	#restamos 1 unidad ya que cuenta el \n como un caracter (creo)

	declare -ag arrayParametrosIntroducidos

	for ((i=1;i<=numeroDeParametrosIntroducidos;i++)); do

		arrayParametrosIntroducidos[$i]=$(echo $argExe1 | cut -c $i)



	done
fi



if [[ $hayParametro == true ]]
	then

		for ((i=2; i<= numeroDeParametrosIntroducidos; i++)); do

			case ${arrayParametrosIntroducidos[i]} in 
				d)
					echo "Modo debug: Activado"
					debug=true
					argDebug
				;;
				h) 
					help
				;;
				c)
					atributoClear=false
				;;
				r)
					alto=$(( ( $(tput lines) - 0 )  ))
					acho=$(( ( $(tput cols) - 0 )   ))


					echo alto: $alto x ancho: $ancho modo experimental
					echo Tamaño del terminal actual: $(tput lines) x $(tput cols)

					read -p "El estado de -r es experimental, pulse enter para continuar " hola
				;;
				*)
					echo "El parámetro introducido \"${arrayParametrosIntroducidos[i]}\" no es válido"
					echo "Utilice -h para visualizar otros parámetros"
				;;
				
			esac
		done
fi

}

help(){

	echo "Bienvenido a la función \"Información\""

	echo "-h: Ayuda"
	echo "-d: Debug General"
	echo "-r: alto x ancho del tamaño del terminal"
	echo "introduzca un segundo parámetro (equivalente a \$2) para introducir debugs indiviuales"
	echo "Si introduce h (sin -) como segundo parámetro, obtendrá la lista general"
	echo "-c: Clear; desactiva el primer clear"



	echo
	echo "Saliendo..."
	echo 
	exit 0
}

argDebug(){


	
	numeroDeParametrosIntroducidosDebug=$(( $(echo $argDebug | wc -c)-1))	#restamos 1 unidad ya que cuenta el \n como un caracter (creo)

if ((numeroDeParametrosIntroducidosDebug >=1))
then
	declare -ag arrayParametrosIntroducidosDebug

	for ((i=1;i<=numeroDeParametrosIntroducidosDebug;i++)); do

		arrayParametrosIntroducidosDebug[$i]=$(echo $argDebug| cut -c $i)

	done

		for ((i=1; i<= numeroDeParametrosIntroducidosDebug; i++)); do

			case ${arrayParametrosIntroducidosDebug[i]} in 
				-)
					echo No es necisario introducir \"-\" leñe
					echo
				;;
				d)
					echo "Modo debug: Activado"
					debug=true
					
				;;
				p)
					echo "Modo Debug Print1: Activado"
					debugPrint1=true
				;;
				b) 	echo "Modo Debug gridSnake: Activado"
					debugGridSnake=true
				;;
				s)
					debugPrint2=true
					;;
				l)
					debugPrint3=true
					;;
				h) 
					
					echo "Lista de parámetros:
						b) debug grid snake
						p) debugPrint1 (coordenadas totales)
						s) debugPrint2 (posición actual de cada cosa importante)
						l) debugPrint3 (Coordeandas totales de por donde ha pasado la serpiente, ordenadas)
						"
					exit 0
				;;
				*)
					echo "El parámetro introducido \"${arrayParametrosIntroducidos[i]}\" no es válido"
					echo "Utilice \"-d h\" para visualizar otros parámetros"
				;;

				
			esac
		done
fi
}


main