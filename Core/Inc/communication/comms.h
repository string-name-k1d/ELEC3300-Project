/*
 * remote_comms.h
 *
 *  Created on: Oct 30, 2025
 *      Author: dik21
 */

#ifndef INC_COMMUNICATION_COMMS_H_
#define INC_COMMUNICATION_COMMS_H_

#include "utils/utils.h"


#define COMMS_MAX_BUF_SIZE		1024		// unit: byte
#define COMMS_TIMEOUT_THRESHOLD	1000		// unit: ms


typedef enum { COMMS_START = 0b11001100, COMMS_END = 0b00110011} Comms_Msg_Type;

/**
 * hand pos				min 7 bit
 * 6 fingers pos		min 4 bit each
 * timestamp(?)			min 8 bit
 */
typedef struct {

}Comms_Msg_t;


typedef struct {
	byte buf[COMMS_MAX_BUF_SIZE];

}Comms_Handler_t;


void comms_init(void);
void comms_send(Comms_Msg_t* msg);
void comms_recv_handler(void);


#endif /* INC_COMMUNICATION_COMMS_H_ */
