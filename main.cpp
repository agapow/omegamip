/************************************/
/*	main.cpp 17th November 2005		*/
/*	Part of omegaMap v0.5			*/
/*	(c) Danny Wilson.				*/
/*	www.danielwilson.me.uk			*/
/************************************/

#include "random.h"
#include "om_incl.h"

#include "om_app.h"


int main (int argc, char* argv[]) {
	if (argc < 2) {
		error ("SYNTAX: ini-filename [options...]");
	}

	int proc_id = 0;
	
#ifdef MPI_ENABLED
	int error_code, num_procs;

	// MSG ("Attempting MPI initialisation ...");
	error_code = MPI_Init (&argc, &argv);
	if (error_code != MPI_SUCCESS) {
		MSG ("Problem initializing MPI");
		exit (1);
	}
	
	error_code = MPI_Comm_size (MPI_COMM_WORLD, &num_procs);
	if (error_code != MPI_SUCCESS) {
		MSG ("Problem getting the number of processors");
		exit (1);
	}

	error_code = MPI_Comm_rank (MPI_COMM_WORLD, &proc_id);
	if (error_code != MPI_SUCCESS) {
		MSG ("Problem getting processors rank");
		exit (1);
	}

#endif

	if (proc_id == 1) MSG ("Creating application ...");
	omegaMap app;
	Random rng;
	if (proc_id == 1) MSG ("Initialising application (setting params and allocating memory) ...");
	app.initialize (argc - 1, argv + 1, argv[1], rng);
	if (proc_id == 1) MSG ("Starting run ...");
	app.go();
	if (proc_id == 1) MSG ("Finished.");

#ifdef MPI_ENABLED
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	
#	endif


	//MSG("at end of prog");
	return 0;
}

