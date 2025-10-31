/*
 * modbus.h
 *
 * modbus protocol transceiver
 */

#ifndef INC_ROBOT_HAND_MODBUS_H_
#define INC_ROBOT_HAND_MODBUS_H_

#include "utils/utils.h"

// =============================================================================================================================
// =============================================================================================================================

/**
 * @brief: Function codes for R/W register
 */
#define READ_HOLDING_REG_FUNC	 0x03
#define PRESET_SINGLE_REG_FUNC	 0x06
#define PRESET_MULTIPLE_REG_FUNC 0x10

/**
 * @brief: Register address list
 */
#define HAND_ID_REG					0x03E8 // default 1; range [1, 254]
#define REDU_RATIO_REG				0x03EA
#define CLEAR_ERROR_REG				0x03EC
#define SAVE_REG					0x03ED
#define RESET_PARA_REG				0x03EE
#define RESERVE_REG					0x03F0
#define GESTURE_FORCE_CLB_REG		0x03F1
#define CURRENT_LIMIT_REG			0x03FC // unit: ma
#define DEFAULT_SPEED_SET_REG		0x0408
#define DEFAULT_FORCE_SET_REG		0x0414
#define VLTAGE_REG					0x05C0
#define POS_SET_REG					0x05C2
#define ANGLE_SET_REG				0x05CE
#define FORCE_SET_REG				0x05DA
#define SPEED_SET_REG				0x05F2
#define POS_ACT_REG					0x05FE
#define ANGLE_ACT_REG				0x060A
#define FORCE_ACT_REG				0x062E
#define CURRENT_REG					0x063A
#define ERROR_REG					0x0646
#define STATUS_REG					0x064C
#define TEMP_REG					0x0652
#define ACTION_SEQ_CHECK_DATA1_REG	0x07D0
#define ACTION_SEQ_CHECK_DATA2_REG	0x07D1
#define ACTION_SEQ_STEPNUM_REG		0x07D2
#define ACTION_SEQ_STEP_0_REG		0x07E0
#define ACTION_SEQ_STEP_1_REG		0x0806
#define ACTION_SEQ_STEP_2_REG		0x082C
#define ACTION_SEQ_STEP_3_REG		0x0852
#define ACTION_SEQ_STEP_4_REG		0x0878
#define ACTION_SEQ_STEP_5_REG		0x089E
#define ACTION_SEQ_STEP_6_REG		0x08C4
#define ACTION_SEQ_STEP_7_REG		0x08EA
#define ACTION_SEQ_INDEX_REG		0x0910
#define SAVE_ACTION_SEQ_REG			0x0911
#define SAVE_ACTION_SEQ_REG			0x0912
#define ACTION_ADJUST_FORCE_SET_REG 0x0914

/**
 * @brief: Finger offsets used for most registers
 */
#define FINGER_ADDR_OFFSET(f_id) FINGER_##f_id##_ADDR_OFFSET

#define FINGER_0_ADDR_OFFSET 0x00
#define FINGER_1_ADDR_OFFSET 0x02
#define FINGER_2_ADDR_OFFSET 0x04
#define FINGER_3_ADDR_OFFSET 0x06
#define FINGER_4_ADDR_OFFSET 0x08
#define FINGER_5_ADDR_OFFSET 0x0A

/**
 * @brief: Finger offsets used for ERROR, STATUS &TEMP registers
 */
#define FINGER_STATUS_ADDR_OFFSET(f_id) FINGER_##f_id##_STATUS_ADDR_OFFSET

#define FINGER_0_STATUS_ADDR_OFFSET 0x00
#define FINGER_1_STATUS_ADDR_OFFSET 0x01
#define FINGER_2_STATUS_ADDR_OFFSET 0x02
#define FINGER_3_STATUS_ADDR_OFFSET 0x03
#define FINGER_4_STATUS_ADDR_OFFSET 0x04
#define FINGER_5_STATUS_ADDR_OFFSET 0x05

/**
 * bit encoded error codes
 */
#define ERROR_LOCLED_MOTOR 0x01
#define ERROR_OVER_TEMP	   0x02
#define ERROR_OVER_CURRENT 0x04
#define ERROR_ABNORMAL_OP  0x08
#define ERROR_COMM		   0x10

/**
 * status code
 */
#define STATUS_UNCLENCHING									   0
#define STATUS_GRASPING										   1
#define STATUS_STOP_AFTER_REACHING_TARGET_POSITION			   2
#define STATUS_STOP_AFTER_REACHING_DEFINED_FORCE_CONTROL_VALUE 3
#define STATUS_STOP_DUE_TO_CURRENT_PROTECTION				   5
#define STATUS_STOP_DUE_TO_LOCKED_ROTOR_OF_ACTUATOR			   6
#define STATUS_STOP_DUE_TO_ACTUATOR_FAULT					   7

/**
 * @brief action registers
 */
#define ACTION_SEQ_CHECKDATA1_REG 2000
#define ACTION_SEQ_CHECKDATA2_REG 2001
#define ACTION_SEQ_STEPNUM_REG	  2002

#define ACTION_SEQ_STEP_0_REG 2016
#define ACTION_SEQ_STEP_1_REG 2054
#define ACTION_SEQ_STEP_2_REG 2092
#define ACTION_SEQ_STEP_3_REG 2130
#define ACTION_SEQ_STEP_4_REG 2168
#define ACTION_SEQ_STEP_5_REG 2206
#define ACTION_SEQ_STEP_6_REG 2244
#define ACTION_SEQ_STEP_7_REG 2282

#define ACTION_SEQ_INDEX_REG 2320
#define SAVE_ACTION_SEQ_REG	 2321
#define ACTION_SEQ_RUN_REG	 2322

// =============================================================================================================================
// =============================================================================================================================

typedef struct {
	byte addr;
	byte func_code;
	byte start_addr_h;
	byte start_addr_l;
	byte end_addr_h;
	byte end_addr_l;
	byte CRC;
} Modbus_Query_Frame_t;

// =============================================================================================================================
// =============================================================================================================================

void mb_write_reg(Modbus_Query_Frame_t* frame);
void mb_write_n_reg(Modbus_Query_Frame_t* frame, u8 count);
void mb_read_reg(Modbus_Query_Frame_t* frame);

#endif /* INC_ROBOT_HAND_MODBUS_H_ */
