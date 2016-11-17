/**
 * ################################################
 * ############### Response Operation #############
 * ################################################
 *
 * Version: 1.0
 * File: response.h
 * Author: Jie Wang
 * Description: Response Operation
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/


#ifndef SRC_RESPONSE_RESPONSE_H_
#define SRC_RESPONSE_RESPONSE_H_

#include <iostream>
#include <stdio.h>
#include "fitsio.h"
#include "string"
#include <sstream>
#include "stdlib.h"
#include <sys/time.h>

#include "../variables/variables.h"

using namespace std;


/*
 * FUNCTION: response
 * INPUT: filename && Start&&End Coordinates
 * OUTPUT: double
 * (SIDE)EFFECTS: response to user
 */
double response(string filename, int sx, int sy, int ex, int ey, int x0, int y0, string path);


#endif /* SRC_RESPONSE_RESPONSE_H_ */
