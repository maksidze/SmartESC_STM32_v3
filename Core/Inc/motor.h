#pragma once

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// motor hall sensor pins
#define HALL_3_Pin GPIO_PIN_0
#define HALL_3_GPIO_Port GPIOB
#define HALL_1_Pin GPIO_PIN_4
#define HALL_1_GPIO_Port GPIOB
#define HALL_2_Pin GPIO_PIN_5
#define HALL_2_GPIO_Port GPIOB

//#define FAST_LOOP_LOG
//#define DISABLE_DYNAMIC_ADC

#define P_FACTOR_I_Q 100
#define I_FACTOR_I_Q 2
#define P_FACTOR_I_D 1
#define I_FACTOR_I_D 1
#define MAX_D_FACTOR 1

#define PUSHASSIST_CURRENT 30
#define SIXSTEPTHRESHOLD 9000

typedef struct {
	q31_t Voltage;
	uint32_t Speed;
	q31_t i_d;
	q31_t i_q;
	q31_t i_q_setpoint;
	q31_t i_d_setpoint;
	q31_t i_setpoint_abs;
	int32_t i_q_setpoint_temp;
	int32_t i_d_setpoint_temp;
	q31_t u_d;
	q31_t u_q;
	q31_t u_abs;
	q31_t Battery_Current;
	uint8_t hall_angle_detect_flag;
	uint8_t char_dyn_adc_state;
	uint8_t assist_level;
	uint8_t regen_level;
	int8_t Temperature;
	int8_t system_state;
	int8_t mode;
	int8_t error_state;
	bool light;
	bool beep;
	uint8_t shutdown;
	int8_t speed_limit;
	int16_t phase_current_limit;
} MotorState_t;

typedef struct {
	q31_t Voltage;
	uint32_t speed;
	q31_t i_d;
	q31_t i_q;
	q31_t i_q_setpoint;
	q31_t i_d_setpoint;
	q31_t i_setpoint_abs;
	int32_t i_q_setpoint_temp;
	int32_t i_d_setpoint_temp;
	q31_t u_d;
	q31_t u_q;
	q31_t u_abs;
	q31_t Battery_Current;
	uint8_t hall_angle_detect_flag;
	uint8_t char_dyn_adc_state;
	uint8_t assist_level;
	uint8_t regen_level;
	int8_t Temperature;
	int8_t system_state;
	int8_t mode;
	int8_t error_state;
	bool light;
	bool beep;
	uint8_t shutdown;
	int8_t speed_limit;
	int16_t phase_current_limit;
} MotorStatePublic_t;

typedef struct {
	uint16_t wheel_cirumference;
	uint16_t p_Iq;
	uint16_t i_Iq;
	uint16_t p_Id;
	uint16_t i_Id;
	uint16_t TS_coeff;
	uint16_t PAS_timeout;
	uint16_t ramp_end;
	uint16_t throttle_offset;
	uint16_t throttle_max;
	uint16_t gear_ratio;
	uint8_t speedLimit;
	uint8_t pulses_per_revolution;
	uint16_t phase_current_max;
	int16_t spec_angle;
} MotorParams_t;

enum {
  Stop,
  SixStep,
  Interpolation,
  PLL
};

enum modes {
  eco=2,
  normal=0,
  sport=4
};

enum errors {hall=1,lowbattery=2,overcurrent=4};

extern q31_t q31_tics_filtered;
extern volatile uint16_t adcData[8];

int motor_init(MotorStatePublic_t* p_MotorStatePublic);
void autodetect();
void runPIcontrol();
static void motor_slow_loop(MotorStatePublic_t* p_MotorStatePublic);
static bool motor_pwm_get_state(void);
static void motor_disable_pwm(void);
static void motor_enable_pwm(void);

void _Error_Handler(char*, int);

#ifdef __cplusplus
}
#endif