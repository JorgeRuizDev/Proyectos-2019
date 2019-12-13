# -*- coding: utf-8 -*-
import tweepy as tp
import time
import os


#credenciales y login
consumer_key = ''
consumer_secret = ''
access_token = ''
access_secret = ''

consumer_key = '-'
consumer_secret = '-'
access_token = '-'
access_secret = '-'

auth = tp.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_secret)
api = tp.API(auth)

#--------------------------------------------------

#bucle que postea el bot
bucle = 0
while True:
	#manipulacion del archivo
	bucle = bucle+1


#Carga modificación y actualización del archivo y la variable que almacenan el número de días sin vídeo en el canal principal	
	f= open("dias.txt","r+")
	diasString =f.read()
	dias = int(diasString) #convierte el string a int
	f.close()

	f= open ("dias.txt","w") #abre un archivo vacio
	dias = dias+1 #suma un dia
	f.write(str(dias))
	f.close()	
	
	
#Carga modificación y actualización del archivo y la variable que almacenan el número de días sin vídeo en el canal secundario
	f= open("diasSecundario.txt","r+")
	diasString =f.read()
	diasSecundario = int(diasString) #convierte el string a int
	f.close()

	f= open ("dias.txt","w") #abre un archivo vacio
	diasSecundario = diasSecundario+1 #suma un dia	
	f.write(str(diasSecundario))
	f.close()
	

	#creacion del tweet
	nbucles= "Numero de bucles: %d" % bucle
	print(nbucles)
	
	ndias= "Numero de dias principal: %d" % dias
	print(ndias)
	
	status = "Revk08 lleva %d días sin subir vídeo y %d días sin subir gaymplei\n\nVuelve a casa riuk, te echamos de menos <3" % (dias , diasSecundario)
	
	print status
	api.update_status(status)
	time.sleep(86400) #tiempo en s que espera el bot

 
