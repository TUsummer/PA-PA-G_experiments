/**
 * ################################################
 * ############### Request Operation ##############
 * ################################################
 *
 * Version: 1.0
 * File: request.h
 * Author: Jie Wang
 * Description: Request Operation
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/


#ifndef SRC_REQUEST_REQUEST_H_
#define SRC_REQUEST_REQUEST_H_

#include <list>
#include <stdio.h>

#include "../variables/variables.h"
#include "../struct/structs.h"
#include "../utils/random.h"


/*
 * FUNCTION: genRequests
 * INPUT: FileInfo && list
 * OUTPUT: none
 * (SIDE)EFFECTS: generate requests
 */
void genRequests(FileInfo files[NUM_FILES], list<RequestInfo> *requests);


/*
 * FUNCTION: allotTime2Request
 * INPUT: FileInfo
 * OUTPUT: none
 * (SIDE)EFFECTS: Allotted time to request(random)
 */
void allotTime2Request(RequestInfo *request);


/*
 * FUNCTION: allotTime2Request
 * INPUT: FileInfo
 * OUTPUT: none
 * (SIDE)EFFECTS: Allotted time to request(TimeWindow)
 */
void allotTime2Request(RequestInfo *request, int TWNum);


/*
 * FUNCTION: allotTime2Request
 * INPUT: list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: Allotted time to requests' list
 */
void allotTime2Request(list<RequestInfo> *requestsList);			//


#endif /* SRC_REQUEST_REQUEST_H_ */
