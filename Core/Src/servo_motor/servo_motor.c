/*
 * servo_motor.c
 *
 */

#include "cmsis_os.h"
#include "servo_motor/servo_motor.h"
//#include ""

// ====================================================================================================================

static Servo_Controller_t servo[NUM_SERVOS] = {};

// ====================================================================================================================

#define servo_angle_to_pos(angle) ((u8)(((float)angle / SERVO_MAX_ANGLE) * (u8)0xFF))
#define servo_pos_to_ccr(pos)	  ((( (float)pos / (u8)0xFF) * (SERVO_MAX_DUTY - SERVO_MIN_DUTY) + SERVO_MIN_DUTY) * htim->Instance->ARR)


// ====================================================================================================================
// ====================================================================================================================


void servo_init(u8 servo_id, u8 htim, u8 ch) {
	// if (!servo[servo_id].init) {
	servo[servo_id].htim = htim;
	servo[servo_id].ch = ch;
	servo[servo_id].init = true;
	// }
}

inline TIM_HandleTypeDef* servo_get_tim_handle(u8 t_id) {
	switch (t_id) {
		case 2: return &htim2;
//		case 3: return &htim3;
		default: return 0;
	}
}

// inline u32 servo_get_tim_channel(u8 ch_id) { return TIM_CHANNEL_1; }

inline void servo_set_target_pos(u8 servo_id, u8 tar) {
	servo[servo_id].tar_pos = tar;
	servo[servo_id].last_set_pos_tick = get_tick();
}

inline i8 servo_get_pos(u8 servo_id) { return servo[servo_id].cur; }

inline void servo_apply(u8 servo_id) {
	TIM_HandleTypeDef* htim = servo_get_tim_handle(servo[servo_id].htim);
	// u32 ch = servo_get_tim_channel(servo[servo_id].ch);
	u32 ccr = servo_pos_to_ccr(servo[servo_id].tar_pos);
	switch (servo[servo_id].ch) {
		case 1: htim->Instance->CCR1 = ccr; break;
		case 2: htim->Instance->CCR2 = ccr; break;
		case 3: htim->Instance->CCR3 = ccr; break;
		case 4: htim->Instance->CCR4 = ccr; break;
		default: break;
	}
}

void servo_update(u8 servo_id, u32 tick) {
	servo[servo_id].cur = servo[servo_id].prev * (tick - servo[servo_id].last_set_pos_tick) + servo[servo_id].tar_pos;
	servo[servo_id].prev = servo[servo_id].cur;
}

void servo_task(void* const args) {
	for (u8 sid = 0; sid < NUM_SERVOS; ++sid) {
		servo_apply(sid);
	}

	u32 tick = get_tick();
	while (1) {
		for (u8 sid = 0; sid < NUM_SERVOS; ++sid) {
			servo_apply(sid);
			servo_update(sid, tick);
		}
		osDelay(4);
	}
}
