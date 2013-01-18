General information
=========

This project only implements one of the MPI function — [MPI_Bcast].

It is usefull and faster than MPI realization on the data arrays with number of elements more or equal to 1024, in other cases MPI realization is preferred.

It was tested only on Regatta machine. Results may vary on BlueGene architectures

Typical compareness of RMB and MPI realizations looks like here (left is length of data array and bottom is time to broadcast it 1000 times):

![compare of realizations](https://docs.google.com/spreadsheet/oimg?key=0AoMv6fev4a2AdEVGZVROMTBkTEZFbUM5Rl9UcTdOSkE&oid=14&zx=e230ssmrywax)

Compile
=======
mpicc *.c -o bin/RMB_Bcast

License
=======
- You can use it free under terms of General Public License for individual use and non-commercial open-sourse projects. 
- You are ***prohibited*** to use this program and its parts without testing in solutions that operate on large amounts of sensitive data in order to prevent loss and / or damage.

[MPI_Bcast]:http://www.mcs.anl.gov/research/projects/mpi/www/www3/MPI_Bcast.html
