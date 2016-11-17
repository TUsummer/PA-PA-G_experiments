/**
 * ################################################
 * ################### Socket ####################
 * ################################################
 *
 * Version: 1.0
 * File: socket.cpp
 * Author: Jie Wang
 * Description: Socket Communications
 * Date: 2016-09-19
 * Copyright (C) 2016 NAOC-TJUCS
 **/

#include "socket.h"

/*
 * FUNCTION: send message to server
 * INPUT: RequestInfo request && string pattern
 * OUTPUT:
 * (SIDE)EFFECTS: send message to server
 */
void send(string ip, RequestInfo request, string pattern) {
	struct sockaddr_in s_in;
	int s_fd;

	memset((void *)&s_in,0,sizeof(s_in));

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(CACHE_PORT);
	inet_pton(AF_INET, ip.c_str(), (void *)&s_in.sin_addr);

	s_fd = socket(AF_INET,SOCK_STREAM,0);

	connect(s_fd,(struct sockaddr *)&s_in,sizeof(s_in));

	string reqStr = request2String(request, pattern);

	write(s_fd, reqStr.c_str(), reqStr.size());

	close(s_fd);
}


/*
 * FUNCTION: send EOF to server
 * INPUT:
 * OUTPUT:
 * (SIDE)EFFECTS: send EOF to server
 */
void reqEOF() {

	struct sockaddr_in s_in;
	int s_fd;

	memset((void *)&s_in,0,sizeof(s_in));

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(SERVER_PORT);

	vector<string> ips = split(SERVER_IP, ",");

	string msg = "EOF";

	for(int i=0; i<ips.size(); i++) {
		inet_pton(AF_INET, ips[i].c_str(), (void *)&s_in.sin_addr);

		s_fd = socket(AF_INET,SOCK_STREAM,0);

		connect(s_fd,(struct sockaddr *)&s_in,sizeof(s_in));

		write(s_fd, msg.c_str(), msg.size());

		close(s_fd);
	}


}

/*
 * FUNCTION: receive message from client
 * INPUT:
 * OUTPUT: RequestInfo
 * (SIDE)EFFECTS: receive message from client
 */
RequestInfo recevice(string pattern) {
    struct sockaddr_in s_in;//server address structure
    struct sockaddr_in c_in;//client address structure
    int l_fd,c_fd;
    socklen_t len;
    char buf[NUM_MAX];//content buff area

    memset((void *)&s_in,0,sizeof(s_in));
    //bzero((void *)&s_in,sizeof(s_in));
    s_in.sin_family = AF_INET;//IPV4 communication domain
    s_in.sin_addr.s_addr = INADDR_ANY;//accept any address
    s_in.sin_port = htons(SERVER_PORT);//change port to netchar

    l_fd = socket(AF_INET,SOCK_STREAM,0);//socket(int domain, int type, int protocol)

    bind(l_fd,(struct sockaddr *)&s_in,sizeof(s_in));

    listen(l_fd,10);//lisiening start

    while(1){
        c_fd = accept(l_fd,(struct sockaddr *)&c_in,&len);

        read(c_fd, buf, NUM_MAX);//read the message send by client

        string reqStr(buf);

        return string2Request(reqStr, pattern);

        close(c_fd);
    }

}
