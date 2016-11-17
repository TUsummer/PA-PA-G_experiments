/**
 * ################################################
 * #################### Dispatcher #################
 * ################################################
 *
 * Version: 1.0
 * File: dispatcher.h
 * Author: Jie Wang
 * Description: Dispatcher
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#ifndef SRC_DISPATCHER_DISPATCHER_H_
#define SRC_DISPATCHER_DISPATCHER_H_

#include <string>

#include "../redis/redis.h"

using namespace std;

/*
 * FUNCTION: Dispatcher
 * INPUT: string fileName
 * OUTPUT: Server IP
 * (SIDE)EFFECTS: dispatcher
 */
string dispatcher(string fileName);



#endif /* SRC_DISPATCHER_DISPATCHER_H_ */
