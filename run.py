import os
import sys

def make(gmax):
    os.chdir("src")
    os.system("make clean > /dev/null")
    os.system("make GMAX="+repr(gmax)+" > /dev/null")
    os.chdir("../")

def init():
    os.system("./init_files > /dev/null")
    todo=os.listdir("todo")
    print("There is",len(todo),"files to treat");

if __name__=="__main__":
    if(len(sys.argv)!=2):
        print("Argument error")
        exit(-1)
    gmax=int(sys.argv[1])
    print("gmax =",gmax)
    make(gmax)
    init()
    os.system("oarsub -S /nfs/home/lmpa/jfromentin/wilf/filter.sh")
    #run(timeout)
    
    
    
    
