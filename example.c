#include	"fsom.h"

#include	<alloca.h>
#include	<stdio.h>

#define 	VECTORS 		10
#define 	INPUTS 		    20
#define 	OUT_ROWS 		10
#define 	OUT_COLS 		10
#define 	TRAIN_STEPS 	30

int
main ( int argc, char *argv[] )
{
	size_t i, j, x, y;
	double step = 0.0;
	double **data = NULL;
	som_network_t *net = NULL;

	data = (double **) alloca ( INPUTS * sizeof ( double* ));

	for ( i=0, step = 0.0; i < INPUTS; ++i, step += 0.1 )
	{
		data[i] = (double *) alloca ( VECTORS * sizeof ( double ));

		for ( j=0; j < VECTORS; ++j )
		{
			data[i][j] = step;
		}
	}

	net = som_network_new ( INPUTS, OUT_ROWS, OUT_COLS );

	if ( !net )
	{
		printf( "ERROR: som_network_new failed.\n" );
		return 1;
	}

	som_init_weights ( net, data, INPUTS );
	som_train ( net, data, VECTORS, TRAIN_STEPS );

	for ( i=0; i < INPUTS; ++i )
	{
		som_set_inputs ( net, data[i] );
		som_get_best_neuron_coordinates ( net, &x, &y );
	//	printf ( "best coordinates [%u]: %u,%u\n", i, x, y );
	}

	som_network_destroy ( net );
}			
