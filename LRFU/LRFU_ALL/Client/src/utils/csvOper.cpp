/**
 * ################################################
 * ################# CSV Operation ################
 * ################################################
 *
 * Version: 1.0
 * File: csvOper.cpp
 * Author: Jie Wang
 * Description: CSV Operation
 * Date: 2016-01-07
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "csvOper.h"

#include "stringOper.h"


/*
 * FUNCTION: writeCSV
 * INPUT: File Path && list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: Write requestsList to CSV
 */
void writeCSV(string filePath, list<RequestInfo> requestsList) {

	ofstream outfile(filePath.c_str());

	//requests' list's iterator
	list<RequestInfo>::iterator reqIter;

	for(reqIter=requestsList.begin(); reqIter!=requestsList.end(); reqIter++) {

		outfile<<(*reqIter).fileName<<","<<(*reqIter).startx<<","<<(*reqIter).starty
				<<","<<(*reqIter).endx<<","<<(*reqIter).endy<<","<<(*reqIter).genTime
				<<","<<(*reqIter).endTime<<","<<(*reqIter).qos<<'\n';
	}

	 outfile.flush();
	 outfile.close();
}


/*
 * FUNCTION: writeCSV
 * INPUT: File Path && record
 * OUTPUT: none
 * (SIDE)EFFECTS: Write record to CSV
 */
void writeCSV(string filePath, string record) {

	ofstream outfile(filePath.c_str());

	outfile<<record<<'\n';

	outfile.flush();
	outfile.close();

}


/*
 * FUNCTION: readCSV
 * INPUT: File Path && list<RequestInfo>
 * OUTPUT: none
 * (SIDE)EFFECTS: read record from CSV
 */
void readCSV(string filePath, list<RequestInfo> *requestsList) {

	ifstream infile(filePath.c_str());

	string tmp;

	while(getline(infile,tmp)) {

		vector<string> info = split(tmp, ",");

		RequestInfo request = {info[0], atoi(info[1].c_str()), atoi(info[2].c_str()), atoi(info[3].c_str()),
				atoi(info[4].c_str()), atoi(info[5].c_str()), atoi(info[6].c_str()), atof(info[7].c_str()), atoi(info[8].c_str())};

		(*requestsList).push_back(request);

	}
}


