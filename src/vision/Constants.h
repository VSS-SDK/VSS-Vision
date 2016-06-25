/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//! This file contains all the constants used in all software

#define RELEASE			"VSS-Vision"

#define FIELD_WIDTH 	150		// Centimetros
#define FIELD_HEIGHT	130		// Centimetros
#define MASS_ROBOT		200		// Gramas
#define MASS_BALL		42		// Gramas
#define QTD_COLORS		8		// Quantidade de cores que podem ser calibradas

// Visão Computacional
#define AREA_MIN		30		// constante que define a area minima de busca dos robos
#define AREA_MAX		700		// constante que define a area maxima de busca dos robos
#define AREA_CUT		30		// constante que define a imagem cortada
#define PROPORTION_MIN	0.70	// constante que define o quanto a figura pode sair do padrao de quadrado
#define PROPORTION_MAX	1.35 	// constante que define o quanto a figura pode sair do padrao de quadrado
#define DISTANCE_MIN  	35		// constante que define a distancia minima entre as cores para ser considerado um robo 
//#define DEBUG 					// Desenho na Visão

// Debug valgrind --leak-check=yes ./SirSoccer

#endif