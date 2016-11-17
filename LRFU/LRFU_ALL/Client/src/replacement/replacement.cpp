/**
 * ################################################
 * ############# Replacement Strategy #############
 * ################################################
 *
 * Version: 1.0
 * File: replacement.cpp
 * Author: Jie Wang
 * Description: Replacement Strategy
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/


#include "replacement.h"


/*
 * FUNCTION: removeFile
 * INPUT: file path
 * OUTPUT: none
 * (SIDE)EFFECTS: Remove File
 */
void removeFile(string fileName) {

    string rfileName = SHELL_PATH + fileName;

    char buffer[1024];

    strcpy(buffer, rfileName.c_str());

    printf("%s\n", buffer);

    system(buffer);

}


/*
 * FUNCTION: extractFile2Cache
 * INPUT: file path && Start&&End Coordinates
 * OUTPUT: double
 * (SIDE)EFFECTS: extract File from HDD to SSD
 */
double extractFile2Cache(string filename, int sx, int sy, int ex, int ey) {

    fitsfile *infptr, *outfptr;
    int status = 0;

    struct timeval start, end;
    double duration;

    gettimeofday(&start, NULL);

    stringstream instrStream;
    instrStream<<".fits["<<sx<<":"<<ex<<","<<sy<<":"<<ey<<"]";
    string s1 = instrStream.str();
    string infilename = HDD_SOURCE_PATH + filename + s1;

    if(!fits_open_file(&infptr, infilename.c_str(), READONLY, &status)){
        stringstream outstrStream;
        outstrStream<<"_"<<sx<<"_"<<sy<<"_"<<ex<<"_"<<ey<<".fits";
        string s2 = outstrStream.str();
        string outfilename = SSD_SOURCE_PATH + filename + s2;
        if(!fits_create_file(&outfptr, outfilename.c_str(), &status)){
            fits_copy_file(infptr, outfptr, 1, 1, 1, &status);
            fits_close_file(outfptr, &status);
        }
        fits_close_file(infptr, &status);
    }

    gettimeofday(&end, NULL);
    duration = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
    return duration;
}
