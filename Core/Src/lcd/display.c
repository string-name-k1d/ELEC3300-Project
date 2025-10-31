/*
 * display.c
 *
 *  Created on: Oct 28, 2025
 *      Author: dik21
 */
#include "lcd/display.h"

#include "string.h"
#include "utils/utils.h"

#include "cmsis_os.h"


static Display_Handle_t disp = {
	.buf = {},
	.contam = {},
	.cur_page = HOME_PAGE,
	.flags = 0,
};

__forceinline char* const disp_get_buf_addr(u8 row, u8 col) { return &disp.buf[row * DISP_MAX_COL + col]; }

static __forceinline u8 disp_get_contam(u16 enc_val) { return (disp.contam[enc_val / 8] >> (enc_val % 8)) & 0x01; }

static __forceinline void disp_set_contam(u16 enc_val) { disp.contam[enc_val / 8] |= 0x01 << (enc_val % 8); }

static __forceinline void disp_reset_contam(u16 enc_val) { disp.contam[enc_val / 8] &= ~(0x01 << (enc_val % 8)); }

/**
 * @brief: sets n bits in contam array
 */
__forceinline void disp_set_N_contam(u16 start, u16 n) {
	u8 start_byte_offset = start % 8;
	u8 end_byte_offset = (start + n) % 8;
	u8 start_byte_idx = start / 8;
	u8 end_byte_idx = (start + n) / 8;
	u8 n_byte_copied = end_byte_idx - start_byte_idx + (end_byte_offset == 0) - (start_byte_offset != 0);

	memset(&disp.contam[start_byte_idx + (start_byte_offset != 0)], 0xFF, n_byte_copied);
	disp.contam[start_byte_idx] |= ~((0x01 << start_byte_offset) - 1);
	disp.contam[end_byte_idx] |= ((0x01 << end_byte_offset) - 1);
}

void disp_init(void) {
	LCD_INIT();
	disp.tft_last_update_tick = get_tick();
	disp.page_last_update_tick = get_tick();
}


void disp_print_i(DISP_COORDS, int i) {
#define MAX_INT_LEN 12
	char _buf[MAX_INT_LEN] = {};
	char* cur = &_buf[MAX_INT_LEN - 2];

	if (i == 0) {
		disp.buf[(u16)row * DISP_MAX_COL + col] = '0';
		disp_set_contam((u16)row * DISP_MAX_COL + col);
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

	strcpy(&disp.buf[(u16)row * DISP_MAX_COL + col], _buf);
	disp_set_N_contam((u16)row * DISP_MAX_COL + col, _buf + MAX_INT_LEN - 1 - cur);
}

void disp_print_f(DISP_COORDS, float f) {
	sprintf(disp_get_buf_addr(row, col), "%f", f);
	disp_set_N_contam((u16)row * DISP_MAX_COL + col, strlen(disp_get_buf_addr(row, col)));
}

void disp_print_s(DISP_COORDS, const char* str) {
	strcpy(&disp.buf[(u16)row * DISP_MAX_COL + col], str);
	disp_set_N_contam((u16)row * DISP_MAX_COL + col, strlen(str));
}

// void disp_print(u8 row, u8 col, const char* txt, ...) {
//	va_list args;
//	va_start(args, txt);
//
//}

void disp_update(u32 tick) {
	if (tick - disp.tft_last_update_tick < 50)
		return;

	for (u16 i = 0; i < DISP_MAX_ROW * DISP_MAX_COL; ++i) {
		if (disp_get_contam(i)) {
			LCD_DrawChar(i % DISP_MAX_COL * WIDTH_EN_CHAR, i / DISP_MAX_COL * HEIGHT_EN_CHAR, disp.buf[i]);
		}
	}
	//	for (u8 r = 0; r < DISP_MAX_ROW; ++r) {
	//		for (u8 c = 0; c < DISP_MAX_COL; ++c) {
	//			if (disp_get_contam(r, c)) {
	//				LCD_DrawStringN(c, r, disp.buf[r * DISP_MAX_COL + c], DISP_MAX_ROW);
	//			}
	//		}
	//	}

	memset(disp.contam, 0x00, sizeof(disp.contam));
	disp.tft_last_update_tick = tick;
}

void disp_page(u32 tick) {
	if (tick - disp.page_last_update_tick < 20)
		return;

	u8 r = 0;

	disp_print(0, 0, "Test");
	disp_print_i(0, r++, get_tick());

	switch (disp.cur_page) {
		case HOME_PAGE: {
			disp_print_s(DISP_MAX_COL / 2 - 4, DISP_MAX_ROW - 1, "HOME");
		} break;
		case RH_PAGE: {
			r = rh_controller_page(r);
		} break;
		default: break;
	}

	disp_update(50);
	disp.page_last_update_tick = tick;
}

inline void disp_set_page(Display_Page_t page) { disp.cur_page = page; }

void disp_clear(void) { memset(disp.buf, 0, DISP_MAX_ROW * DISP_MAX_COL); }

void display_task(void* const argguments) {
	disp_init();
	osDelay(100);

	u32 last_tick = get_tick();
	while (1) {
		osDelayUntil(&last_tick, 1);
		disp_page(last_tick);
	}
}
