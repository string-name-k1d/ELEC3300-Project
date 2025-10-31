/*
 * utils.h
 *
 * common definitions & short-hand functions
 */

#define true (1)
#define false (0)

#define __forceinline __attribute__((always_inline)) inline

#define ABS(val)	((val < 0)? -val: val)
#define IN_RANGE(val, lower, upper) (val > lower) && (val < upper)
#define get_tick()	HAL_GetTick()
#define min(a,b)	((a < b)? a: b)
#define max(a,b)	((a > b)? a: b)

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef uint8_t bool;
typedef uint8_t byte;

typedef union {
	struct {
		u8 upper;
		u8 lower;
	};
	u16 val;
} Short_Bytes_t;
