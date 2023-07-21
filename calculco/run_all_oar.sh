#OAR -n Wilf walk
#OAR -l /nodes=1/core=1/cpu=1,walltime=2:0:0
#OAR -q besteffort
#OAR -t besteffort
#OAR -t idempotent
#OAR -O oar_stdout/walk.%jobid%.stdout
#OAR -E oar_stderr/walk.%jobid%.stderr
#OAR --array-param-file /nfs/home/lmpa/jfromentin/wilf/parameters
/nfs/home/lmpa/jfromentin/wilf/run_walk "$@" 3600


