#!/usr/bin/python
import math

N = 10

global matriz_de_test 
global bando_uno
global bando_dos
def test():
	global matriz_de_test
	global bando_uno
	global bando_dos
	for i in bando_uno:
		for j in bando_dos:
			matriz_de_test[i][j]=0
	for i in bando_dos:
		for j in bando_uno:
			matriz_de_test[i][j]=0
matriz_de_test = [[0 for x in range(N)] for x in range(N)] 




#ESTE ES EL ALGORITMO
for x in range(N):
	for y in range(N):
		matriz_de_test[x][y] = 1
lista_guerreros = range(N)
print "guerreros", lista_guerreros
rango =range(1,int(math.log(N,2))+2)
for i in rango:
	bando_uno = [x for x in lista_guerreros if x % (2**(i)) < int(2**i)/2]
	bando_dos = [x for x in lista_guerreros if x % (2**(i)) >= int(2**i)/2]
	print  bando_uno, bando_dos
	#test()
#FIN DEL ALGORITMO




#for x in range(N):
#	print matriz_de_test[x]