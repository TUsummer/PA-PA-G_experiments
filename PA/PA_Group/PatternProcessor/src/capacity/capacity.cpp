/**
 * ################################################
 * ############# Capacity Calculation #############
 * ################################################
 *
 * Version: 1.0
 * File: capacity.cpp
 * Author: Jie Wang
 * Description: Get Capacity of Cache Disks
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "capacity.h"


/*
 * FUNCTION: getCapacity
 * INPUT: Disk's Path
 * OUTPUT: Disk's Capacity
 * (SIDE)EFFECTS: Get Capacity of Cache Disks
 */
int getCapacity(string path) {

	const char *dir = path.c_str();

	int totalSzie = BYTES_OF_FOLDER/1024;

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp=opendir(dir)) == NULL) {
        fprintf(stderr, "Cannot open dir: %s\n", dir);
        exit(0);
    }

    //open child dir
    chdir(dir);

    while ((entry=readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)){
            if (strcmp(".", entry->d_name)==0 || strcmp("..", entry->d_name)==0){
                continue;
            }

            totalSzie += statbuf.st_size/1024;
            getCapacity(entry->d_name);
        } else {
        	totalSzie += statbuf.st_size/1024;
        }
    }

    chdir("..");
    closedir(dp);

    return totalSzie;
}


/*
 * FUNCTION: getFileSize
 * INPUT: File's Path
 * OUTPUT: File's Size
 * (SIDE)EFFECTS: Get Size of File
 */
int getFileSize(string path) {

	const char *filePath = path.c_str();

	FILE* fp = NULL;
	int fileLen = 0;

	fp = fopen(filePath, "rb");
	if (fp == NULL) {
	   return 0;
	}

	fseek(fp,0,SEEK_END);      //last of file
	fileLen = ftell(fp);       //file size

	return fileLen;

}

