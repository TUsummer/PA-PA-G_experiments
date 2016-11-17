/**
 * ################################################
 * ################# CSV Operation ################
 * ################################################
 *
 * Version: 1.0
 * File: csvOper.h
 * Author: Jie Wang
 * Description: CSV Operation
 * Date: 2016-01-07
 * Copyright (C) 2016 NAOC-TJUCS
 **/


#ifndef SRC_CSVOPER_H_
#define SRC_CSVOPER_H_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <list>
#include <fstream>

#include "../struct/structs.h"

using namespace std;


/*
 * FUNCTION: writeCSV
 * INPUT: File Path && list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: Write requestsList to CSV
 */
void writeCSV(string filePath, list<RequestInfo> requestsList);


/*
 * FUNCTION: writeCSV
 * INPUT: File Path && record
 * OUTPUT: none
 * (SIDE)EFFECTS: Write record to CSV
 */
void writeCSV(string filePath, string record);


/*
 * FUNCTION: readCSV
 * INPUT: File Path && list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: read record from CSV
 */
void readCSV(string filePath, list<RequestInfo> *requestsList);


#endif /* SRC_CSVOPER_H_ */
