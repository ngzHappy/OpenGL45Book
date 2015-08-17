import sys
import os
import random

width = sys.argv[1]
height = sys.argv[2]
fileName = sys.argv[3]

command_0= 'python createPNG.py ' + width +' ' + height+' '

command_1='%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)
command_2=' '+fileName+"MouseON.png"
os.system( command_0+command_1+command_2 )

command_1='%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)
command_2=' '+fileName+"MouseOFF.png"
os.system( command_0+command_1+command_2 )

command_1='%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)+' '+'%d'%random.randint(0,255)
command_2=' '+fileName+"MousePressed.png"
os.system( command_0+command_1+command_2 )








