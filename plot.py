#! /usr/bin/python
import argparse
import os
import sys
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np

fileA = os.getcwd()+'/informe/data/p'
fileB = os.getcwd()+'/informe/data/p'
fileW = os.getcwd()+'/informe/data/p'

def valid_file(parser, arg):
    global fileA
    global fileB
    global fileW
    fileA += arg+'-average.txt'
    fileB += arg+'-best.txt'
    fileW += arg+'-worst.txt'
    if not os.path.isfile(fileA):
        parser.error("The file %s does not exist!" % fileA)
    elif not os.path.isfile(fileB):
        parser.error("The file %s does not exist!" % fileB)
    elif not os.path.isfile(fileW):
        parser.error("The file %s does not exist!" % fileW)
    else:
        return arg

parser = argparse.ArgumentParser(description="Generates a plot for files in data directory")
parser.add_argument('-p', '--problem', required=True, type=lambda x: valid_file(parser,x), help='problem number', metavar='FILE')
args = parser.parse_args()
output = os.getcwd()+'/informe/imgs/p'+args.problem

with open(fileA) as file:
    label = []
    average = []
    for line in file:
        words = line.split()
        label.append(words[0])
        average.append(words[1])

with open(fileB) as file:
    best = []
    for line in file:
        words = line.split()
        best.append(words[1])

with open(fileW) as file:
    worst = []
    for line in file:
        words = line.split()
        worst.append(words[1])
t = np.arange(1., 9., 1.)
plt.figure(figsize=(15,5))
best = [float(i) for i in best]
average = [float(i) for i in average]
worst = [float(i) for i in worst]
x = [int(i) for i in label]
sub1 = plt.subplot(2,1,1)
sub1.set_xticks(x)
sub1.plot(x,best,color='red',linewidth=2.5,label="Best")
sub1.plot(x,average,color='green',linewidth=2.5,label="Average")
sub1.plot(x,worst,color='blue',linewidth=2.5,label="Worst")
y = [pow(i,i+2) for i in x]
sub1.plot(x,y,color='yellow', linewidth=2.5,label="N^(N+2)")
sub1.legend(loc='upper left', frameon=False)
sub1.grid()
sub1.set_yscale('log')
#plt.show()
plt.savefig(output+"."+"png")

