/**
 * ################################################
 * ############### Track Operation ################
 * ################################################
 *
 * Version: 1.0
 * File: track.cpp
 * Author: Jie Wang
 * Description: Track Operation
 * Date: 2016-01-07
 * Copyright (C) 2016 NAOC-TJUCS
 **/


#include "track.h"


/*
 * FUNCTION: record
 * INPUT: list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: record of requests list
 */
void record(list<RequestInfo> requestsList) {

	writeCSV(REQUEST_RECORD_PATH, requestsList);

}


/*
 * FUNCTION: recordRate
 * INPUT: string hitRate
 * OUTPUT: none
 * (SIDE)EFFECTS: record of hit Rate
 */
void recordRate(string hitRate) {

	writeCSV(RATE_RECORD_PATH, hitRate);

}


/*
 * FUNCTION: genReqFromTrack
 * INPUT: list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: Generate requests from track
 */
void genReqFromTrack(list<RequestInfo> *requestsList) {

	readCSV(TRACK_PATH, requestsList);

}

