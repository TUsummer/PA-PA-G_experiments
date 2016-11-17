/**
 * ################################################
 * ################# Redis Operation ##############
 * ################################################
 *
 * Version: 1.0
 * File: redis.h
 * Author: Jie Wang
 * Description: Redis Operation
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#ifndef SRC_REDIS_REDIS_H_
#define SRC_REDIS_REDIS_H_

#include <iostream>
#include <string>
#include <hiredis/hiredis.h>
#include <vector>
#include <map>
#include <list>

#include "../variables/variables.h"
#include "../struct/structs.h"
#include "../utils/stringOper.h"

using namespace std;

/*
 * FUNCTION: Set
 * INPUT: string key, string value
 * OUTPUT:
 * (SIDE)EFFECTS: redis set
 */
void redisSet(string key, string value);

/*
 * FUNCTION: Get
 * INPUT: string key
 * OUTPUT: string value
 * (SIDE)EFFECTS: redis get
 */
string redisGet(string key);

void redisHSet(string key, string value);
map<string, list<RequestInfo> > GetAllRequest();
vector<string> getAllKeys();
list<RequestInfo> redisHGetAll(string key);

#endif /* SRC_REDIS_REDIS_H_ */
