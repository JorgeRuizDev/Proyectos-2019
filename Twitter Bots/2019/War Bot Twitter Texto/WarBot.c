/*
Warbot que genera archivos de texto individuales para cada combate
	Incluye vidas, gemas de poder (Infinity Stones) y resurrecciones

Autor: Jorge Ruiz Gómez
Fecha: 11/07/2019

COMPILADO Y EJECUCIÓN:
c(99) e instalar GCC (última versión)

	gcc WarBot.c -o WarBot.out && ./Warbot.out
	
V 1.0	
	Información
	
	El programa necesita de las carpetas indicadas más adelante para funcionar
	Asegurese que existen, o use el sistema automático
	
	Introduzca a los famosos (No más de 60 caracteres, ni más de 500 famosos, 
		el algoritmo no ha sido probado con más de 150) en el archivo 'lista_famosos.txt'
		
		El algoritmo no permite más de una gema de cada tipo, téngalo en cuenta a la hora de añadirlas al archivo
		
		Cada gema ó jugador con atributos especiales desde el inicio tienen que ser modificados dentro del algoritmo

ATENCIÓN: Actualmente el algorimo no detecta si Thanos ha conseguido las 6 gemas (Al ser muy improbable)		
*/

//Librerias
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 



//Defines
#define FAMOSOSMAX 500
#define FAMOSOSLONGMAX 60
#define VIDASREVK 4
#define VICTORIASREVK 4
#define NUMITEMS 16 //Son los items 


//Estructuras
struct famoso{
	char nom[200];
	int vidas,victorias;
	
	
	//Booleanos
	//Utilizamos booleanos para el control de flujo
	bool item;
	bool uso;
	
	//gamas
	bool realidad;
	bool mente;
	bool alma;
	bool espacio;
	bool poder;
	bool tiempo;
	
	bool muerto;
	bool vida;
	bool resurreccion;
};
typedef struct famoso FAMOSO;



//Prototipos
int cargarFamosos(char famosos[][FAMOSOSLONGMAX], FILE *pArchivo);
void combate(char famosos[][FAMOSOSLONGMAX],int nFamosos);
void debug (int, int, FAMOSO[]);
void gemasWrite(int ganador, int perdedor, FAMOSO fam[],FILE *);

int main(){
	
	
	FILE *pArchivo;
	pArchivo = fopen("./lista_famosos.txt","r+");
	
	if (pArchivo==NULL){
		printf("Deteniendo Ejecución\nLectura de archivos incorrecta, compruebe que los ficheros tienen los permisos adecuados\n");
		printf("Asegurese de tener el archivo \"./lista_famosos.txt\"\n");
		getchar();
		exit (0);
	}
	
	
	

	//array donde se almacenan los famosos
	char v_famosos[FAMOSOSMAX][FAMOSOSLONGMAX];
	
	int nLineas = cargarFamosos(v_famosos, pArchivo);
	printf("\nSe han leido %d famosos\n",nLineas);
	fclose(pArchivo);
	
	

	combate (v_famosos,nLineas);
	
	printf("\nThis is the End\n");
	
	return 0;
}

int cargarFamosos(char famosos[][FAMOSOSLONGMAX], FILE *pArchivo){
	//Esta función carga el archivo con los famosos
	int nLineas =0;
	//printf("¿Desea ver a los famosos introducidos?\nEscriba \"S\" para prodceder\n");
	char si[100];
	//scanf("%s",si);
	while (fgets(famosos[nLineas],60,pArchivo)){
		//puts(famosos[nLineas]);
		if(strcmp(si,"S")==0){
			printf("Famoso: %s",famosos[nLineas]);
		}
		famosos[nLineas][strcspn(famosos[nLineas], "\r\n")] = 0;
		nLineas++;
	}
	return nLineas;
}

void combate(char famosos[][FAMOSOSLONGMAX],int nFamosos){
	//		IGUAL PUEDEN USARSE ARRAYS TRIDIMENSIONALES, PERO ESTO ME PARCE MÁS RÁPIDO
	
	//int vidas[nFamosos]; // cada usuario tiene una vida en el mismo valor que el vector
				//Si la vida es 0, no se tiene en cuenta su valor.
	int victorias[nFamosos]; //al igual que el array anterior, si el personaje en cuestión tiene 1 victorias, su posibilidad de ganar aumenta un 33%
	
	//definimos el vector de registros
	FAMOSO fam[nFamosos];
	
	//Definimos dos vectores con las gemas (reutilizar el mismo da error)
	char *gemas [6] = {"La Gema de la Realidad","La Gema de la Mente","La Gema del Alma","La Gema del Espacio","La Gema del Poder","La Gema del Tiempo"}; //array 0-5
	char *gemas2[6] = {"La Gema de la Realidad","La Gema de la Mente","La Gema del Alma","La Gema del Espacio","La Gema del Poder","La Gema del Tiempo"};

	//Asignación de victorias y vidas
	
	for (int a=0; a<nFamosos; a++){
		//Iniciamos todos los arrays a uno por defecto, 0, false, etc
		
		//Carga del vector de registros con el array de los nombres
		strcpy(fam[a].nom,famosos[a]);
		fam[a].vidas=1;
		fam[a].victorias=0;
		fam[a].item=false;
		fam[a].realidad=false;
		fam[a].mente=false;
		fam[a].alma=false;
		fam[a].espacio=false;
		fam[a].poder=false;
		fam[a].tiempo=false;
		fam[a].vida=false;
		fam[a].resurreccion=false;
		fam[a].uso=false;
		fam[a].muerto=false;
		
		
		
		//Comprobación de si es un objeto, jugador especial, etc, para cambiar los stats manualmente
		if (strcmp("Revk08",famosos[a])==0){
			fam[a].vidas=VIDASREVK;
			fam[a].victorias=VICTORIASREVK;
		}
		
	//tratamiento de las gemas
		else if (strncmp("La Gema",fam[a].nom,5)==0){
			for(int b=0; b<6;b++){
				if(strcmp(fam[a].nom,gemas[b])==0){
				
					switch(b){
						case 0:
						fam[a].realidad=true;
						fam[a].item=true;
						break;
						case 1:
						fam[a].mente=true;
						fam[a].item=true;
						break;
						case 2:
						fam[a].alma=true;
						fam[a].item=true;
						break;
						case 3:
						fam[a].espacio=true;
						fam[a].item=true;
						break;
						case 4:
						fam[a].poder=true;
						fam[a].item=true;
						break;
						case 5:
						fam[a].tiempo=true;
						fam[a].item=true;
						break;					
					}
				}
			}
		}
		else if (strcmp("Vida",fam[a].nom)==0){
				fam[a].item=true;
				fam[a].vida=true;
				fam[a].uso=true;
		}
		else if (strcmp("Resurreccion",fam[a].nom)==0){
				fam[a].item=true;
				fam[a].resurreccion=true;
				fam[a].uso=true;
		}	
		
		//debug para visualizar toda la lista
		//int error1=a;
		//printf("%d: %s, %d, %d \n bools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);
		

	}




//Asignación de valores del combate
	int random1, random2; // Dos integers donde se almacenará el id de un famoso aleatorio
	srand(time(0)); //seedeo del rand (Para generar números aleatorios)
	int restantes=nFamosos-NUMITEMS;//Integer con los famosos, restando vidas, gemas, etc.
	int ciclos=0, ciclosBucle=0; // Contadores de ciclos válidos (Duelos) y ciclos totales
	
	int vivos=2; //Vivos es el contador que asigna un valor, Lo inicializamos a más de 2, porque si hay una única persona viva, el bucle de batalla no se ejecuta
	
	//Los distintos archivos con los que vamos a trabajar
	FILE *pArchivo, *pRe, *info,*logs; //pRe es el archivo para reopen
	
	
		//GESTIÓN DE FICHEROS, SÓLO LINUX (Es necesario la creación de directorios si se ejecuta bajo windows si deseamos tener todos los documentos)
		int entrada;
		bool entradaBool = false;
		
		printf("\n\n\nEs necesario que exista una carpeta llamada \"./output\" junto con el .out/.exe del programa\n");
		printf("Si usas Windows o no quieres dar permisos de administrador para modificar la carpeta, MODIFIQUE LA JERARQUÍA DE CARPETAS MANUALMENTE\n");
		
		printf("\n\n¿Qué tipo de gestión de ficheros quiere realizar?\n\n1) Manual  (Windows ó Linux sin Sudo)\n2) Automática (Require de la ejecución de Linux más permisos root mediante Sudo (El usuario ha de estar en sudoers)\n");
		while (entradaBool==false){
			
			printf("-->");
			scanf("%d",&entrada);
			
			if (entrada<1 || entrada>2){
				bool entrada=false;
				printf("Error, introduzca cualquier valor para continuar\nEvite congestionar la entrada, use sólo números\n");
				printf("Continuar: ");
				while (getchar()!='\n'){
					printf("Continuar: ");
				}
				
			}
			else 
				entradaBool = true;
		}
		
		if (entrada==2){
		
		system ("mkdir ./output");
		system ("sudo rm -r ./output/*");
		system ("mkdir ./output/logs && mkdir ./output/vivos");
		
		}
		else if (entrada == 1){
			printf ("Cree la carpeta './output' para guardar los resultados\n'./output/logs' y './output/vivos' generan archivos extras, SON fundamentales para un funcinamiento correcte\n");
			printf("Asegurese que la carpta ./output no tiene ningún contenido que puda interferir con el programa (Por ejemplo archivos .txt), sólo las carptas indicadas previamente\n");
			printf("\nPulse  varias veces una vez este listo...\n");
			
			getchar();
			getchar();
		}
		
		//Limpieza de la cache
		pArchivo = fopen ("./output/cache","w");
		if (pArchivo == NULL)
			printf("Intento de creación de Caché fallido, compruebe que existe la carpeta \"Enfrentamientos\" o tiene los permisos necesarios");
		fclose(pArchivo);
//**********************************


	//Archivo en el que se imprime el número de famosos
	info = fopen ("./output/info.txt","w");
	if (info!=NULL){
		//Guarda en un archivo al número de jugadores
		fprintf(info,"%d",nFamosos-NUMITEMS);
		fclose (info);
	}
	else
		printf("Error a la hora de escribir la información\n");





//Combate, bucle************************
	while(vivos>1){
		bool ciclosB=false;
		int r1 = random1 = rand() % nFamosos;
		int r2 = random2 = rand() % nFamosos;


		//GESTION DE ARCHIVOS
		
		//creamos un string dinámico que gestione el nombre de los archivos.
		char nombre[50];
		sprintf(nombre,"output/%d.txt",ciclos+1);
		


		//CACHÉ ; si no hay un pArchivo abierto dentro del while, los fprintf y fclose fallarán == core dump, quitar comentario para tener un archivo temporal
		//pArchivo = fopen ("./Enfrentamientos/cache","a");

		//Archivo de trabajo, con nombre dinámico
		pArchivo = fopen(nombre,"a");
		

		//REOPEN -- Guarda todo el stdout en los archivos, mantener uno de los siguientes freopen sin comentar, o eliminar el fclose del final del while para evitar un error.
		//pRe = freopen (nombre,"w+",stdout);
		//pRe = fopen("./Enfrentamientos/cache","a");

		//mismo jugador, skip
		if(random1==random2){
			char cacas=0;
		}
		
		//resurreción
		else if ((fam[r1].resurreccion==true || fam[r2].resurreccion==true ) && (fam[r1].resurreccion!=fam[r2].resurreccion) && (fam[r1].muerto==true || fam[r2].muerto==true)&& (strcmp(fam[r1].nom,fam[r2].nom)!=0)){
			if (fam[r1].resurreccion==true && fam[r1].uso==true){
				printf("%s ha vuelto de entre los muertos, ahora más fuerte que nunca.\n",fam[r2].nom);
				fprintf(pArchivo,"%s ha vuelto de entre los muertos, ahora más fuerte que nunca.\n",fam[r2].nom);
				fam[r2].victorias++;
				fam[r2].vidas++;
				fam[r1].resurreccion=false;
				fam[r2].muerto=false;
			}
			else if(fam[r2].resurreccion==true && fam[r2].uso==true){
				printf("%s ha vuelto de entre los muertos, ahora más fuerte que nunca.\n",fam[r1].nom);
				fprintf(pArchivo,"%s ha vuelto de entre los muertos, ahora más fuerte que nunca.\n",fam[r1].nom);
				fam[r1].victorias++;
				fam[r1].vidas++;
				fam[r2].resurreccion=false;
				fam[r1].muerto=false;
			}
			else{
				printf("ERROR!!! en resurreción\n");
				debug(r1,r2,fam);
			}

			ciclos++;
			ciclosB=true;
/*			
		int error1=r1;
		printf("%d: %s, %d, %d \n bools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);
		error1=r2;
		printf("%d: %s, %d, %d \n bools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);
*/						
		}
		
		//vidas
		else if ((fam[r1].vida==true || fam[r2].vida==true) && (strcmp(fam[r1].nom,fam[r2].nom)!=0 && (strcmp(fam[r1].nom,"Resurrecion")!=0) && strcmp(fam[r2].nom,"Resurrecion" )!=0&& strncmp("La Gema",fam[r1].nom,6)!=0 && strncmp("La Gema",fam[r2].nom,6)!=0)){
			int item,player;
			
			if(fam[r1].vida==fam[r2].vida){
				printf("Error, en vidas, ambas son iguales\n");
				debug(r1,r2,fam);	
			}
			
			else if (fam[r1].item==true){
				item=r1;
				player=r2;
			}
			else if(fam[r2].item==true){
				item=r2;
				player=r1;
			}
			else{
				printf("Error en vidas, algo falla (no hay items)");
				debug(r1,r2,fam);	
			}
			fam[player].vidas++;
			fam[item].vida=false;
			printf("%s ha encontrado una vida, actualemente tiene %d vidas restantes.\n",fam[player].nom,fam[player].vidas);
			fprintf(pArchivo,"%s ha encontrado una vida, actualemente tiene %d vidas restantes.\n",fam[player].nom,fam[player].vidas);

			ciclos++;
			ciclosB=true;
/*			
		int error1=player;
		printf("%d: %s, %d, %d \n bools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);
		error1=item;
		printf("%d: %s, %d, %d \n bools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);
*/

		}
//Encontrar Gemas		
		else if ((fam[r1].item==true || fam[r2].item==true) && (fam[r1].item!=fam[r2].item)&&(fam[r1].realidad==true || fam[r1].mente==true || fam[r1].alma==true || fam[r1].espacio==true || fam[r1].poder==true || fam[r1].tiempo==true || fam[r2].realidad==true || fam[r2].mente==true || fam[r2].alma==true || fam[r2].espacio==true || fam[r2].poder==true || fam[r2].tiempo==true)&&(fam[r2].muerto==false && fam[r1].muerto==false)){

			int gem,player;
			
			if (fam[r1].item==true){
				gem=r1;
				player=r2;
			}
			else if (fam[r2].item==true){
				gem=r2;
				player=r1;
			}
			else{
				printf("Error con las gemas, ninguna es un item\n");
				debug(r1,r2,fam);
			}
			
			fam[player].victorias++;
			
			for (int a=0;a<6;a++){
				
				if (strcmp(fam[gem].nom,gemas[a])==0){
					switch(a){
						case 0:
						if (fam[gem].realidad==true){
					
						printf("%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fprintf(pArchivo,"%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fam[gem].realidad=false;
						fam[player].realidad=true;
						ciclos++;
						ciclosB=true;						
						break;
						}
						case 1:
						if (fam[gem].mente==true){
						printf("%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fprintf(pArchivo,"%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fam[gem].mente=false;
						fam[player].mente=true;						
						ciclos++;
						ciclosB=true;
						break;
						}
						case 2:
						if (fam[gem].alma==true){
						printf("%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fprintf(pArchivo,"%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fam[gem].alma=false;
						fam[player].alma=true;
						ciclos++;
						ciclosB=true;
						break;
						}
						case 3:
						if (fam[gem].espacio==true){
						printf("%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fprintf(pArchivo,"%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fam[gem].espacio=false;
						fam[player].espacio=true;
						ciclos++;
						ciclosB=true;
						break;
						}
						case 4:
						if (fam[gem].poder==true){
						printf("\n%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fprintf(pArchivo,"\n%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fam[gem].poder=false;
						fam[player].poder=true;
						ciclos++;
						ciclosB=true;
						break;
						}
						case 5:
						if (fam[gem].tiempo==true){
						printf("\n%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fprintf(pArchivo,"\n%s ha encontrado %s, ahora es más poderoso.\n",fam[player].nom,fam[gem].nom);
						fam[gem].tiempo=false;
						fam[player].tiempo=true;
						ciclos++;
						ciclosB=true;
						break;	
						}
					}
			}	}
	}
//Combate final	
		
		else if (fam[r1].vidas>0 && fam[r2].vidas>0 && fam[r1].item==false && fam[r2].item==false && fam[r1].muerto==false && fam[r2].muerto==false){
		ciclos++;
		ciclosB=true;
			int victoriasTotales=victorias[random1]+victorias[random2];
			int aleatorio =rand()% (victoriasTotales+2);
			int ganador,perdedor;
			bool gemas=false;
			 
			if (aleatorio <=victorias[random1]){
				ganador=r1;
				perdedor=r2;
			}
			else{
				ganador=r2;
				perdedor=r1;
			}
			
			//Comprobación si el perdedor tenía gemas:
			bool gemasW = true; //bool que escribe el string de "x ha derrotado a x" UNA ÚNICA VEZ, una vez se roba una gema, no se llama a la función hasta un nuevo ganador.
			bool arrayGemas[6];
			
				//Asiganmos al array todas las gemas para saber si el perdedro tenía alguna
				arrayGemas[0]=fam[perdedor].realidad;
				arrayGemas[1]=fam[perdedor].mente;
				arrayGemas[2]=fam[perdedor].alma;
				arrayGemas[3]=fam[perdedor].espacio;
				arrayGemas[4]=fam[perdedor].poder;
				arrayGemas[5]=fam[perdedor].tiempo;

			for (int a=0;a<6;a++){
				
				if (arrayGemas[a]==true)
					switch(a){
						case 0:
						//printf("%s ha derrotado a %s y le ha robado La Gema de la Realidad.\n",fam[ganador].nom,fam[perdedor].nom);
						if (gemasW==true)
							gemasWrite(ganador,perdedor,fam,pArchivo);
						gemasW=false;
						printf("la Gema de la Realidad, ");
						fprintf(pArchivo,"la Gema de la Realidad, ");
						fam[perdedor].realidad=false;
						fam[ganador].realidad=true;
						fam[ganador].victorias++;						
						gemas=true;
						break;
						
						case 1:
						if (gemasW==true)
							gemasWrite(ganador,perdedor,fam,pArchivo);
						gemasW=false;						
						//printf("%s ha derrotado a %s y le ha robado La Gema de la Mente.\n",fam[ganador].nom,fam[perdedor].nom);
						printf("la Gema de la Mente, ");
						fprintf(pArchivo,"la Gema de la Mente, ");
						fam[perdedor].mente=false;
						fam[ganador].mente=true;
						fam[ganador].victorias++;							
						gemas=true;						
						break;
						
						case 2:
						if (gemasW==true)
							gemasWrite(ganador,perdedor,fam,pArchivo);
						gemasW=false;
						//printf("%s ha derrotado a %s y le ha robado La Gema del Alma.\n",fam[ganador].nom,fam[perdedor].nom);
						printf("la Gema del Alma, ");
						fprintf(pArchivo,"la Gema del Alma, ");
						fam[perdedor].alma=false;
						fam[ganador].alma=true;
						fam[ganador].victorias++;	
						gemas=true;
						break;
						
						case 3:
						if (gemasW==true)
							gemasWrite(ganador,perdedor,fam,pArchivo);
						gemasW=false;
						//printf("%s ha derrotado a %s y le ha robado La Gema del Espacio.\n",fam[ganador].nom,fam[perdedor].nom);
						printf("la Gema del Espacio, ");
						fprintf(pArchivo,"la Gema del Espacio, ");
						fam[perdedor].espacio=false;
						fam[ganador].espacio=true;
						fam[ganador].victorias++;	
						gemas=true;
						break;
						
						case 4:
						if (gemasW==true)
							gemasWrite(ganador,perdedor,fam,pArchivo);
						gemasW=false;
						//printf("%s ha derrotado a %s y le ha robado La Gema del Poder.\n",fam[ganador].nom,fam[perdedor].nom);
						printf("la Gema del Poder, ");
						fprintf(pArchivo,"la Gema del Poder, ");
						fam[perdedor].poder=false;
						fam[ganador].poder=true;
						fam[ganador].victorias++;	
						gemas=true;
						break;
						
						case 5:
						if (gemasW==true)
							gemasWrite(ganador,perdedor,fam,pArchivo);
						gemasW=false;
						//printf("%s ha derrotado a %s y le ha robado La Gema del Tiempo.\n",fam[ganador].nom,fam[perdedor].nom);
						printf("la Gema del Tiempo, ");
						fprintf(pArchivo,"la Gema del Tiempo, ");
						fam[perdedor].tiempo=false;
						fam[ganador].tiempo=true;
						fam[ganador].victorias++;	
						gemas=true;
						break;

					}
			}
					//Si se han conseguido gemas, se borra parte del mensaje fina (quitar las comas)
				if (gemas==true){
					printf("\b\b.\n¡Un buen botín!\n");
					fprintf(pArchivo,"\b\b.\n¡Un buen botín!\n");
				}

			
					//Si se han conseguido gemas, se suman y restan los respectivos stats
					if (gemas==true){
						fam[ganador].victorias++;
						fam[perdedor].vidas--;
					
					//Si el perdedor muere, o sobrevive, se imprimen los mensajes
					if(fam[perdedor].vidas<=0){
						printf("%s murió tras el encuentro por las heridas.\n",fam[perdedor].nom);
						fprintf(pArchivo,"%s murió tras el encuentro por las heridas.\n",fam[perdedor].nom);
						restantes--;
						fam[perdedor].muerto=true;
						//printf("Quedan %d jugadores\n",restantes);
				}
				else{
					printf("%s ha sido derrotado, pero consiguió huir con el rabo entre las piernas.\nVidas restanes: %d\n",fam[perdedor].nom,fam[perdedor].vidas);
				
					fprintf(pArchivo,"%s ha sido derrotado, pero consiguió huir con el rabo entre las piernas.\nVidas restanes: %d\n",fam[perdedor].nom,fam[perdedor].vidas);
				}
			}
			
			//Si no hay gemas, se imprimen los mensajes sin gemas del resulta
			else{
				fam[ganador].victorias++;
				fam[perdedor].vidas--;
				
				if(fam[perdedor].vidas<=0){
					printf("%s ha muerto a manos de %s en un combate singular.\n",fam[perdedor].nom, fam[ganador].nom);
					fprintf(pArchivo,"%s ha muerto a manos de %s en un combate singular.",fam[perdedor].nom, fam[ganador].nom);
					restantes--;
					fam[perdedor].muerto=true;
					//printf("Quedan %d jugadores\n",restantes);
				}
				else{
					printf("%s ha sido vencido por %s, pero consiguió huir con el rabo entre las piernas. Le quedan %d vidas\n",fam[perdedor].nom,fam[ganador].nom,fam[perdedor].vidas);				
					fprintf(pArchivo,"%s ha sido vencido por %s, pero consiguió huir con el rabo entre las piernas. Le quedan %d vidas\n",fam[perdedor].nom,fam[ganador].nom,fam[perdedor].vidas);
				}
			}
			
			if(restantes<=nFamosos){
				vivos=0;
				for(int a=0;a<nFamosos;a++){
					if (fam[a].muerto!=true && fam[a].item==0){
					vivos++;
					//int error1=a;
					//debug que imprime a los supervivientes
					//printf("%d: %s, %d, %d \nbools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);	
					}

				}
			}
			if (ciclosB==true && vivos !=1){
				printf("\nVictorias:\n%.15s: %d, %.15s: %d\n",fam[r1].nom,fam[r1].victorias,fam[r2].nom,fam[r2].victorias);
				printf("\nHan pasado %d días y quedan %d supervivientes.\n\n",ciclos,vivos);
				
				fprintf(pArchivo,"\nVictorias:\n%.15s: %d, %.15s: %d\n",fam[r1].nom,fam[r1].victorias,fam[r2].nom,fam[r2].victorias);
				fprintf(pArchivo,"\nHan pasado %d días y quedan %d supervivientes.\n",ciclos,vivos);
				
			}
			if (vivos==1){
				for(int a=0;a<nFamosos;a++){
					if (fam[a].muerto!=true && fam[a].item==0){
						printf("\n\nEl único superviviente a esta guerra ha sido %s tras %d días de ardua batalla.\nENHONRABUENA!!!\n",fam[a].nom,ciclos);
						fprintf(pArchivo,"\n\nEl único superviviente a esta guerra ha sido %s tras %d días de ardua batalla\n¿Qué futuro nos deparará?\nENHONRABUENA!?!?\n",fam[a].nom,ciclos);
					}
				}	
			}
			
			//fclose(stdout);
			//fclose(pArchivo);


//LOGS-----------------------------------LOGS---------------------
	

		//esta parte del código está dedicada a guardar los registros individuales de los distintos eventos y flags

/*
	Imprime por pantalla cualquir jugador VIVO
			if (vivos==1){
				for(int a=0;a<nFamosos;a++){
					if (fam[a].muerto!=true && fam[a].item==0){
					int error1=a;				
					printf("\n\n%d: %s, %d, %d \nbools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);	
					}
				}				
			}
*/		


	//LOGS EN FICHEROS
//Activar/desactivar de logs sutituyendo el if (true) por false	
		}
	char nlogs[100];

		if (ciclosB==true){
			//Imprime una lsita de vivos
			
				sprintf(nlogs,"output/vivos/%d.txt",ciclos);
				
				logs = fopen(nlogs,"w");
				
				if (logs != NULL){
					
					for(int a=0;a<nFamosos;a++){
						if (fam[a].muerto!=true && fam[a].item==0){
							fprintf(logs,"%s\n",fam[a].nom);
						}									
					}
				}
				else
					printf(".--------------Error archivo log, %d ciclos\n",ciclos);				
				fclose(logs);					
			
					
			
			
			
				
				//Tabla de vivos con flgas
				sprintf(nlogs,"output/logs/vivos%d.txt",ciclos);
				logs = fopen(nlogs,"w");
				if (logs != NULL){
					for(int a=0;a<nFamosos;a++){
						if (fam[a].muerto!=true && fam[a].item==0){
						int error1=a;				
						fprintf(logs,"\n\n%d: %s, %d, %d \nbools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);	
						}				
					
					}
				}

				fclose(logs);
				
				//Tabla completa con flags
				sprintf(nlogs,"output/logs/todos%d.txt",ciclos);
				logs = fopen(nlogs,"w");
				if (logs != NULL){
					for(int a=0;a<nFamosos;a++){
						
						int error1=a;				
						fprintf(logs,"\n\n%d: %s, %d, %d \nbools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d\n\n",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);	
					}
				}
				fclose(logs);
		}//Fin if ciclosB==true	
				
			
		fclose(pArchivo);
		ciclosBucle++;
		//fclose(pRe);
	}//fin while
}//fin funcion



void debug (int r1, int r2, FAMOSO fam[]){
	int error1;
		printf("DEBUG\n");
		error1=r1;
		printf("%d: %s, %d, %d \nbools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d, muerto %d",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);
		error1=r2;
		printf("%d: %s, %d, %d \nbools: item %d, uso %d, realidad %d, mente %d, alma %d, espacio %d, poder %d, tiempo %d, vida %d, resurrecion %d,muerto %d",error1,fam[error1].nom,fam[error1].vidas,fam[error1].victorias,fam[error1].item,fam[error1].uso,fam[error1].realidad,fam[error1].mente,fam[error1].alma, fam[error1].espacio, fam[error1].poder,fam[error1].tiempo,fam[error1].vida, fam[error1].resurreccion, fam[error1].muerto);
		error1 = getchar();
}

void gemasWrite(int ganador, int perdedor, FAMOSO fam[], FILE *pArchivo){
	
			printf("%s ha derrotado a %s y le ha robado ",fam[ganador].nom,fam[perdedor].nom);
			fprintf(pArchivo,"%s ha derrotado a %s y le ha robado ",fam[ganador].nom,fam[perdedor].nom);
	
}