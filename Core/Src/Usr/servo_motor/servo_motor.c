/*
 * servo_motor.c
 *
 */

#include "Usr/servo_motor/servo_motor.h"

#include "cmsis_os.h"
#include "main.h"

//#include ""

// ====================================================================================================================

#define _s servo[servo_id]

#define servo_angle_to_pos(angle) ((u8)(((float)angle / SERVO_MAX_ANGLE) * (u8)0xFF))
#define servo_pos_to_angle(pos)	  ((float)(pos) / (u8)0xFF * SERVO_MAX_ANGLE)
#define servo_pos_to_ccr(pos) \
	((((float)pos / (u8)0xFF) * (SERVO_MAX_DUTY - SERVO_MIN_DUTY) + SERVO_MIN_DUTY) * tim->ARR)

 inline TIM_HandleTypeDef* servo_get_tim_handle(u8 tid) {
	return
		(tid == 2)? &htim2:
		(tid == 3)? &htim3:
		0;

}

 inline u32 servo_get_tim_channel(u8 chid) {
	 return TIM_CHANNEL_1 + 4 * (chid - 1);
 }

// ====================================================================================================================
// ====================================================================================================================

static Servo_Controller_t servo[NUM_SERVOS] = {
		[0] = {
			.htim = 2,
			.ch = 1,
		},
		[1] = {
			.htim = 2,
			.ch = 2,
		},
		[2] = {
			.htim = 2,
			.ch = 3,
			.init = true,
		},
		[3] = {
			.htim = 2,
			.ch = 1,
		},
		[4] = {
			.htim = 3,
			.ch = 1,
		},
};

// ====================================================================================================================


void servo_init(void) {
	for (u8 servo_id = 0; servo_id < NUM_SERVOS; ++servo_id) {
//		servo[servo_id].init = true;
	}

	TIM2->PSC = SERVO_PSC;
	TIM2->ARR = SERVO_ARR;
//	TIM3->PSC = SERVO_PSC;
//	TIM3->ARR = SERVO_ARR;

//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

__forceinline TIM_TypeDef* servo_get_tim(u8 tid) { return (tid == 2) ? TIM2 : TIM3; }

inline void servo_set_target_pos(u8 servo_id, u8 tar) {
	servo[servo_id].tar_pos = tar;
	//	servo[servo_id].last_set_pos_tick = get_tick();
}

inline i8 servo_get_pos(u8 servo_id) { return servo[servo_id].cur; }

inline void servo_apply(void) {
	u32 tick = get_tick();
	TIM_TypeDef* tim;
	u32 ccr;

	for (u8 servo_id = 0; servo_id < NUM_SERVOS; ++servo_id) {

		if (!_s.init)
			continue;

		tim = servo_get_tim(servo[servo_id].htim);
		ccr = servo_pos_to_ccr(servo[servo_id].tar_pos);

		switch (servo[servo_id].ch) {
			case 1: tim->CCR1 = ccr; break;
			case 2: tim->CCR2 = ccr; break;
			case 3: tim->CCR3 = ccr; break;
			case 4: tim->CCR4 = ccr; break;
			default: break;
		}

		_s.last_apply_tick = tick;
	}
}

void servo_update(u32 tick) {
	u32 dt;
	for (u8 servo_id; servo_id < NUM_SERVOS; ++servo_id) {
		dt = tick - _s.last_apply_tick;

		_s.prev = _s.cur;
		_s.cur = clamp((float)_s.cur + dt * SERVO_SPEED * ((_s.tar_pos > _s.cur) ? 1 : -1), _s.cur, _s.tar_pos);
		//	servo[servo_id].cur = (float)servo[servo_id].prev * (dt) + (float)servo[servo_id].tar_pos * (dt);
	}
}

static void servo_test(void) {
//	servo_set_target_pos((get_tick() / 2000) % 5, (get_tick() % 20000 < 10000) ? 255 : 0);
	servo_set_target_pos(2, (get_tick() % 20000 < 10000) ? 255 : 0);
}

void servo_task(void* const args) {
	servo_init();

		u32 tick = get_tick();
	while (1) {
		servo_test();
		servo_apply();
		servo_update(tick);
		osDelay(4);
	}
}
