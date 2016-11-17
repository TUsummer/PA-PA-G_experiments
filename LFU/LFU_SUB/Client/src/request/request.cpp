/**
 * ################################################
 * ############### Request Operation ##############
 * ################################################
 *
 * Version: 1.0
 * File: request.cpp
 * Author: Jie Wang
 * Description: Request Operation
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "request.h"

//
void calculate(int fileName, int xstart, int ystart, int threshold, list<RequestInfo> *requests){

	srand((int)time(0));

	int centerx, centery;

    centerx = xstart + random(ERR_XY);
    centery = ystart + random(ERR_XY);

    //single request Info
    RequestInfo request;

    for(int i=0; i<threshold; i++){

    	int startx, starty, endx, endy;

        startx = centerx - (R+random(ERR_R));
        starty = centery - (R+random(ERR_R));

        endx = centerx + (R+random(ERR_R));
        endy = centery + (R+random(ERR_R));

        char buf[NUM_MAX];
        sprintf(buf, "%d", fileName);
        string name = buf;

        RequestInfo request = {name, startx, starty, endx, endy, 0, 0, 0};
        (*requests).push_back(request);
    }

}


/*
 * FUNCTION: genRequests
 * INPUT: FileInfo && list
 * OUTPUT: none
 * (SIDE)EFFECTS: generate requests
 */
void genRequests(FileInfo files[NUM_FILES], list<RequestInfo> *requests){
    int filename;
    int tempmax, hotmax, coldmax;
    for(int i=0; i<NUM_FILES; i++){

    	filename = files[i].filename;
        if(files[i].hot==1||files[i].hot==2){///20% of the file to produce 80% of the record
            tempmax = (NUM_REQUESTS*HOT_PART)/(NUM_FILES*COLD_PART);
            if(files[i].type==1){//hot: above average: average+
                tempmax += HOT_SCALE*tempmax;
                hotmax = tempmax*HOT_PART;
                coldmax = tempmax*COLD_PART*0.3;

                int max[NUM_HOT_ZONE];

                for(int j=0; j<NUM_HOT_ZONE; j++) {
                	max[j] = coldmax;
                }

                max[files[i].hotzone-1] = hotmax;

				calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[0], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[1], requests);
				calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[2], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[3], requests);


            } else if(files[i].type==4){///hot: below average: average-

                tempmax -= 20;

                hotmax = tempmax*HOT_PART;
                coldmax = tempmax*COLD_PART*0.3;

                int max[NUM_HOT_ZONE];

                for(int j=0; j<NUM_HOT_ZONE; j++) {
                	max[j] = coldmax;
                }

                max[files[i].hotzone-1] = hotmax;

                calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[0], requests);
                calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[1], requests);
				calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[2], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[3], requests);

            } else{///hot: average
                hotmax = tempmax*HOT_PART;
                coldmax = tempmax*COLD_PART*0.3;

                int max[NUM_HOT_ZONE];

                for(int j=0; j<NUM_HOT_ZONE; j++) {
                	max[j] = coldmax;
                }

                max[files[i].hotzone-1] = hotmax;

                calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[0], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[1], requests);
				calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[2], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[3], requests);
            }
        } else{///80% of the file to produce 20% of the record
            tempmax = (NUM_REQUESTS*COLD_PART)/(NUM_FILES*HOT_PART);
            if(files[i].type==1){///cold: above average: average+
                tempmax += 2;
                hotmax = tempmax*HOT_PART;
                coldmax = tempmax*COLD_PART*0.3;

                int max[NUM_HOT_ZONE];

                for(int j=0; j<NUM_HOT_ZONE; j++) {
                	max[j] = coldmax;
                }

                max[files[i].hotzone-1] = hotmax;

                calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[0], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[1], requests);
				calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[2], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[3], requests);
            } else if(files[i].type==4){///cold: below average: average-
                tempmax -= 2;
                hotmax = tempmax*HOT_PART;
                coldmax = tempmax*COLD_PART*0.3;

                int max[NUM_HOT_ZONE];

                for(int j=0; j<NUM_HOT_ZONE; j++) {
                	max[j] = coldmax;
                }

                max[files[i].hotzone-1] = hotmax;

                calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[0], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[1], requests);
				calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[2], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[3], requests);

            } else{///cold: average
                hotmax = tempmax*HOT_PART;
                coldmax = tempmax*COLD_PART*0.3;

                int max[NUM_HOT_ZONE];

                for(int j=0; j<NUM_HOT_ZONE; j++) {
                	max[j] = coldmax;
                }

                max[files[i].hotzone-1] = hotmax;

                calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[0], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[1], requests);
				calculate(filename, SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[2], requests);
				calculate(filename, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, 3*SIZE_ZONE/NUM_HOT_ZONE-0.5*ERR_XY, max[3], requests);

            }
        }
    }
}


/*
 * FUNCTION: allotTime2Request
 * INPUT: FileInfo
 * OUTPUT: none
 * (SIDE)EFFECTS: Allotted time to request(random)
 */
void allotTime2Request(RequestInfo *request){

	srand((int)time(0));

	int genTime = random(NUM_TIME);

	(*request).genTime = genTime;

}


/*
 * FUNCTION: allotTime2Request
 * INPUT: FileInfo
 * OUTPUT: none
 * (SIDE)EFFECTS: Allotted time to request(TimeWindow)
 */
void allotTime2Request(RequestInfo *request, int TWNO){

	srand((int)time(0));

	int startTime = TWNO * SIZE_TIME_WINDOW;
	int genTime = startTime + random(SIZE_TIME_WINDOW);

	(*request).genTime = genTime;

}


/*
 * FUNCTION: allotTime2Request
 * INPUT: list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: Allotted time to requests' list
 */
void allotTime2Request(list<RequestInfo> *requestsList){

	srand((int)time(0));

	//average requests per Time Window
	int reqOfTimeWindow = (*requestsList).size()/NUM_TIME_WINDOW;

	//NO. of Time Window
	int TWNO = 0;

	//flag 0f average requests per Time Window
	int flagOfSize = 0;

	//requests' list's iterator
	list<RequestInfo>::iterator reqIter;

	//allot Time 2 Request
	for(reqIter=(*requestsList).begin(); reqIter!=(*requestsList).end(); reqIter++) {

		int startTime = TWNO * SIZE_TIME_WINDOW;
		int genTime = startTime + random(SIZE_TIME_WINDOW);

		(*reqIter).genTime = genTime;

		flagOfSize++;

		if(flagOfSize > reqOfTimeWindow){
			flagOfSize = 0;
			TWNO++;
		}
	}

	//order by genTime asc
	(*requestsList).sort();
}
