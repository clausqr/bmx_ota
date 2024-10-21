#include <Arduino.h>
#include <ESP32Servo.h>

#include "bmx_servo.h"


BMXServoHandler::BMXServoHandler(const unsigned int tick_interval)
{
  this->tick = tick_interval;
  this->last_tick = millis();
    this->servo_count = 0;
}

BMXServoHandler::~BMXServoHandler() {
    for (std::size_t i = 0; i < servo_count; ++i) {
        delete servos[i];
        servos[i] = nullptr; // Optional: Clear the pointer
    }
}

void BMXServoHandler::addServo(BMXServo* servo) 
{
    if (servo_count < MAX_SERVOS) {
        servos[servo_count++] = servo;
        Serial.print("Servo added. Servo count: ");
        Serial.println(servo_count);
    } else {
        // Handle error: max servos reached
        // Optional: Log an error message or handle overflow
        Serial.println("Error: Max servos reached");
    }
}

void BMXServoHandler::removeServo(BMXServo* servo) {
    for (std::size_t i = 0; i < servo_count; ++i) {
        if (servos[i] == servo) {
            // Move the last servo to the current position to maintain continuity
            servos[i] = servos[--servo_count];
            servos[servo_count] = nullptr; // Optional: Clear the last position
            return;
        }
    }
    // Handle error: servo not found
    // Optional: Log an error message
}

unsigned int BMXServoHandler::getServoCount() 
{
    return servo_count;
}

void BMXServoHandler::handle() 
{
    for (std::size_t i = 0; i < servo_count; ++i) {
        if (servos[i]) {
            Serial.print("Servo count: ");
            Serial.println(servo_count);
            Serial.print("Handling servo ");
            Serial.println(i);
            servos[i]->handle();
        }
    }

}

BMXServo::BMXServo(bmx_servo_config config)
{
    this->config = config;
    this->setPos(config.initial_value);

    // attach servo
    this->servo = new Servo();
    ESP32PWM::allocateTimer(config.PWM_CHANNEL);
    this->servo->setPeriodHertz(config.PWM_FREQ);
    this->servo->attach(config.GPIO_PIN, config.PWM_MIN, config.PWM_MAX);
    this->servo->writeMicroseconds(config.initial_value);
}

void BMXServo::setPos(float pos)
{
    // Clip pos to within bounds
    if (pos < this->config.NUM_VALUE_MIN)
    {
        pos = this->config.NUM_VALUE_MIN;
    }
    else if (pos > this->config.NUM_VALUE_MAX)
    {
        pos = this->config.NUM_VALUE_MAX;
    }

    this->pos_target = pos;
    this->pos_target_us = (pos - this->config.NUM_VALUE_MIN) / (this->config.NUM_VALUE_MAX - this->config.NUM_VALUE_MIN) * (this->config.PWM_MAX - this->config.PWM_MIN) + this->config.PWM_MIN;
}

void BMXServo::setPos_us(unsigned int pos_us)
{

    // Clip pos_us to within bounds
    if (pos_us < this->config.PWM_MIN)
    {
        pos_us = this->config.PWM_MIN;
    }
    else if (pos_us > this->config.PWM_MAX)
    {
        pos_us = this->config.PWM_MAX;
    }

    pos_target_us = pos_us;
    pos_target = (pos_us - this->config.PWM_MIN) / (this->config.PWM_MAX - this->config.PWM_MIN) * (this->config.NUM_VALUE_MAX - this->config.NUM_VALUE_MIN) + this->config.NUM_VALUE_MIN;
}

float BMXServo::getPos()
{
    return this->pos;
}

void BMXServo::handle()
{
    this->servo->writeMicroseconds(this->pos_target_us);
    this->pos = this->pos_target;        
}