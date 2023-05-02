#!/bin/sh
#SBATCH --constraint=moles
#SBATCH --ntasks-per-node=20
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=1G

./3way-pthread_slurm