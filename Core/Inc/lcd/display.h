/*
 * display.h
 *
 *  Created on: Oct 28, 2025
 *      Author: dik21
 */

#ifndef INC_LCD_DISPLAY_H_
#define INC_LCD_DISPLAY_H_

#include "lcd/lcd.h"
#include "stdio.h"
#include "utils/utils.h"


#define DISP_MAX_ROW (LCD_DispWindow_PAGE / HEIGHT_EN_CHAR)
#define DISP_MAX_COL (LCD_DispWindow_COLUMN / WIDTH_EN_CHAR)

#define DEFAULT_PAGE HOME_PAGE

#define DISP_COORDS			   u8 row, u8 col
#define DISP_MAX_PRINT_BUF_LEN 30


typedef enum {
	HOME_PAGE = 0,
	RH_PAGE,
	NUM_DISP_PAGE,
} Display_Page_t;


typedef struct {
	char buf[DISP_MAX_ROW * DISP_MAX_COL];		  // buffer
	char contam[DISP_MAX_ROW * DISP_MAX_COL / 8]; // 1 bit contam

	Display_Page_t cur_page;

	u32 tft_last_update_tick;
	u32 page_last_update_tick;

	union {
		struct {
			u8 init_flag : 1;
			//			u8 page_contam_flag : 1;
		};
		u8 flags;
	};
} Display_Handle_t;


extern inline void disp_set_N_contam(u16 start, u16 n);
extern inline char* const disp_get_buf_addr(u8 row, u8 col);


void disp_init(void);

#define disp_print(row, col, ...)                                                                \
	{                                                                                            \
		sprintf(disp_get_buf_addr(row, col), __VA_ARGS__);                                       \
		disp_set_N_contam(((u16)row * DISP_MAX_COL + col), strlen(disp_get_buf_addr(row, col))); \
	}


void disp_update(u32 tick);
void disp_clear(void);

void disp_page_update(void);
void disp_set_page(Display_Page_t page);

void display_task(void* const arguments);

#endif /* INC_LCD_DISPLAY_H_ */
