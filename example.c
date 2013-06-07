/*
 * =====================================================================================
 *
 *       Filename:  example.c
 *
 *    Description:  Examle file to benchmark fsom library.
 *
 *        Version:  0.1
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BlackLight (http://blacklight.gotdns.org), <blacklight@autistici.org>
 *    Contributor:  evilsocket (http://www.evilsocket.net), <evilsocket@gmail.com>
 *        Licence:  BSD-3
 *
 * =====================================================================================
 */

/*
 * Copyright (c) 2010, Fabio "BlackLight" Manganiello
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the the developers nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE DEVELOPERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include	"fsom.h"

#include	<alloca.h>
#include	<stdio.h>
#include 	<sys/time.h>

static unsigned long prev_uticks = 0;

static unsigned long get_uticks(){
    struct timeval ts;
    gettimeofday(&ts,0);
    return ((ts.tv_sec * 1000000) + ts.tv_usec);
}

static void start_timer(){
	prev_uticks = get_uticks();
}

static void print_timing( const char *msg ){
	#define MS_DELTA (1000.0)
	#define SS_DELTA (MS_DELTA * 1000.0)
	#define MM_DELTA (SS_DELTA * 60.0)
	#define HH_DELTA (MM_DELTA * 60.0)

	double ticks = get_uticks() - prev_uticks;

	if( ticks < MS_DELTA ){
	   printf( "%s\t : %lf us\n", msg, ticks );
	}
	else if( ticks < SS_DELTA ){
	   printf( "%s\t : %lf ms\n", msg, ticks / MS_DELTA );
	}
	else if( ticks < MM_DELTA ){
	   printf( "%s\t : %lf s\n", msg, ticks / SS_DELTA );
	}
	else if( ticks < HH_DELTA ){
	   printf( "%s\t : %lf m\n", msg, ticks / MM_DELTA );
	}
	else{
	   printf( "%s\t : %lf h\n", msg, ticks / HH_DELTA );
	}

	start_timer();
}

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

	start_timer();

	net = som_network_new ( INPUTS, OUT_ROWS, OUT_COLS );

	if ( !net )
	{
		printf( "ERROR: som_network_new failed.\n" );
		return 1;
	}

	print_timing( "Network Creation" );

	som_init_weights ( net, data, INPUTS );
	som_train ( net, data, VECTORS, TRAIN_STEPS );

	print_timing( "Network Training" );

	for ( i=0; i < INPUTS; ++i )
	{
		som_set_inputs ( net, data[i] );
		som_get_best_neuron_coordinates ( net, &x, &y );
	//	printf ( "best coordinates [%u]: %u,%u\n", i, x, y );
	}

	print_timing( "Input Recognition" );

	som_network_destroy ( net );

	print_timing( "Network Destruction" );
}			
