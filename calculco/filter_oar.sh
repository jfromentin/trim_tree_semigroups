#OAR -n Wilf fileter
#OAR -l /nodes=1/core=128/cpu=1,walltime=20:0:0
#OAR -p host="orval14"
#OAR -q cimpa
#OAR -t idempotent
#OAR -O oar_stdout/filter.%jobid%.stdout
#OAR -E oar_stderr/filter.%jobid%.stderr

sh /nfs/home/lmpa/jfromentin/wilf/filter.sh

