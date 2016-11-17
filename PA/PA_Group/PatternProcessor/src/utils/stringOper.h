/**
 * ################################################
 * ################ String Operater ###############
 * ################################################
 *
 * Version: 1.0
 * File: stringSplit.h
 * Author: Jie Wang
 * Description: String Operater
 * Date: 2016-01-07
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#ifndef SRC_UTILS_STRINGOPER_H_
#define SRC_UTILS_STRINGOPER_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../struct/structs.h"

using namespace std;


/*
 * FUNCTION: split
 * INPUT: string str && string pattern
 * OUTPUT: vector<string>
 * (SIDE)EFFECTS: string split
 */
vector<string> split(string str, string pattern);


/*
 * FUNCTION: Request to String
 * INPUT: RequestInfo
 * OUTPUT: string
 * (SIDE)EFFECTS: change Request to String
 */
string request2String(RequestInfo request, string pattern);


/*
 * FUNCTION: String to Request
 * INPUT: reqStr string
 * OUTPUT: RequestInfo
 * (SIDE)EFFECTS: change String to Request
 */
RequestInfo string2Request(string reqStr, string pattern);


#endif /* SRC_UTILS_STRINGOPER_H_ */
