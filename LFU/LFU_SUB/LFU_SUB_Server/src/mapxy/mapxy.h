/**
 * ################################################
 * ################ Map Coordinates ###############
 * ################################################
 *
 * Version: 1.0
 * File: file.h
 * Author: Jie Wang
 * Description: Initialize File Info
 * Date: 2016-01-05
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#ifndef SRC_MAPXY_MAPXY_H_
#define SRC_MAPXY_MAPXY_H_


#include "../variables/variables.h"


/*
 * FUNCTION: mapXY
 * INPUT: Start&&End Coordinates
 * OUTPUT: int*
 * (SIDE)EFFECTS: Map coordinates by accuracy
 */
int * mapXY(int startx, int starty, int endx, int endy);


#endif /* SRC_MAPXY_MAPXY_H_ */
