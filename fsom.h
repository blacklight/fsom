/*
 * =====================================================================================
 *
 *       Filename:  neural_som.h
 *
 *    Description:  Header file for neural_som mini-library
 *
 *        Version:  0.1
 *        Created:  15/10/2010 15:31:50
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

#ifndef 	__NEURAL_SOM_H
#define 	__NEURAL_SOM_H

#include	<stddef.h>
#include	<time.h>

#define TAYLOR_LAMBERT_ELEMENTS 	1001
#define TAYLOR_LAMBERT_LAST_ELEMENT 1000

#ifndef INLINE
#	define INLINE __inline__ __attribute__((always_inline))
#endif

typedef struct  {
	double                 output;
	double                 input;

	struct som_synapsis_s  **synapses;
	size_t                 synapses_count;
} som_neuron_t
__attribute__ ((aligned));;

typedef struct som_synapsis_s  {
	som_neuron_t    *neuron_in;
	som_neuron_t    *neuron_out;
	double          weight;
} som_synapsis_t
__attribute__ ((aligned));

typedef struct  {
	som_neuron_t    **neurons;
	size_t          neurons_count;
} som_input_layer_t
__attribute__ ((aligned));

typedef struct  {
	som_neuron_t    ***neurons;
	size_t          neurons_rows;
	size_t          neurons_cols;
} som_output_layer_t
__attribute__ ((aligned));

typedef struct  {
	som_input_layer_t   *input_layer;
	som_output_layer_t  *output_layer;
	double              T_learning_param;
	time_t              serialization_time;
	double				alphas[TAYLOR_LAMBERT_ELEMENTS];
	double			    mus[TAYLOR_LAMBERT_ELEMENTS];
} som_network_t
__attribute__ ((aligned));

void                 som_network_destroy ( som_network_t* );
void                 som_set_inputs ( som_network_t*, double* );
void                 som_train ( som_network_t*, double**, size_t, size_t );
void                 som_serialize ( som_network_t*, const char* );
void                 som_init_weights ( som_network_t*, double**, size_t );
double               som_get_best_neuron_coordinates ( som_network_t*, size_t*, size_t* );
som_network_t*       som_deserialize ( const char* );
som_network_t*       som_network_new ( size_t, size_t, size_t );

#endif

