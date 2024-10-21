#ifndef BMX_SERVO_H
#define BMX_SERVO_H

#include <cstddef> // for std::size_t
#include <ESP32Servo.h>

// abstract class to encapsulate SERVO control code,
// derived classes will cater for PWM SERVOs, DC SERVOs or stepper SERVOs

// abstract struct for SERVO configuration, will vary depending on implementation

#define MAX_SERVOS 16 // Adjust the size as needed

struct bmx_servo_config {
    unsigned int Servo_ID;               // ID of servo (courtesy index, internal to program)
    unsigned int GPIO_PIN;               // GPIO pin (on the physical board)
    unsigned int PWM_CHANNEL;            // PWM channel (on the physical board)
    unsigned int PWM_FREQ;               // PWM frequency (in Hz)
    unsigned int PWM_MIN;                // PWM min value (in microseconds)
    unsigned int PWM_MAX;                // PWM max value (in microseconds)

    float NUM_VALUE_MIN;                  // min numerical value (phsyical units like rad or rpm)
    float NUM_VALUE_MAX;                  // max numerical value (phsyical units like rad or rpm)

    unsigned int PWM_UPDATE_TIMESTEP;    // PWM update timestep (in milliseconds, commands are physically sent to the servo at this rate)
    float initial_value;                 // zero reference for the servo
    bool enabled;                        // enable motor
};
    

class BMXServo
{
    public:
        BMXServo(bmx_servo_config config);
        ~BMXServo();

        void setPos(float pos);
        void setPos_us(unsigned int pos_us);
        float getPos();
        void handle();

    private:    
        bmx_servo_config config;

        // from ESP32Servo.h library (madhephaestus/ESP32Servo@^3.0.5)
        Servo* servo;

        float pos;                      // units of rad
        unsigned int pos_target_us;     // units of microseconds
        float pos_target;               // units of rad
};

class BMXServoHandler
{
    public:
        BMXServoHandler(const unsigned int tick);
        ~BMXServoHandler();

        void addServo(BMXServo* servo);
        void removeServo(BMXServo* servo);
        unsigned int getServoCount();
        void handle();

    private:
        unsigned int tick; // time between handle() calls, in milliseconds
        unsigned int last_tick; // last time handle() was called, in milliseconds
        BMXServo* servos[MAX_SERVOS];
        std::size_t servo_count;
};


#endif 