import os
import shutil
import sys

srcpath = os.getcwd()

argv = sys.argv
argc = len(sys.argv)

if argc >1:
    make_command = argv[1]
    if argc >2:
        out_path = argv[2]
    else:
        out_path = srcpath+"/../outs"
else:
    print "You Must set name command like: nmake,make,win32-make and so on"
    print "a command lick: python ConfigureProject.py nmake  "

out_path = os.path.normpath(out_path)
os.system("python CopyDirTree.py src/outs "+out_path)
#os.system("python CopyDirTree.py src/outs "+out_path+"gcc")

#write configure file
configure_file = open( "src/configure.pri.user","w" )
configure_file.write("###\n\n\n\n\n\n")
#configure_file.write("win32-g++{\n")
#configure_file.write("OUT__DIR__BASE__ ="+out_path+"gcc\n\n\n")
#configure_file.write("}else{\n")
configure_file.write("OUT__DIR__BASE__ ="+out_path+"\n\n\n")
#configure_file.write("}\n\n\n")
configure_file.write("MAKE__COMMAND__ ="+make_command+"\n\n\n")
configure_file.write("###\n\n\n\n\n\n")
configure_file.close()


print "ok!"
