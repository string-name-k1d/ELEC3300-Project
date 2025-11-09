/*
 * glove_sensor.h
 *
 *  Created on: 2025年11月2日
 *      Author: dik21
 */

#ifndef INC_GLOVE_SENSOR_GLOVE_SENSOR_H_
#define INC_GLOVE_SENSOR_GLOVE_SENSOR_H_


#include "Usr/robot_hand/hand_defines.h"

typedef struct {
	float pos;
} GS_Finger_t;

void gs_init(void);
void gs_read(void);
void gs_update(void);
void gs_send(void);
void gs_task(void* const args);

#endif /* INC_GLOVE_SENSOR_GLOVE_SENSOR_H_ */
