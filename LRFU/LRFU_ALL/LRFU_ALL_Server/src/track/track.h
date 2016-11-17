/**
 * ################################################
 * ############### Track Operation ################
 * ################################################
 *
 * Version: 1.0
 * File: track.h
 * Author: Jie Wang
 * Description: Track Operation
 * Date: 2016-01-07
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#ifndef SRC_TRACK_TRACK_H_
#define SRC_TRACK_TRACK_H_


#include "../utils/csvOper.h"
#include "../variables/variables.h"


/*
 * FUNCTION: record
 * INPUT: list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: record of requests list
 */
void record(list<RequestInfo> requestsList);


/*
 * FUNCTION: recordRate
 * INPUT: string hitRate
 * OUTPUT: none
 * (SIDE)EFFECTS: record of hit Rate
 */
void recordRate(string hitRate);


/*
 * FUNCTION: genReqFromTrack
 * INPUT: list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: Generate requests from track
 */
void genReqFromTrack(list<RequestInfo> *requestsList);

#endif /* SRC_TRACK_TRACK_H_ */
