#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 256
#define QUEUE_A_KEY 0x1234
#define QUEUE_B_KEY 0x5678

struct message {
    long mtype;
    char mtext[MSG_SIZE];
};

#endif
