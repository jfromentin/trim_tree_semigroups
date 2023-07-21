import os
import sys
import struct

def read_results(f):
    res=[]
    file=open("results/"+f,'rb')
    while True:
        b=file.read(8)
        if not b:
            break
        n=struct.unpack('Q',b)[0]
        res.append(n)
    file.close()
    return res

def write_results(res,f):
    file=open(f,'wb')
    for n in res:
        b=struct.pack('Q',n)
        file.write(b)
    file.close()
    
def merge_results(res,temp):
    if res==None:
        return temp
    else:
        for i in range(len(res)):
            res[i]+=temp[i]
        return res
    
if __name__=="__main__":
    res=None
    print("---------------")
    print(" Merge results ")
    print("---------------")
    files=os.listdir("results")
    for f in files:
        #print(f)
        temp=read_results(f)
        res=merge_results(res,temp)
    print(res)
    os.system("rm results/*")
    write_results(res,"results/main")
