# -*- coding: utf-8 -*-
import tweepy as tp
import time
import os

#import de la api para generar un enlace con las vidas
import sys
sys.path.insert(0, './lib')
from pasteee import Paste

#credenciales y login de Twitter
consumer_key = '-'
consumer_secret = '-'
access_token = '-'
access_secret = '-'
auth = tp.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_secret)
api = tp.API(auth)

#--------------------------------------------------

f = open("./output/info.txt","r")
nJugadores = f.read()
f.close ()
nJugadores=int(nJugadores)

status="Revk08, un dios omnipresente está sufriendo una rebelión, %d persones no apoyan que sus maravillas audiovisuales sean de visionado obligatorio, lo consideran... ADOCTRINAMIENTO, y consideran 'The End of Super Meat Boyi un insulto" %nJugadores
#api.update_status(status)
status="Para muchos, Revk no es más que un pringaillo incapaz de matar a una mosca, algo que deja una puerta abierta...\n Obtener las 6 piedras mágicas y convertirse en el nuevo youtuber #1 imponiendo sus ideales para controlar a la población."
#status="Para muchos, revk no es más que un debilucho, pero... ¿quién es el más fuerte?\nPor defecto REVK es el más fuerte, pero distintos items han aparecido a lo largo del mundo, y aquel que salga victorios más veces, estará más curtido en batalla. Cualquiera puede ganar "
#api.update_status(status)
status="¿Quién será el mas fuerte?, ¿Quién conseguirá ese Epic Victory Royale?, Revk es el jugador más fuerte, pero cualquiera que aumente su pode por medio de las batallas podrá derrotarle.\n\n ¡Qué comience que el juego!"
#api.update_status(status)
status="Los combates"

ciclosDia=0	
while True:
	ciclosDia = ciclosDia + 1

	#manipulacion del archivo
	
	#Lectura de días
	f= open("dias.txt","r+")
	diaString =f.read()
	dia = int(diaString) #convierte el string a int
	f.close()
	
	#Incrementa en 1 el ciclo de días y lo almacena en el archivo
	f= open ("dias.txt","w") #abre un archivo vacio
	dia = int(diaString)
	dia = dia+1 #suma un dia
	f.write(str(dia))
	f.close()
	
	#Dirección del archivo dinamico
	dirTweet = "./output/%d.txt" % dia
	dirVivos = "./output/vivos/%d.txt" % dia
	
	#Tratamiento del archivo que envía el Tweet con el combate
	archivoTweet=open (dirTweet,"r")
	status = archivoTweet.read()
	archivoTweet.close()
	print(status)
	#creacion del tweet
	#print(archivoTweet)


	#cada 5 días de batalla ,se publica una lista con los supervivientes
	if dia % 5 == 0:
		
		#Cargamos el archivo entero en una variable
		archivoVivos = open (dirVivos,"r")
		listaVivos = archivoVivos.read()
		#print (listaVivos)
		archivoVivos.close()
		
		#Subimos el archivo con la api Pasteee y recogemos la salida (Contiene el enlace)
		paste = Paste(listaVivos, private=False, desc="Twitter War Bot", views=100)
		paste = str(paste) #Conversión de la salida a string para poder recortarla
		enlaceRecortado = paste[90:116]
		status = "Aquí están los más valientes\n\nLista con los supervivientes: %s" %enlaceRecortado
		print status
	#api.update_status(status)
	if ciclosDia==15:
		ciclosDia=0
		time.sleep(36000)
	else:
		time.sleep(3600) #tiempo en s que espera el bot
	
	

 
