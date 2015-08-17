import os
import shutil
import sys

def _copy(ffile,tfile):
    isfe = os.path.exists(ffile)

    if not isfe:
        print "can not find : "+ffile
        return

    if os.path.exists(tfile):
        fst =  os.stat(ffile)
        tst =  os.stat(tfile)
        if fst.st_size==tst.st_size:
            if abs(fst.st_mtime==tst.st_mtime)>0.01:
                shutil.copy2(ffile,tfile)
        else:
            shutil.copy2(ffile,tfile)
    else:
        shutil.copy2(ffile,tfile)

def copyDir(src,tar):
    src = os.path.normpath(src)
    tar = os.path.normpath(tar)
    if os.path.exists(src):
        if not os.path.exists(tar):
            os.makedirs(tar)
        if os.path.exists(tar):
            for parent,dirnames,filenames in os.walk(src):
                for dirname in dirnames:
                    _p = parent[len(src)+1::]
                    _parent = tar+"/"+_p
                    _dn = os.path.join(_parent,dirname)
                    if not os.path.exists(_dn):
                        os.makedirs(_dn)
                    
                for filename in filenames:
                    _p = parent[len(src)+1::]
                    _parent = tar+"/"+_p
                    _copy(os.path.join(parent,filename),os.path.join(_parent,filename)  )

if __name__=="__main__":
    argv = sys.argv
    if len(argv)>2:
        copyDir(argv[1],argv[2])
    else:
        print "input error!"
    
