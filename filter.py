import os
import sys

if __name__=="__main__":
    todo=os.listdir("todo")
    print("=> Filter <=")
    print("in :",len(todo))
    todo_flat=' '.join(todo)
    cmd="parallel ./run_walk ::: "+todo_flat+" ::: 3600"
    os.system(cmd)
    todo2=os.listdir("todo")
    rem=set(todo).intersection(todo2)
    print("rem :",len(rem))
    print("done :",len(todo)-len(rem))
    print("new :",len(todo2)-len(rem))


    
    
    
    
