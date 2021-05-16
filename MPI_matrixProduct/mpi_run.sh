#!/bin/bash

#PBS -l nodes=10:ppn=1,walltime=00:00:30
#PBS -N mpi_wtime
#PBS -q staff
#PBS -d /mnt/zfs-pool/home/curso11/wtime/
#PBS -o wtime.log
#PBS -j oe
#PBS -V
#PBS -S /bin/bash

source $MODULESHOME/init/bash
module purge
module load Compilers/Parallel-Studio-XE-2018

NPROCS=`wc -l < $PBS_NODEFILE`
cat ${PBS_NODEFILE} | sort -u > $PBS_O_WORKDIR/machines.LINUX
mpirun -np $NPROCS -machinefile machines.LINUX ./wtime 10 10 10 > wtime.out
