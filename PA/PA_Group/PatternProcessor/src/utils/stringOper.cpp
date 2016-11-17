/**
 * ################################################
 * ################## String Split ################
 * ################################################
 *
 * Version: 1.0
 * File: stringSplit.cpp
 * Author: Jie Wang
 * Description: String Split
 * Date: 2016-01-07
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "stringOper.h"


/*
 * FUNCTION: split
 * INPUT: string str && string pattern
 * OUTPUT: vector<string>
 * (SIDE)EFFECTS: string split
 */
vector<string> split(string str, string pattern) {

	string::size_type pos;
	vector<string> result;

	str += pattern;

	int size = str.size();

	for(int i=0; i<size; i++) {
		pos = str.find(pattern,i);

		if(pos < size) {
			string s = str.substr(i, pos-i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}

	return result;
}

/*
 * FUNCTION: Request to String
 * INPUT: RequestInfo
 * OUTPUT: string
 * (SIDE)EFFECTS: change Request to String
 */
string request2String(RequestInfo request, string pattern) {

	stringstream strStream;
	strStream<<request.fileName<<pattern
			<<request.startx<<pattern<<request.starty<<pattern
			<<request.endx<<pattern<<request.endy<<pattern
			<<request.genTime<<pattern<<request.endTime<<pattern<<request.qos<<pattern;

	string reqStr = strStream.str();

	return reqStr;
}


/*
 * FUNCTION: String to Request
 * INPUT: reqStr string
 * OUTPUT: RequestInfo
 * (SIDE)EFFECTS: change String to Request
 */
RequestInfo string2Request(string reqStr, string pattern) {

	vector<string> infos = split(reqStr, pattern);

	string fileName = infos[0];					//The file name is requested
	int startx = atoi(infos[1].c_str());		//Start coordinates
	int starty = atoi(infos[2].c_str());
	int endx = atoi(infos[3].c_str());			//End coordinates
	int endy = atoi(infos[4].c_str());

	long genTime = atol(infos[5].c_str());		//Request's generation time
	long endTime = atol(infos[6].c_str());		//Request's response time
	double qos = 0.0;							//quality of service, equals endTime - genTime

    RequestInfo request = {fileName, startx, starty, endx, endy, genTime, endTime, qos, 0};

    return request;
}


