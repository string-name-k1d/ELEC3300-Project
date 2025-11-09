/*
 * glove_sensor.c
 */

#include "Usr/glove_sensor/glove_sensor.h"

#if defined(ROBOT_GLOVE_SENSOR)

void gs_init(void);
void gs_read(void);
void gs_update(void);
void gs_send(void);
void gs_task(void* const args);

#endif
