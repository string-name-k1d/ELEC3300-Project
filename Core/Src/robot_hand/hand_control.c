/*
 * hand_control.c
 *
 *  Created on: Oct 31, 2025
 *      Author: dik21
 */


#include "robot_hand/hand_control.h"

#include "lcd/display.h"

#include "cmsis_os.h"


static RH_Controller_t rh = {

};

inline void rh_controller_set_finger_pos(u8 fid, u8 pos) {}
inline void rh_controller_set_hand_pos(u8* pos) {}
inline void rh_controller_set_hand_state(RH_State_t tar) {}
inline void rh_controller_apply_finger_pos(u8 fid) {}

void rh_controller_set_state(RH_Controller_State state) {
	if (state == rh.state) {
		return; // No state change needed
	}

	switch (state) {
		case RH_IDLE: {
		} break;
		case RH_MANUAL: {
		} break;
		case RH_PLAYSONG: {
		} break;
		// Invalid state, do nothing or handle error
		default: break;
	}
	rh.state = state;
}

__forceinline bool rh_controller_check_state(RH_Controller_State state) { return rh.state == state; }

// ============================================ //
// ======== Control FSM Control Task ========== //
// ============================================ //

void rh_controller_init(void) { rh.state = RH_IDLE; }

void rh_controller_fsm(void) {
	switch (rh.state) {
		case RH_IDLE: {
		} break;
		case RH_MANUAL: {
		} break;
		case RH_PLAYSONG: {
		} break;
		// case RH_MANUAL: {
		// } break;
		default: break;
	}
}

void rh_controller_apply(void) {
	for (u8 f_id; f_id < NUM_FINGERS; ++f_id) {
		rh_controller_apply_finger_pos(f_id);
		// Here you would add the code to actually move the finger hardware to finger->pos
	}
}


void rh_controller_task(void* const args) {
	rh_controller_init();

	u32 last_tick = get_tick();
	while (1) {
		osDelayUntil(&last_tick, RH_CONTROL_TASK_INTERVAL);

		rh_controller_fsm();
		rh_controller_apply();
	}
}

// ============================================ //
// =============== Display Page =============== //
// ============================================ //

u8 rh_controller_page(u8 r) {
	disp_print(0, r++, "State: %d", rh.state);
	disp_print(0, r++, "");
	return r;
}
