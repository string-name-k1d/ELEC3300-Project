/*
 * display.c
 */
#include "Usr/lcd/display.h"

#include "Usr/robot_hand/hand_control.h"
#include "string.h"

#include "cmsis_os.h"


static Display_Handle_t disp = {
	.buf = {{}, {}},
	.cur_screen = 0,
	.cur_page = HOME_PAGE,
	.flags = 0,
};

// ============================================
// ============================================

__forceinline char* const disp_get_buf_addr(DISP_COORDS) { return &disp.buf[disp.cur_screen][DISP_COORDS_FLATTENED]; }

static __forceinline bool disp_changed(DISP_COORDS) {
	return disp.buf[disp.cur_screen][DISP_COORDS_FLATTENED] != disp.buf[0x01 ^ disp.cur_screen][DISP_COORDS_FLATTENED];
}

// ============================================
// ============================================

void disp_init(void) {
	// __disable_irq();
	LCD_INIT();
	// __enable_irq();
//	disp.page_last_update_tick = get_tick();
}

/**
 * @deprecated
 * type specific printing functions
 */
/*
void disp_print_i(DISP_COORDS, int i) {
#define MAX_INT_LEN 12
	char _buf[MAX_INT_LEN] = {};
	char* cur = &_buf[MAX_INT_LEN - 2];

	if (i == 0) {
		disp.buf[disp.cur_screen][(u16)row * DISP_MAX_COL + col] = '0';
		return;
	}

	if (i < 0) {
		_buf[0] = '-';
		i = -i;
	}

	while (i > 0) {
		*cur = (i % 10) + '0';
		--cur;
		i /= 10;
	}

	*cur = _buf[0];

	strcpy(disp_get_buf_addr(row, col), cur);
}
*/

void disp_print_i(DISP_COORDS, int i) { sprintf(disp_get_buf_addr(row, col), "%d", i); }

void disp_print_f(DISP_COORDS, float f) { sprintf(disp_get_buf_addr(row, col), "%f", f); }

void disp_print_s(DISP_COORDS, const char* str) { strcpy(disp_get_buf_addr(row, col), str); }

u8 disp_prints(DISP_COORDS, const char* str, ...) {
	va_list args;
	va_start(args, str);
	vsprintf(disp_get_buf_addr(col, row), str, args);
	va_end(args);
	return ++row;
}

void disp_update(void) {
	__disable_irq();

	for (u8 r = 0; r < DISP_MAX_ROW; ++r) {
		for (u8 c = 0; c < DISP_MAX_COL; ++c) {
			if (disp_changed(c, r)) {
				LCD_DrawChar((u16)c * WIDTH_EN_CHAR, (u16)r * HEIGHT_EN_CHAR,
							 disp.buf[disp.cur_screen][(u16)r * DISP_MAX_COL + c]);
			}
		}
	}

	__enable_irq();

	disp.cur_screen ^= 1; // toggle screen buffer
}

static void disp_page(u32 tick) {
	//	if (tick - disp.page_last_update_tick < 20)
	//		return;

	u8 r = 0;

	 disp_prints(0, r++, "Test 2: %d", tick);

	switch (disp.cur_page) {
		case HOME_PAGE: {
			// disp_print_s(DISP_MAX_COL / 2 - 2, DISP_MAX_ROW - 1, "HOME");
		} break;
		case RH_PAGE: {
			r = rh_controller_page(r);
		} break;
		default: break;
	}

	disp_update();
	disp.page_last_update_tick = tick;
}

inline void disp_set_page(Display_Page_t page) { disp.cur_page = page; }

void disp_clear(void) { memset(disp.buf, 0, DISP_MAX_ROW * DISP_MAX_COL); }

void display_task(void const* arguments) {
	disp_init();
	osDelay(100);

	//	LCD_Rst();
	u32 last_tick = get_tick();
	while (1) {
		osDelayUntil(&last_tick, 1);
		disp_page(last_tick);
		//		disp_page(get_tick());
		osDelay(100);
	}
}
