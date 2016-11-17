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
#include "../redis/redis.h"

using namespace std;

void mapRequest(string fileName, list<RequestInfo> requests) {
	int *mapxy, *min;
	min = new int[NUM_XY];

	min[0] = 10000;						//mix
	min[1] = 10000;
	min[2] = -1;						//max
	min[3] = -1;

	list<RequestInfo>::iterator iter;

	//请求聚合
	for(iter=requests.begin(); iter!=requests.end(); iter++) {
		//map x && y
		mapxy = mapXY((*iter).startx, (*iter).starty, (*iter).endx, (*iter).endy);

		if(min[0] > mapxy[0]) {
			min[0] = mapxy[0];
		}

		if(min[1] > mapxy[1]) {
			min[1] = mapxy[1];
		}

		if(min[2] < mapxy[2]) {
			min[2] = mapxy[2];
		}

		if(min[3] < mapxy[3]) {
			min[3] = mapxy[3];
		}
	}

	RequestInfo request = {fileName, min[0], min[1], min[2], min[3], 0, 0, 0, 0, 0};

	send(SERVER_IP, request, PATTERN);		//发送到缓存服务器
}

int main(){

	cout << "==========>>>>> START TO SERVE <<<<<==========\n" << endl;

	//初始化数据库
	init_db();
	//连接到数据库
	if (conn_db(DB_HOST_NAME, DB_USER_NAME, DB_PASSWORD, DB_DB_NAME) != 0) {
		return -1;										//连接数据库失败，函数退出
	}

	//serve
	string path = "";									//file path
	double qos = 0.0;
	struct timeval start, end;

	while(1){

		//定时
		//sleep(SLEEP_TIME);

		//获取队列并聚集
		map<string, list<RequestInfo> > requestsMap = GetAllRequest();
		map<string, list<RequestInfo> >::iterator iter;
		list<RequestInfo> requests;

		for(iter=requestsMap.begin(); iter!=requestsMap.end(); iter++) {
			mapRequest(iter->first, iter->second);

			//merge requests
			requests.merge(iter->second);
		}

		//====>>执行顺序<<====
		//1、若无操作按文件名自然序执行
		//2、order by genTime asc
		requests.sort();

		//requests' list's iterator
		list<RequestInfo>::iterator reqIter;

		for(reqIter=requests.begin(); reqIter!=requests.end(); reqIter++) {

			gettimeofday(&start, NULL);				//start to serve

			RequestInfo request = (*reqIter);
			qos = 0.0;

			//file name: Full | Sub
			string subFitsName = "";

			if(searchInIndex(request)){				//hit in cache perfectly
				subFitsName = updateIndex(request);

				path = SSD_SOURCE_PATH;

				request.hit = 1;
			} else {								//not hit
				path = HDD_SOURCE_PATH;
				subFitsName = request.fileName + ".fits";
			}

			int x0=0, y0=0; //sub fits (0, 0)
			vector<string> result = split(subFitsName, "_");

			if(result.size() > 2) {
				x0 = atoi(result[1].c_str());
				y0 = atoi(result[2].c_str());
			}

			//response to user
			response(subFitsName, request.startx, request.starty,
						request.endx, request.endy, x0, y0, path);

			gettimeofday(&end, NULL);				//请求结束时间
			long timeuse = end.tv_sec*1000 + end.tv_usec/1000;

			request.endTime = timeuse;

			//服务时间
			qos = (end.tv_sec-start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;

			request.qos = qos;

			//store result to record
			insertIntoResult(request);
		}
	}
}
