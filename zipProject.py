import os
import os.path
import zipfile

rootdir = os.getcwd()
rootsrc = rootdir+"/src"

if os.path.exists(rootsrc+"/configure.pri"):
    os.remove(rootsrc+"/configure.pri")

zf = zipfile.ZipFile('project.zip', 'w' ,zipfile.ZIP_DEFLATED)

for parent,dirnames,filenames in os.walk(rootsrc):
    for filename in filenames:
        parent_ = parent
        parent_ = parent_.replace('\\','/')
        parent_ = parent_.split('/')
        if ( '.git' in parent_ ):
            continue
        parent_ = parent[len(rootdir)+1::]
        outfile = os.path.join(parent_,filename)
        ftemp,fext = os.path.splitext(filename)
        if not (fext=='.user') :
            print outfile
            zf.write(outfile)

for filename in os.listdir(rootdir):
    ftemp,fext = os.path.splitext(filename)
    if ((fext==".py")||(fext==".pro")):
        print filename
        zf.write(filename)

zf.close()
