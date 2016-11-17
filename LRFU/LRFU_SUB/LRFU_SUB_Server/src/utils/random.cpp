/**
 * ################################################
 * ################# Random Number ################
 * ################################################
 *
 * Version: 1.0
 * File: random.cpp
 * Author: Jie Wang
 * Description: Random Number
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/


#include "../utils/random.h"


/*
 * FUNCTION: random
 * INPUT: int
 * OUTPUT: int
 * (SIDE)EFFECTS: Random Number
 */
int random(int x) {
	return (rand()%x);
}

