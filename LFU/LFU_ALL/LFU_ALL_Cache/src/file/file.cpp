/**
 * ################################################
 * ############# Initialize File Info #############
 * ################################################
 *
 * Version: 1.0
 * File: file.cpp
 * Author: Jie Wang
 * Description: Initialize File Info
 * Date: 2016-01-05
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "file.h"


/*
 * FUNCTION: Initialize File Info
 * INPUT: FileInfo *files
 * OUTPUT: none
 * (SIDE)EFFECTS: Initialize Files' Info
 */
void initFiles(FileInfo *files) {

	srand((int)time(0));

	for(int i=0; i<NUM_FILES; i++) {
        files[i].filename = i;
        files[i].hot = 1 + random(NUM_HOT);
        files[i].type = 1 + random(NUM_TYPE);
        files[i].hotzone = 1 + random(NUM_HOT_ZONE);
        files[i].reqcounts = 0;
        files[i].idletime =0;
    }

}
