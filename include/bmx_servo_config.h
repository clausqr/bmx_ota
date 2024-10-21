#ifndef BMX_SERVO_CONFIG
#define BMX_SERVO_CONFIG
// describe servo configuration
#include "bmx_servo.h"
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 

// common servo configuration
#define SERVO_PWM_FREQ 50
#define SERVO_PWM_MIN 1000
#define SERVO_PWM_MAX 2000
#define SERVO_PWM_UPDATE_TIMESTEP 20

// servo specific configuration
bmx_servo_config servo1_config = {
    .Servo_ID = 0,
    .GPIO_PIN = 2,
    .PWM_CHANNEL = 0,
    .PWM_FREQ = SERVO_PWM_FREQ,
    .PWM_MIN = SERVO_PWM_MIN,
    .PWM_MAX = SERVO_PWM_MAX,
    .NUM_VALUE_MIN = 0,
    .NUM_VALUE_MAX = 180,
    .PWM_UPDATE_TIMESTEP = SERVO_PWM_UPDATE_TIMESTEP,
    .initial_value = 90,
    .enabled = true
};

bmx_servo_config servo2_config = {
    .Servo_ID = 1,
    .GPIO_PIN = 4,
    .PWM_CHANNEL = 1,
    .PWM_FREQ = SERVO_PWM_FREQ,
    .PWM_MIN = SERVO_PWM_MIN,
    .PWM_MAX = SERVO_PWM_MAX,
    .NUM_VALUE_MIN = 0,
    .NUM_VALUE_MAX = 180,
    .PWM_UPDATE_TIMESTEP = SERVO_PWM_UPDATE_TIMESTEP,
    .initial_value = 90,
    .enabled = true
};

bmx_servo_config servo3_config = {
    .Servo_ID = 2,
    .GPIO_PIN = 5,
    .PWM_CHANNEL = 2,
    .PWM_FREQ = SERVO_PWM_FREQ,
    .PWM_MIN = SERVO_PWM_MIN,
    .PWM_MAX = SERVO_PWM_MAX,
    .NUM_VALUE_MIN = 0,
    .NUM_VALUE_MAX = 180,
    .PWM_UPDATE_TIMESTEP = SERVO_PWM_UPDATE_TIMESTEP,
    .initial_value = 90,
    .enabled = true
};

bmx_servo_config servo4_config = {
    .Servo_ID = 3,
    .GPIO_PIN = 18,
    .PWM_CHANNEL = 3,
    .PWM_FREQ = SERVO_PWM_FREQ,
    .PWM_MIN = SERVO_PWM_MIN,
    .PWM_MAX = SERVO_PWM_MAX,
    .NUM_VALUE_MIN = 0,
    .NUM_VALUE_MAX = 180,
    .PWM_UPDATE_TIMESTEP = SERVO_PWM_UPDATE_TIMESTEP,
    .initial_value = 90,
    .enabled = true
};


#endif /* BMX_SERVO_CONFIG */
