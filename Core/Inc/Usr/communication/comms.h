/*
 * remote_comms.h
 *
 *  Created on: Oct 30, 2025
 *      Author: dik21
 */

#ifndef INC_COMMUNICATION_COMMS_H_
#define INC_COMMUNICATION_COMMS_H_

#include "Usr/utils/utils.h"
#include "Usr/robot_hand/hand_defines.h"


#define COMMS_MAX_BUF_SIZE		  100 // unit: byte
#define COMMS_MIN_UPDATE_INTERVAL 50
#define COMMS_MAX_UPDATE_INTERVAL 300
#define COMMS_TIMEOUT_THRESHOLD	  1000 // unit: ms


#define COMMS_START_BYTE 0xCE
#define COMMS_END_BYTE	 0x03

/**
 * hand pos				min 7 bit
 * 6 fingers pos		min 4 bit each
 * timestamp(?)			min 8 bit
 */
typedef struct {
	// payload data start
	byte finger_pos[NUM_FINGERS];

	// payload data end
	// checking start
	byte check_sum;
} Comms_Msg_t;


typedef struct {
	byte buf[COMMS_MAX_BUF_SIZE];

	u32 last_recv_tick;
} Comms_Handler_t;


void comms_init(void);
void comms_send(Comms_Msg_t* msg);
void comms_recv_handler(void);
void comms_connection_check(void);


#endif /* INC_COMMUNICATION_COMMS_H_ */
