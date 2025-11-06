# Docs

- [rtos](#rtos)
- [display](#displaylcd)

## RTOS
In short, use threads (called tasks in code) to do stuff
1. define thread in .ioc or add by copying existing format in @file main.c
2. for the thread, write a task that does stuff with a never ending loop in it
3. add osDelay(period) in while loop to let cpu do other stuff

```c
// Step 1
@file main.c
...
  osThreadid someTaskHandle;
...

  osThreadDef(someTask, function_for_task, osPriorityNormal, 0, 128);
  someTaskHandle = osThreadCreate(osThread(someTask), NULL);
...
```

```c
// Step 2
@any file
...
  void someTask(void const * args) {
    // init stuff
    init_something();
    while (1) {
        // do stuff
        do_something();

        // Step 3
        // let other thread/task do stuff
        osDelay(100);
    }
  }
...
```

## display/lcd

1. Create page in @file display.h `enum Display_Page_t`
2. Add print content in switch case in @file display.c @function `display_page`
3. Use r variable for printing row as you like

```c
@file lcd/display.h
...
typedef enum {
	HOME_PAGE = 0,
    ...
    // << Add here
    SOME_PAGE
    ...
	NUM_DISP_PAGE,
} Display_Page_t;
...
```
```c
@file lcd/display.c
...
static void disp_page(u32 tick) {
    ...
    u8 r = 0;   // current row printing

	switch (disp.cur_page) {
		case HOME_PAGE: {
			disp_print_s(DISP_MAX_COL / 2 - 2, DISP_MAX_ROW - 1, "HOME");
		} break;
        // << Add here
        case SOME_PAGE: {
            r = some_page_display(r);
        } break;
		default: break;
	}
    ...
}
...
```