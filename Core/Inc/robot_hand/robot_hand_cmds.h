/*
 * robot_hand_cmds.h
 *
 * low level robot hand control
 */

#ifndef INC_ROBOT_HAND_ROBOT_HAND_CMDS_H_
#define INC_ROBOT_HAND_ROBOT_HAND_CMDS_H_

#define SEND_START_BYTE 0xEB
#define RECV_START_BYTE 0x90

#define READ_REG_INSTRUCTION 	0x11
#define WRITE_REG_INSTRUCTION 	0x12

enum {
	FINGER_0_ID = 0,
	FINGER_1_ID,
	FINGER_2_ID,
	FINGER_3_ID,
	FINGER_4_ID,
	FINGER_5_ID,
};

typedef union {
	struct {
		uint8_t start_byte;
		uint8_t second_byte;
		uint8_t hands_id;
		uint8_t frame_data_len;
	};
	uint8_t byte[4];
} RH_Common_Header_t;

#endif /* INC_ROBOT_HAND_ROBOT_HAND_CMDS_H_ */
