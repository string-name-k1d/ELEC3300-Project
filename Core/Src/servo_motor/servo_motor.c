/*
 * servo_motor.c
 *
 */

#include "cmsis_os.h"
#include "servo_motor/servo_motor.h"
//#include ""

// ====================================================================================================================

#define _s servo[servo_id]

#define servo_angle_to_pos(angle) ((u8)(((float)angle / SERVO_MAX_ANGLE) * (u8)0xFF))
#define servo_pos_to_ccr(pos)	  ((( (float)pos / (u8)0xFF) * (SERVO_MAX_DUTY - SERVO_MIN_DUTY) + SERVO_MIN_DUTY) * tim->ARR)

// ====================================================================================================================
// ====================================================================================================================

Servo_Controller_t servo[NUM_SERVOS] = {};

// ====================================================================================================================


void servo_init(void) {
	for (u8 servo_id = 0; servo_id < NUM_SERVOS; ++servo_id) {
		// if (!servo[servo_id].init) {
		servo[servo_id].htim = servo_id / 4 + 2;
		servo[servo_id].ch = servo_id % 4;
		servo[servo_id].init = true;
		// }
	}

	  TIM2->PSC = SERVO_PSC;
	  TIM2->ARR = SERVO_ARR;
	  TIM3->PSC = SERVO_PSC;
	  TIM3->ARR = SERVO_ARR;

	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

inline TIM_TypeDef* servo_get_tim(u8 tid) {
	return (tid == 2)? TIM2: TIM3;
}

//inline TIM_HandleTypeDef* servo_get_tim_handle(u8 tid) {
//	switch (tid) {
//		case 2: return &htim2;
//		case 3: return &htim3;
//		default: return 0;
//	}
//}

// inline u32 servo_get_tim_channel(u8 ch_id) {
//	 return TIM_CHANNEL_1 + 4 * (id - 1);
// }

inline void servo_set_target_pos(u8 servo_id, u8 tar) {
	servo[servo_id].tar_pos = tar;
	servo[servo_id].last_set_pos_tick = get_tick();
}

inline i8 servo_get_pos(u8 servo_id) { return servo[servo_id].cur; }

inline void servo_apply(u8 servo_id) {
	TIM_TypeDef* tim = servo_get_tim(servo[servo_id].htim);
	u32 ccr = servo_pos_to_ccr(servo[servo_id].tar_pos);
	switch (servo[servo_id].ch) {
		case 1: tim->CCR1 = ccr; break;
		case 2: tim->CCR2 = ccr; break;
		case 3: tim->CCR3 = ccr; break;
		case 4: tim->CCR4 = ccr; break;
		default: break;
	}
}

void servo_update(u8 servo_id, u32 tick) {
	u32 dt = tick - servo[servo_id].last_set_pos_tick;
	servp[servo_id].cur = (float)_s.prev + dt * SERVO_SPEED * ((_s.tar_pos > _s.prev)? 1: -1);
//	servo[servo_id].cur = (float)servo[servo_id].prev * (dt) + (float)servo[servo_id].tar_pos * (dt);
	servo[servo_id].prev = servo[servo_id].cur;
}

void servo_task(void* const args) {
	servo_init();

	u32 tick = get_tick();
	while (1) {
		for (u8 sid = 0; sid < NUM_SERVOS; ++sid) {
			servo_apply(sid);
			servo_update(sid, tick);
		}
		osDelay(4);
	}
}
