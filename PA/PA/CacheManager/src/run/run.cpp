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
#include "../mydb/mydb.h"

using namespace std;


int CACHE_HIT = 0;
double TOTAL_QOS = 0;

int main(){

	cout << "==========>>>>> START TO SERVE <<<<<==========\n" << endl;

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
	s_in.sin_port = htons(PORT);						//change port to netchar

	l_fd = socket(AF_INET, SOCK_STREAM, 0);				//socket(int domain, int type, int protocol)

	bind(l_fd, (struct sockaddr *)&s_in, sizeof(s_in));

	listen(l_fd, NUM_MAX);								//lisiening start

	struct timeval cur;

	while(1){
		c_fd = accept(l_fd,(struct sockaddr *)&c_in,&len);

		memset(&buf,0,sizeof(buf));

		read(c_fd, buf, NUM_MAX);						//read the message send by client

		string reqStr(buf);

		RequestInfo request = string2Request(reqStr, PATTERN);

		//map x && y
		int *mapxy;

		//map x && y
		mapxy = mapXY(request.startx, request.starty, request.endx, request.endy);

		//merge
		IndexInfo tmpIndex;

		//fileName Hit
		if(fileNameHit(request)){

			//Area miss
			if(!areaHit(request)){

				//judge cross area
				//get from DB
				list<IndexInfo> indexList;

				string sql = "select * from `index` where filename='" + request.fileName + "'";

				indexList = getIndexList(sql.c_str());

				//indexs' list's iterator
				list<IndexInfo>::iterator indexIter;

				//Compute cross area
				for(indexIter=indexList.begin(); indexIter!=indexList.end(); indexIter++) {
					int newArea = comArea(request.startx, request.starty, request.endx, request.endy);
					int oldArea = comArea((*indexIter).startx, (*indexIter).starty, (*indexIter).endx, (*indexIter).endy);

					int crossArea = comCrossArea((*indexIter).startx, (*indexIter).starty, (*indexIter).endx, (*indexIter).endy,
							request.startx, request.starty, request.endx, request.endy);

					double oldProportion = ((double) crossArea / (double) oldArea);
					double newProportion = ((double) crossArea / (double) newArea);


					if(oldProportion>=AREA_THRESHOLD || newProportion>=AREA_THRESHOLD){

						//merge
						tmpIndex = merge((*indexIter), request);

						//map x && y
						mapxy = mapXY(tmpIndex.startx, tmpIndex.starty, tmpIndex.endx, tmpIndex.endy);

						break ;
					}
				}
			}

		}


		//cache sub fits file
		extractFile2Cache(request.fileName, mapxy[0], mapxy[1], mapxy[2], mapxy[3]);
		//insert new index to indexMap
		insertIntoIndex(request, mapxy);

		//compute cache capacity
		while(getCapacity(SSD_SOURCE_PATH) > CACHESIZE){
			gettimeofday(&cur, NULL);				//请求结束时间
			long currentTime = cur.tv_sec*1000 + cur.tv_usec/1000;
			//update all indexes' priority and remove the file within lowest priority
			updateAllIndex(currentTime);
		}

		close(c_fd);
	}

}
