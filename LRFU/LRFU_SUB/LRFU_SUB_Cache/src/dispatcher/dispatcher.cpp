/**
 * ################################################
 * #################### Dispather #################
 * ################################################
 *
 * Version: 1.0
 * File: dispather.h
 * Author: Jie Wang
 * Description: Dispather
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "dispatcher.h"

/*
 * FUNCTION: dispatcher
 * INPUT: string fileName
 * OUTPUT: Server IP
 * (SIDE)EFFECTS: dispatcher
 */
string dispatcher(string fileName) {

	return redisGet(fileName);

}
