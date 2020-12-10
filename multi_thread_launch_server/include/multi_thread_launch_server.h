#ifndef NETWORK_PROGRAMMING_MULTI_THREAD_LAUNCH_SERVER_H
#define NETWORK_PROGRAMMING_MULTI_THREAD_LAUNCH_SERVER_H


#include <stdio.h>
#include <stdlib.h>
#include "common_net.h"
#include "shared_tcp_structs.h"
#include "common_thread.h"
#include "math.h"
#include <vector>
#define DEFAULT_PORT 5562
#define CONNECTION_QUEUE 100

LaunchProgResponse* compute(LaunchProgRequest*, LaunchProgResponse*);

//void handle_connection(SOCKET, sockaddr_in*);
THREAD_RESULT handle_connection(void*);

#endif //NETWORK_PROGRAMMING_MULTI_THREAD_LAUNCH_SERVER_H
