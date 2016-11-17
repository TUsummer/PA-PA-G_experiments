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

/*
 * FUNCTION: Set
 * INPUT: string key, string value
 * OUTPUT:
 * (SIDE)EFFECTS: redis set
 */
void redisHSet(string key, string value) {
    redisContext* conn = redisConnect(REDIS_IP, REDIS_PORT);
    if(conn->err){
        cout<<"connection error:"<<conn->errstr<<endl;;
    }

    string com = "hset " + key + " " + value + " ''";

    redisReply* reply = (redisReply*)redisCommand(conn, com.c_str());
    freeReplyObject(reply);

    redisFree(conn);
}



map<string, list<RequestInfo> > GetAllRequest() {
	map<string, list<RequestInfo> > requests;
	vector<string> keys = getAllKeys();

	cout<<"keys:"<<keys.size()<<endl;

	for(int i=0; i<keys.size(); i++) {
		list<RequestInfo> req = redisHGetAll(keys[i]);
		requests[keys[i]] = req;
	}

	return requests;
}

vector<string> getAllKeys() {
	vector<string> keys;

    redisContext* conn = redisConnect(REDIS_IP, REDIS_PORT);
    if(conn->err){
        cout<<"connection error:"<<conn->errstr<<endl;;
    }

    string com = "keys *";

    redisReply* reply = (redisReply*)redisCommand(conn, com.c_str());

    if(reply->type == REDIS_REPLY_ARRAY) {
    	for(int i=0 ; i<reply->elements; i++) {
    		keys.push_back(reply->element[i]->str);
    	}
    } else {
    	keys.push_back(reply->str);
    }

    freeReplyObject(reply);

    redisFree(conn);

    return keys;
}

//HGETALL key 返回哈希表 key 中，所有的域和值。
//成功返回true 否则false
list<RequestInfo> redisHGetAll(string key) {
    redisContext* conn = redisConnect(REDIS_IP, REDIS_PORT);
    if(conn->err){
        cout<<"connection error:"<<conn->errstr<<endl;;
    }

    string com = "HKEYS " + key;
    redisReply *reply = (redisReply*)redisCommand(conn, com.c_str());

    list<RequestInfo> requests;

    if(reply->type == REDIS_REPLY_ARRAY) {
        for(int i=0 ; i<reply->elements; i++) {
            RequestInfo request = string2Request(reply->element[i]->str, PATTERN);
            requests.push_back(request);
        }
        freeReplyObject(reply);
    } else {
    	cout<<reply->str<<endl;
    	RequestInfo request = string2Request(reply->str, PATTERN);
    	requests.push_back(request);
    }

    com = "DEL " + key;
    reply = (redisReply*)redisCommand(conn, com.c_str());


    return requests;
}
