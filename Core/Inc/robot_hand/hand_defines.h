/*
 * hand_defines.h
 *
 *  Created on: Oct 31, 2025
 *      Author: dik21
 */

#ifndef INC_ROBOT_HAND_HAND_DEFINES_H_
#define INC_ROBOT_HAND_HAND_DEFINES_H_

#define HAND_MIN_POS
#define HAND_MAX_POS
#define HAND_MAX_SPEED

#define RH_CONTROL_TASK_INTERVAL 4 // unit: ms

enum {
	FINGER_0_ID = 0,
	FINGER_1_ID,
	FINGER_2_ID,
	FINGER_3_ID,
	FINGER_4_ID,

	NUM_FINGERS,
};


#endif /* INC_ROBOT_HAND_HAND_DEFINES_H_ */
