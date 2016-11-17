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

int main(){

	cout << "==========>>>>> START TO SERVE <<<<<==========\n" << endl;

	//store all the request result
	list<RequestInfo> resultList;

	//初始化数据库
	init_db();
	//连接到数据库
	if (conn_db(DB_HOST_NAME, DB_USER_NAME, DB_PASSWORD, DB_DB_NAME) != 0) {
		return -1;										//连接数据库失败，函数退出
	}


	struct sockaddr_in s_in;							//server address structure
	struct sockaddr_in c_in;							//client address structure
	int l_fd,c_fd;
	socklen_t len;
	char buf[NUM_MAX];									//content buff area

	memset((void *)&s_in, 0, sizeof(s_in));

	s_in.sin_family = AF_INET;							//IPV4 communication domain
	s_in.sin_addr.s_addr = INADDR_ANY;					//accept any address
	s_in.sin_port = htons(SERVER_PORT);					//change port to netchar

	l_fd = socket(AF_INET, SOCK_STREAM, 0);				//socket(int domain, int type, int protocol)

	bind(l_fd, (struct sockaddr *)&s_in, sizeof(s_in));

	listen(l_fd, NUM_MAX);								//lisiening start

	//serve
	double qos = 0.0;
	string serverIp = SERVER_IP;						//server IP

	string path = "";
	struct timeval start, end;

	while(1){
		c_fd = accept(l_fd,(struct sockaddr *)&c_in,&len);

		memset(&buf,0,sizeof(buf));

		read(c_fd, buf, NUM_MAX);						//read the message send by client

		string reqStr(buf);


		if(reqStr == "EOF") {
			break;
		}

		gettimeofday(&start, NULL);						//start to serve

		RequestInfo request = string2Request(reqStr, PATTERN);
		qos = 0.0;
		string subFitsName = "";						//file name: Full | Sub


		if(searchInIndex(request)){						//hit in cache perfectly
			subFitsName = updateIndex(request);

			path = SSD_SOURCE_PATH;

			request.hit = 1;

			int x0=0, y0=0; //sub fits (0, 0)
			vector<string> result = split(subFitsName, "_");

			if(result.size() > 2) {
				x0 = atoi(result[1].c_str());
				y0 = atoi(result[2].c_str());
			}

			//response to user
			response(subFitsName, request.startx, request.starty,
						request.endx, request.endy, x0, y0, path);

			gettimeofday(&end, NULL);					//end of serve
			long timeuse = end.tv_sec*1000 + end.tv_usec/1000;
			request.endTime = timeuse;

			//服务时间
			qos = (end.tv_sec-start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
			request.qos = qos;

			//store result to record
			insertIntoResult(request);
		} else {										//not hit, write into redis queue
			//写入redis
			redisHSet(request.fileName, reqStr);
		}

		close(c_fd);
	}
}
