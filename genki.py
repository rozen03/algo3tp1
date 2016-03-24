#!/usr/bin/python
from math import log
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import random
#Generador de puntos random
global enemigos
global T
global N
N=50
T=10
maximum = 10000
enemigos =  [0 for x in range(N)] 
maxX =maximum
minY = 1
fig1 = plt.gca()
for i in range(N):
	x = random.randint(random.randint(maxX/(N-i),maxX),maxX)
	y = random.randint(minY,random.randint(minY,maximum/(N-i) + minY))
	enemigos[i] = (x,y)
	maxX=x
	minY=y 
##esto era pra printearlo en un grafico, no darle bola	
#ax1 = fig1.add_subplot(111, aspect='equal')
# fig1.add_patch(
#     patches.Rectangle((0,0),
#         enemigos[0][0],
#         enemigos[0][1],   # (x,y)
#         #1,          # width
#         #1,          # height
#          facecolor="blue",
#     )
#)
#testList2 = [(elem1, log(elem2)) for elem1, elem2 in enemigos]
#plt.scatter(*zip(*testList2))
#plt.show()
def se_matan(i,j):
	global T
	global enemigos
	#return ((enemigos[i][0] <= enemigos[j][0]+ T) & ((enemigos[i][1] ) <= enemigos[j][1]+T)) | ((enemigos[j][0] <= enemigos[i][0]+ T) & ((enemigos[j][1] ) <= enemigos[i][1]+T))
	return mata(i,j) | mata(j,i)
def mata(i,j):
	global T
	global enemigos
	return ((enemigos[j][0] <= enemigos[i][0]+ T) & ((enemigos[j][1] ) <= enemigos[i][1]+T))
def si_la_tiro_aca_mueren(i):
	global N
	global T
	global enemigos
	#hasta cual mata
	hasta=i
	desde=i
	while hasta<N and mata(i,hasta):
		hasta= hasta+ 1
	#desde cual mata
	while 0<desde and mata(i,desde):
		desde=desde -1
	return (desde,hasta-1)	



print "Enemigos:"
print enemigos
#i=1
sols = []
i=0
while i <N-1:
	j=i
	while ((j<N) and mata(j,i)):
		j+=1
	j-=1
	mueren_con_j = si_la_tiro_aca_mueren(j)
	sols.append(enemigos[j])
	i=mueren_con_j[1]+1
print "soluciones: ",sols
print  "#Soluciones: ",len(sols)
