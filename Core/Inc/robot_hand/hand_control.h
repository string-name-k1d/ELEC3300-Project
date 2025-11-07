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
 * Controls each finger movement
 */
typedef struct {
	u8 pos;
	u8 tar_pos;
} RH_Finger_t;

/**
 * Represents physical hand state for each finger's position
 */
typedef struct {
	u8 finger_0_play : 1;
	u8 finger_1_play : 1;
	u8 finger_2_play : 1;
	u8 finger_3_play : 1;
	u8 finger_4_play : 1;
} RH_State_t;

/**
 * Logic control states for hand controller
 */
typedef enum {
	RH_TEST,
	RH_IDLE,
	RH_MANUAL,
	RH_PLAYSONG,
} RH_Controller_State;

/**
 * Logic controller for robot hand
 */
typedef struct {
	RH_Controller_State state;
	RH_Finger_t finger[NUM_FINGERS];
} RH_Controller_t;


/**
 * Sets target positions for the fingers
 */
void rh_controller_set_hand_state(RH_State_t tar);

/**
 * Sets control logic state for hand
 */
// extern inline void rh_controller_set_finger_pos(u8 fid, u8 pos);
// extern inline void rh_controller_set_hand_pos(u8* pos);
void rh_controller_set_state(RH_Controller_State state);
// extern inline bool rh_controller_check_state(RH_Controller_State state);

/**
 * Controls main logic flow for robot hand
 */
void rh_controller_init(void);
void rh_controller_fsm(void);
void rh_controller_apply(void);


void rh_controller_task(void* const args);

u8 rh_controller_page(u8 r);

#endif /* INC_ROBOT_HAND_HAND_CONTROL_H_ */
