/**
 * ################################################
 * ############# Capacity Calculation #############
 * ################################################
 *
 * Version: 1.0
 * File: capacity.h
 * Author: Jie Wang
 * Description: Get Capacity of Cache Disks
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/


#ifndef SRC_CAPACITY_CAPACITY_H_
#define SRC_CAPACITY_CAPACITY_H_

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <string>
#include "../variables/variables.h"
using namespace std;


/*
 * FUNCTION: Get Capacity of Cache Disks
 * INPUT: Disk's Path
 * OUTPUT: Disk's Capacity
 * (SIDE)EFFECTS: Get Capacity of Cache Disks
 */
int getCapacity(string path);


/*
 * FUNCTION: getFileSize
 * INPUT: File's Path
 * OUTPUT: File's Size
 * (SIDE)EFFECTS: Get Size of File
 */
int getFileSize(string path);


#endif /* SRC_CAPACITY_CAPACITY_H_ */
