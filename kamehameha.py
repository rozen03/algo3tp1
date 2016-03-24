#!/usr/bin/python
import sys 
sys.setrecursionlimit(10000)
import copy

# variable globales
BEST_KAMEHAMEHA = 9999
PARTIAL_KAMEHAMEHA = 0
SOLUTION = []

class Android():
    def __init__(self, posX, posY):
        self.posX = posX
        self.posY = posY
        self.state = 'active'   #activo o destruido con pos de quien lo destruyo
        self.kame = 0   #numero de kamehameha que lo destruyo 
    def __repr__(self):
        return "{x:%s, y:%s, state:%s, kame:%s}" % (self.posX, self.posY, self.state, self.kame)


enemies = []
enemies.append(Android(1,1))
enemies.append(Android(1,4))
enemies.append(Android(3,2))
enemies.append(Android(4,1))
enemies.append(Android(4,3))
enemies.append(Android(5,0))

REMAINING_ANDROIDS = len(enemies)

print 'Enemies: ' + str(enemies)

def horizontalDestroy(e):
    res = 0
    s = 'destroyed(%s,%s)' % (e.posX, e.posY)
    for x in enemies:
        if(x.posY == e.posY):
            if(x.state == 'active'):
                x.state = s
                x.kame = PARTIAL_KAMEHAMEHA
                res += 1
    return res  #cantidad destruida

def verticalDestroy(e):
    res = 0
    s = 'destroyed(%s,%s)' % (e.posX, e.posY)
    for x in enemies:
        if(x.posX == e.posX):
            if(x.state == 'active'):
                x.state = s
                x.kame = PARTIAL_KAMEHAMEHA
                res += 1
    return res

def horizontalRestore(e):
    res = 0
    s = 'destroyed(%s,%s)' % (e.posX, e.posY)
    for x in enemies:
        if(x.posY == e.posY):
            if(x.state == s):
                x.state = 'active'
                res += 1
    return res #cantidad restaurada

def verticalRestore(e):
    res = 0
    s = 'destroyed(%s,%s)' % (e.posX, e.posY)
    for x in enemies:
        if(x.posX == e.posX):
            if(x.state == s):
                x.state = 'active'
                res += 1
    return res       

def backtrack():
    global REMAINING_ANDROIDS
    global PARTIAL_KAMEHAMEHA
    global BEST_KAMEHAMEHA
    global SOLUTION
    if(REMAINING_ANDROIDS == 0):
        BEST_KAMEHAMEHA = PARTIAL_KAMEHAMEHA    #mejor solucion encontrada hasta ahora
        SOLUTION = copy.deepcopy(enemies)   
    else:
        for e in enemies:
            if(e.state == 'active'):    #poda: solo seguimos si no esta destruido
                if(PARTIAL_KAMEHAMEHA + 1 < BEST_KAMEHAMEHA):   #poda: a lo sumo es igual a la mejor solucion encontrada
                    PARTIAL_KAMEHAMEHA += 1
                    res = horizontalDestroy(e)  #destruimos todos los androides en la misma fila
                    REMAINING_ANDROIDS -= res
                    backtrack()
                    res = horizontalRestore(e)  #volmemos a como estaba antes
                    REMAINING_ANDROIDS += res
                    PARTIAL_KAMEHAMEHA -= 1
                if(PARTIAL_KAMEHAMEHA + 1 < BEST_KAMEHAMEHA):
                    PARTIAL_KAMEHAMEHA += 1
                    res = verticalDestroy(e)    #destruimos todos los androides en la misma columna
                    REMAINING_ANDROIDS -= res
                    backtrack()
                    res = verticalRestore(e)    #volvemos a como estaba antes
                    REMAINING_ANDROIDS += res
                    PARTIAL_KAMEHAMEHA -= 1

backtrack()
print "\n"
print 'Output:'
print BEST_KAMEHAMEHA
output = [''] * BEST_KAMEHAMEHA
for x in sorted(SOLUTION,key=lambda android: android.kame):
    output[x.kame -1] = str(output[x.kame -1])+str(x.posX) + ' ' + str(x.posY) + ' '    
for pos, item in enumerate(output):
    print str(pos +1) + ' ' + item 
