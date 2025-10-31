/*
 * hand_control.c
 *
 *  Created on: Oct 31, 2025
 *      Author: dik21
 */


#include "hand_control.h"
#include "lcd/display.h"
#include "cmsis_os.h"

static RH_Controller_t rh = {

};

void rh_controller_init(void) {

}

u8 rh_controller_page(u8 r) {
	disp_print(0, r++, "State: %d", rh.state);
	disp_print(0, r++, "");
	return r;
}

void rh_controller_task(void* const args) {
	rh_controller_init();

	while (1) {
		osDelay(RH_CONTROL_TASK_INTERVAL);
	}
}
