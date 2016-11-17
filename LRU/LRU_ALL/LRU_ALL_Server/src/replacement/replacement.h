/**
 * ################################################
 * ############# Replacement Strategy #############
 * ################################################
 *
 * Version: 1.0
 * File: replacement.h
 * Author: Jie Wang
 * Description: Replacement Strategy
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#ifndef SRC_REPLACEMENT_REPLACEMENT_H_
#define SRC_REPLACEMENT_REPLACEMENT_H_

#include <iostream>
#include <stdio.h>
#include "fitsio.h"
#include <string>
#include <sstream>
#include "stdlib.h"
#include "string.h"

#include <sys/file.h>
#include <unistd.h>
#include <sys/time.h>

#include "../variables/variables.h"

using namespace std;


/*
 * FUNCTION: removeFile
 * INPUT: file path
 * OUTPUT: none
 * (SIDE)EFFECTS: Remove File
 */
void removeFile(string fileName);


/*
 * FUNCTION: extractFile2Cache
 * INPUT: file path && Start&&End Coordinates
 * OUTPUT: double
 * (SIDE)EFFECTS: extract File from HDD to SSD
 */
double extractFile2Cache(string filename, int sx, int sy, int ex, int ey);


#endif /* SRC_REPLACEMENT_REPLACEMENT_H_ */
