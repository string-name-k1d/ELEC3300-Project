/*
 * servo_motor.h
 *
 *  Created on: Nov 5, 2025
 *      Author: dik21
 */

#ifndef INC_SERVO_MOTOR_SERVO_MOTOR_H_
#define INC_SERVO_MOTOR_SERVO_MOTOR_H_

#include "Usr/utils/utils.h"

// =============================================================================================================
// =============================================================================================================

#define SERVO_TIM_CLK_FREQ (72000000)
#define SERVO_PSC		   (u16)(255) // TODO: change
#define SERVO_ARR		   (u16)(5624)

#define SERVO_FREQ		  50 // Hz
#define SERVO_PERIOD	  (1 / SERVO_FREQ)
#define SERVO_MAX_ON_TIME (2) // ms
#define SERVO_MIN_ON_TIME (1) // ms

#define SERVO_MAX_ANGLE 180.f // [0, 180]
#define SERVO_MAX_DUTY	0.1f  // 10%
#define SERVO_MIN_DUTY	0.05f // 5%

#define SERVO_SPEED 10.f // unit: deg / s

#define NUM_SERVOS 5


// =============================================================================================================
// =============================================================================================================

typedef struct {
	struct {
		u8 htim : 3;
		u8 ch : 2;
		u8 init : 1;
	};
	u8 pos; // estimated actual position
	u8 prev;
	u8 tar_pos; // target position to reach

	u32 last_apply_tick;
} Servo_Controller_t;


// =============================================================================================================
// =============================================================================================================


void servo_init(void);
void servo_set_target_pos(u8 servo_id, u8 tar);
i8 servo_get_pos(u8 servo_id);
void servo_apply(void);
void servo_update(u32 tick);
void servo_task(void const *args);

#endif /* INC_SERVO_MOTOR_SERVO_MOTOR_H_ */
