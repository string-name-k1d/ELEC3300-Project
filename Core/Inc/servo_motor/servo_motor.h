/*
 * servo_motor.h
 *
 *  Created on: Nov 5, 2025
 *      Author: dik21
 */

#ifndef INC_SERVO_MOTOR_SERVO_MOTOR_H_
#define INC_SERVO_MOTOR_SERVO_MOTOR_H_

#include "utils/utils.h"

#define SERVO_MAX_ANGLE 90.f
#define SERVO_MAX_DUTY 1.f
#define SERVO_MIN_DUTY 0.5f

#define NUM_SERVOS 5

typedef struct {
	struct {
		u8 htim : 3;
		u8 ch : 2;
		u8 init : 1;
	};
	u8 cur; // estimated actual position
	u8 prev;
	u8 tar_pos; // target position to reach

	u32 last_set_pos_tick;
} Servo_Controller_t;


void servo_init(u8 servo_id, u8 tim, u8 ch);
void servo_set_target_pos(u8 servo_id, u8 tar);
i8 servo_get_pos(u8 servo_id);
void servo_apply(u8 servo_id);

#endif /* INC_SERVO_MOTOR_SERVO_MOTOR_H_ */
