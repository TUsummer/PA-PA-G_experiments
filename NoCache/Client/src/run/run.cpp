/**
 * ################################################
 * ################## Main Function ###############
 * ################################################
 *
 * Version: 1.0
 * File: run.cpp
 * Author: Jie Wang
 * Description: Main Function
 * Date: 2016-11-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <map>
#include <list>
#include "../capacity/capacity.h"
#include "../dispatcher/dispatcher.h"
#include "../file/file.h"
#include "../index/index.h"
#include "../mapxy/mapxy.h"
#include "../replacement/replacement.h"
#include "../request/request.h"
#include "../response/response.h"
#include "../socket/socket.h"
#include "../struct/structs.h"
#include "../variables/variables.h"
#include "../track/track.h"
#include "../utils/stringOper.h"

using namespace std;


int main(){

	cout << "==========>>>>> START TO RUN <<<<<==========\n" << endl;

	cout << "==========>>>>>  INIT FILES  <<<<<==========\n" << endl;

	//files
	FileInfo files[NUM_FILES];

	//generate files
	initFiles(files);


	cout << "==========>>>>> GENERATE REQUESTS <<<<<==========\n" << endl;

	//store all the request
	list<RequestInfo> requestsList;

	//store all the request result
	list<RequestInfo> resultList;

	//requests' list's iterator
	list<RequestInfo>::iterator reqIter;

	//generate requests
//	genRequests(files, &requestsList);

	//generate requests from track
	genReqFromTrack(&requestsList);

	if(requestsList.size()>0) {
		cout << "==========>>>>> REQUESTS' NUM: " << requestsList.size() << " <<<<<==========\n" << endl;
	}

	cout << "==========>>>>> ALLOT TIME TO REQUESTS <<<<<==========\n" << endl;
//	allotTime2Request(&requestsList);

//	record(requestsList);

	if(requestsList.size()>0) {
		cout << "==========>>>>> REQUESTS' NUM: " << requestsList.size() << " <<<<<==========\n" << endl;
	}

	cout << "==========>>>>> START TO SERVE <<<<<==========\n" << endl;


	string serverIp = SERVER_IP;				//服务器IP
	int i = 0;									//计数

	//dispatcher
	for(reqIter=requestsList.begin(); reqIter!=requestsList.end(); reqIter++) {

		sleep((*reqIter).idle);					//等待开始
		struct timeval tv;
	    gettimeofday(&tv, NULL);
	    long timeuse = tv.tv_sec*1000 + tv.tv_usec/1000;

	    //request count
	    cout<<"Req:"<<i++<<"  Time:"<<timeuse<<endl;

	    (*reqIter).genTime = timeuse;

		send(serverIp, *reqIter, PATTERN);		//发送到服务器
	}

	//EOF
	reqEOF();

}
