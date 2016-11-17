/**
 * ################################################
 * #################### Variables #################
 * ################################################
 *
 * Version: 1.0
 * File: variables.h
 * Author: Jie Wang
 * Description: Variables
 * Date: 2016-01-05
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#ifndef SRC_VARIABLES_VARIABLES_H_
#define SRC_VARIABLES_VARIABLES_H_

/* Global Variables */
#define NUM_MAX 1024		//NUM of max
#define NUM_XY 4			//NUM of coordinates


/* requests variables */
#define NUM_REQUESTS 2000	//NUM of requests


/* Time variables */
#define NUM_TIME 2000			//NUM of time
#define SIZE_TIME_WINDOW 2000	//size of time window
#define NUM_TIME_WINDOW 1		//NUM of time window
#define CONTINUE 2				//the requests will last time window


/* coordinate variables */
#define ERR_XY 10			//err of coordinate x & y
#define ERR_R 30			//err of area
#define R 210				//value of area R = (0.45*SIZE_ZONE-ERR_R)/2


/* File variables */
#define NUM_FILES 300		//NUM of files
#define NUM_HOT 10			//NUM of hot file
#define NUM_TYPE 4			//NUM of file type
#define NUM_HOT_ZONE 4		//NUM of hot zones of file
#define SIZE_ZONE 1000		//Size of zone X*X


/* 2-8 Rule variables */
#define HOT_PART 0.8		//value of hot part
#define COLD_PART 0.2		//value of cold part

#define HOT_SCALE 0.25


/* Index variables */
#define AREA_THRESHOLD 0.50		//Threshold of cross area


/* File path variables */
#define SSD_SOURCE_PATH "/home/summer/disks/ssd1/CacheFITS/" 	//cache file path
#define HDD_SOURCE_PATH "/home/summer/disks/hdd2/FITS/DATA/" 	//source file path
#define SSD_TARGET_PATH "/home/summer/disks/hdd1/TargetFITS/" 	//target file path


/* Capacity variables */
#define BYTES_OF_FOLDER 4096		//folder size
#define CACHESIZE 1024*1024*1		//Cache Size(5GB)


/* Priority variables */
#define WEIGHT	1.0					//weight of priority


/* fits map variables */
#define ACCURACY 100				//map division accuracy


/* Record variables */
#define REQUEST_RECORD_PATH "/home/summer/disks/hdd2/FITS/result/Requests.csv"
#define RATE_RECORD_PATH "/home/summer/disks/hdd2/FITS/result/Rate.csv"


/* Track variables */
//#define TRACK_PATH "./track/Req1000_File100_Range500.csv"
#define TRACK_PATH "./track/Requests.csv"


/* Shell Path */
#define SHELL_PATH "bash /home/summer/workspace/RemoveFile.sh /home/summer/disks/ssd1/CacheFITS/"


/* Socket */
#define SERVER_PORT 9090
#define CACHE_PORT 9099


/* Redis */
#define REDIS_IP "127.0.0.1"
#define REDIS_PORT 6379

/* Servers */
#define SERVER_IP "127.0.0.1"

/* Pattern */
#define PATTERN ","

/* Pthread variables */
#define NUM_PTHREAD 5		//NUM of Pthread

/* DB */
#define DB_HOST_NAME "localhost"		//NUM of Pthread
#define DB_USER_NAME "root"				//NUM of Pthread
#define DB_PASSWORD "1"					//NUM of Pthread
#define DB_DB_NAME "PA"					//NUM of Pthread


#endif /* SRC_VARIABLES_VARIABLES_H_ */
