/**
 * ################################################
 * ############### Index's Operation ##############
 * ################################################
 *
 * Version: 1.0
 * File: capacity.h
 * Author: Jie Wang
 * Description: Index's Operation
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "index.h"
#include "../variables/variables.h"
#include "../replacement/replacement.h"
#include "../capacity/capacity.h"
#include "../mapxy/mapxy.h"


/*
 * FUNCTION: Compute Area
 * INPUT: Start&&End coordinates
 * OUTPUT: Area
 * (SIDE)EFFECTS: Compute Area
 */
int comArea(int startx, int starty, int endx, int endy) {
	return (endx-startx)*(endy-starty);
}


/*
 * FUNCTION: Compute Cross Area
 * INPUT: Start&&End coordinates
 * OUTPUT: Area
 * (SIDE)EFFECTS: Compute Cross Area
 */
int comCrossArea(int oldStartx, int oldStarty, int oldEndx, int oldEndy,
		int newStartx, int newStarty, int newEndx, int newEndy){

	//not cross
	if(newEndx<oldStartx || newEndy<oldStarty ||
		oldEndx<newStartx || oldEndy<newStarty) {
		return 0;
	}

	//cross
	int startx = newStartx>oldStartx ? newStartx : oldStartx;
	int starty = newStarty>oldStarty ? newStarty : oldStarty;

	int endx = newEndx<oldEndx ? newEndx : oldEndx;
	int endy = newEndy<oldEndy ? newEndy : newEndy;

	return comArea(startx, starty, endx, endy);
}


/*
 * FUNCTION: Is File Name Hit or Not
 * INPUT: IndexInfo & RequestInfo
 * OUTPUT: bool
 * (SIDE)EFFECTS: Is File Name Hit or Not
 */
bool fileNameHit(RequestInfo request) {

	int count = 0;

	stringstream instrStream;
	instrStream<<"select count(*) from `index` where filename='"<<request.fileName<<"'";

	string sql = instrStream.str();

	count = getCount(sql.c_str());

	if(count > 0) {
		return true;
	}

	return false;
}


/*
 * FUNCTION: Is Area Hit or Not
 * INPUT: IndexInfo & RequestInfo
 * OUTPUT: bool
 * (SIDE)EFFECTS: Is Area Hit or Not
 */
bool areaHit(RequestInfo request) {

	int count = 0;

	stringstream instrStream;
	instrStream<<"select count(*) from `index` where `filename`='"<<request.fileName<<
			"' and `start_x`<="<<request.startx<<" and `start_y`<="<<request.starty<<
			" and `end_x`>="<<request.endx<<" and `end_y`>="<<request.endy;

	string sql = instrStream.str();

	count = getCount(sql.c_str());

	if(count > 0) {
		return true;
	}

	return false;
}


/*
 * FUNCTION: Merge Two IndexInfo
 * INPUT: IndexInfo & RequestInfo
 * OUTPUT: IndexInfo
 * (SIDE)EFFECTS: Merge Two IndexInfo
 */
IndexInfo merge(list<IndexInfo> *indexList, IndexInfo oldIndex, RequestInfo request) {

	int * mapxy = mapXY(request.startx, request.starty, request.endx, request.endy);

	int newStartx = oldIndex.startx<mapxy[0] ? oldIndex.startx : mapxy[0];
	int newStarty = oldIndex.starty<mapxy[1] ? oldIndex.starty : mapxy[1];

	int newEndx = oldIndex.endx>mapxy[2] ? oldIndex.endx : mapxy[2];
	int newEndy = oldIndex.endy>mapxy[3] ? oldIndex.endy : mapxy[3];


	double newSize = 0;
	IndexInfo newIndex = {request.fileName, newStartx, newStarty, newEndx, newEndy,
			oldIndex.count, request.genTime, newSize, oldIndex.priority};



	list<IndexInfo>::iterator iter;

	for(iter=(*indexList).begin(); iter!=(*indexList).end(); iter++){

		if(!((*iter).fileName).compare(oldIndex.fileName)){

			iter = (*indexList).erase(iter);

			//remove old
			removeFile(oldIndex.fileName);

		}

	 }

	return newIndex;

}


/*
 * FUNCTION: Search In Index
 * INPUT: IndexInfo & RequestInfo
 * OUTPUT: bool
 * (SIDE)EFFECTS: Search In Index
 */
bool searchInIndex(RequestInfo request){

	//file name hit
	if(!fileNameHit(request)) {
		return false;
	}

	//area hit
	if(areaHit(request)) {
		return true;
	}

	return false;
}


/*
 * FUNCTION: Update Index
 * INPUT: IndexInfo & RequestInfo
 * OUTPUT: string
 * (SIDE)EFFECTS: Update Index
 */
string updateIndex(RequestInfo request){

	string subFitsName = "";

	stringstream instrStream;
	instrStream<<"select `sub_name` from `index` where filename='"<<request.fileName<<
			"' and start_x<="<<request.startx<<" and start_y<="<<request.starty<<
			" and end_x>="<<request.endx<<" and end_y>="<<request.endy;

	string sql = instrStream.str();

	subFitsName = getValue(sql.c_str());

	if(subFitsName != "") {
		stringstream instrStream;
		instrStream<<"update `index` set `count`=`count`+1, idle_time="<<
				request.genTime<<" where `sub_name`='"<<subFitsName<<"'";

		string sql = instrStream.str();

		updateInfo(sql.c_str());
	}


	//update Capacity
	updateTotalCapacity();

	return subFitsName;
}


///*
// * FUNCTION: Insert Into Index
// * INPUT: IndexInfo & RequestInfo & int
// * OUTPUT: string
// * (SIDE)EFFECTS: Insert Into Index
// */
//string insertIntoIndex(map<string, list<IndexInfo> > *index, RequestInfo request, int* mapxy) {
//
//	stringstream outstrStream;
//	outstrStream<<"_"<<mapxy[0]<<"_"<<mapxy[1]<<"_"<<mapxy[2]<<"_"<<mapxy[3]<<".fits";
//	string tmpstr = outstrStream.str();
//	string indexFileName = request.fileName + tmpstr;
//
//	double size = getFileSize(SSD_SOURCE_PATH + indexFileName);
//
//	IndexInfo newIndex = {indexFileName, mapxy[0], mapxy[1], mapxy[2], mapxy[3], 1, request.genTime, size, 0};
//
//
//	//fileName hit
//	if(!fileNameHit((*index), request)){
//		list<IndexInfo> indexList;
//		indexList.push_back(newIndex);
//
//		//insert
//		(*index)[request.fileName] = indexList;
//	} else {
//
//		map<string, list<IndexInfo> >::iterator iter;
//
//		iter = (*index).find(request.fileName);
//
//		//insert
//		list<IndexInfo> indexList = iter->second;
//
//		indexList.push_back(newIndex);
//
//		//insert
//		(*index)[request.fileName] = indexList;
//
//		//update Capacity
//		updateTotalCapacity();
//	}
//
//	return indexFileName;
//}
//
//
///*
// * FUNCTION: Insert Into Index
// * INPUT: IndexInfo & RequestInfo & IndexInfo
// * OUTPUT: string
// * (SIDE)EFFECTS: Insert Into Index
// */
//string insertIntoIndex(map<string, list<IndexInfo> > *index, RequestInfo request, IndexInfo tmpIndex){
//
//	int startx = tmpIndex.startx;
//	int starty = tmpIndex.starty;
//	int endx = tmpIndex.endx;
//	int endy = tmpIndex.endy;
//
//	stringstream outstrStream;
//	outstrStream<<"_"<< startx <<"_"<< starty <<"_"<< endx <<"_"<< endy <<".fits";
//	string tmpstr = outstrStream.str();
//	string indexFileName = request.fileName + tmpstr;
//
//	double size = getFileSize(SSD_SOURCE_PATH + indexFileName);
//
//	IndexInfo newIndex = {indexFileName, tmpIndex.startx, tmpIndex.starty, tmpIndex.endx, tmpIndex.endy, tmpIndex.count+1, request.genTime, size, 0};
//
//
//	//fileName hit
//	if(!fileNameHit((*index), request)){
//		list<IndexInfo> indexList;
//		indexList.push_back(newIndex);
//
//		//insert
//		(*index)[request.fileName] = indexList;
//	} else {
//
//		map<string, list<IndexInfo> >::iterator iter;
//
//		iter = (*index).find(request.fileName);
//
//		//insert
//		list<IndexInfo> indexList = iter->second;
//
//		indexList.push_back(newIndex);
//
//		//insert
//		(*index)[request.fileName] = indexList;
//
//		//update Capacity
//		updateTotalCapacity();
//	}
//
//	return indexFileName;
//
//}
//
//
///*
// * FUNCTION: Update All Index
// * INPUT: IndexInfo & int
// * OUTPUT: none
// * (SIDE)EFFECTS: Update All Index
// */
//void updateAllIndex(map<string, list<IndexInfo> > *index, int currentTime){
//
//	map<string, list<IndexInfo> >::iterator iter;
//
//	//Index whose priority is the min.
//	IndexInfo minIndex = { "", 0, 0, 0, 0, 0, 0, 0, NUM_MAX};
//	string minFileName = "";
//
//	for(iter=(*index).begin(); iter!=(*index).end(); iter++){
//
//		list<IndexInfo> indexList = iter->second;
//		list<IndexInfo> newIndexList;
//
//		//indexes' list's iterator
//		list<IndexInfo>::iterator indexIter;
//
//		//update priority of all index
//		for(indexIter=indexList.begin(); indexIter!=indexList.end(); indexIter++) {
//
//			IndexInfo tmpIndex = (*indexIter);
//
//			//====>> compute priority <<====
//			double priority = comPriority(tmpIndex, currentTime);
//
//			tmpIndex.priority = priority;
//
//			//the min priority index
//			if(tmpIndex.priority < minIndex.priority){
//				minIndex = tmpIndex;
//				minFileName = iter->first;
//			} else if(tmpIndex.priority == minIndex.priority){
//				//compare size
//				if(tmpIndex.size > minIndex.size){
//					minIndex = tmpIndex;
//					minFileName = iter->first;
//				}
//			}
//
//			//add to new IndexList
//			newIndexList.push_back(tmpIndex);
//		}
//
//		//update
//		(*index)[iter->first] = newIndexList;
//	}
//
//	//delete the min priority index
//	map<string, list<IndexInfo> >::iterator newIter;
//
//	newIter = (*index).find(minFileName);
//
//	if(newIter == (*index).end()){
//
//		cout<<"ERROR====>> :( \n";
//
//	} else {
//
//		//insert
//		list<IndexInfo> indexList = newIter->second;
//
//		//delete
//		list<IndexInfo>::iterator tmpIter;
//
//		for(tmpIter=indexList.begin(); tmpIter!=indexList.end(); tmpIter++){
//
//			if(!((*tmpIter).fileName).compare(minIndex.fileName)) {
//				tmpIter = indexList.erase(tmpIter);
//
//				//remove File within least priority
//				removeFile(minIndex.fileName);
//			}
//
//		 }
//
//		(*index)[minFileName] = indexList;
//
//
//		//update Capacity
//		updateTotalCapacity();
//	}
//
//}


/*
 * FUNCTION: Compute Priority
 * INPUT: IndexInfo & int
 * OUTPUT: double
 * (SIDE)EFFECTS: Compute Priority
 */
double comPriority(IndexInfo index, int currentTime){

	double priority = 0;

	priority = WEIGHT * ((double)(index.count)/(double)(currentTime-index.idleTime+1));

	return priority;

}


/*
 * FUNCTION: update Total Capacity
 * INPUT: IndexInfo & int
 * OUTPUT: none
 * (SIDE)EFFECTS: Update Total Capacity
 */
void updateTotalCapacity(){


}




