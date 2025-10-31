/*
 * hand_control.h
 *
 *  Created on: Oct 31, 2025
 *      Author: dik21
 */

#ifndef INC_ROBOT_HAND_HAND_CONTROL_H_
#define INC_ROBOT_HAND_HAND_CONTROL_H_

#include "hand_defines.h"
#include "utils/utils.h"


/**
 * controls each finger movement
 */
typedef struct {
	i8 pos;
	i8 tar_pos;
} RH_Finger_t;

/**
 * states for hand controller
 */
typedef enum {
	RH_IDLE,
	RH_MANUAL,
	RH_PLAYSONG,
} RH_Controller_State;

typedef struct {
	RH_Controller_State state;
	RH_Finger_t finger[NUM_FINGERS];
} RH_Controller_t;


typedef struct {
	u8 finger_0_play : 1;
	u8 finger_1_play : 1;
	u8 finger_2_play : 1;
	u8 finger_3_play : 1;
	u8 finger_4_play : 1;
} RH_State_t;

void rh_controller_init(void);
void rh_controller_fsm(void);
void rh_controller_apply(void);

void rh_controller_set_hand(RH_State_t tar);

u8 rh_controller_page(u8 r);

void rh_controller_task();


#endif /* INC_ROBOT_HAND_HAND_CONTROL_H_ */
