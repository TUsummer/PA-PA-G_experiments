/**
 * ################################################
 * ################# Redis Operation ##############
 * ################################################
 *
 * Version: 1.0
 * File: redis.cpp
 * Author: Jie Wang
 * Description: Redis Operation
 * Date: 2016-01-06
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "../redis/redis.h"

/*
 * FUNCTION: Set
 * INPUT: string key, string value
 * OUTPUT:
 * (SIDE)EFFECTS: redis set
 */
void redisSet(string key, string value) {
    redisContext* conn = redisConnect(REDIS_IP, REDIS_PORT);
    if(conn->err){
        cout<<"connection error:"<<conn->errstr<<endl;;
    }

    string com = "set " + key + " " + value;

    redisReply* reply = (redisReply*)redisCommand(conn, com.c_str());
    freeReplyObject(reply);

    redisFree(conn);
}


/*
 * FUNCTION: Get
 * INPUT: string key
 * OUTPUT: string value
 * (SIDE)EFFECTS: redis get
 */
string redisGet(string key) {

    redisContext* conn = redisConnect(REDIS_IP, REDIS_PORT);
    if(conn->err){
        cout<<"connection error:"<<conn->errstr<<endl;;
    }

    string com = "get " + key;

    redisReply* reply = (redisReply*)redisCommand(conn, com.c_str());

    string value(reply->str);

    freeReplyObject(reply);

    redisFree(conn);

    return value;

}

