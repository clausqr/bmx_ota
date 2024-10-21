
#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <iostream>
#include <string>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float64.h>
#include <std_msgs/msg/string.h>
#include <rosidl_runtime_c/string_functions.h>

#include "bmx_ros2.h"

#define LED_PIN 13

BMXROS2 *BMXROS2::instance = nullptr;

void BMXROS2::error_loop()
{
    while (1)
    {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(100);
    }
}

void BMXROS2::timer_callback_wrapper(rcl_timer_t *timer, int64_t last_call_time)
{
    // Use the static instance pointer to call the instance method
    if (BMXROS2::instance) {
        BMXROS2::instance->timer_callback(timer, last_call_time);
    }
}

void BMXROS2::timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    RCLC_UNUSED(last_call_time);
    if (timer != NULL)
    {
        RCSOFTCHECK(rcl_publish(&publisher, &int_msg, NULL));
        int_msg.data++;
    }
}

BMXROS2::BMXROS2()
{
    // Set the static instance pointer to this instance
    BMXROS2::instance = this;

    int_msg.data = 0;

    // Initialize the executor and messages here if needed
    setup_transport();
    allocator = rcl_get_default_allocator();

    // create init_options
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

    // create node
    RCCHECK(rclc_node_init_default(&node, "bmx_ota", "", &support));

    // create publisher
    RCCHECK(rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "pps"));

    // create timer
    const unsigned int timer_timeout = 1000;

    // Initialize the timer with the correct callback
    RCCHECK(rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        BMXROS2::timer_callback_wrapper  // Use static method
    ));

    // create executor
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_timer(&executor, &timer));
}

void BMXROS2::setup_transport()
{

    // configure according to https://github.com/micro-ROS/micro_ros_platformio?tab=readme-ov-file#transport-configuration

    Serial.print("Setting up Micro-ROS transport...");

    IPAddress agent_ip(192, 168, 0, 114);
    size_t agent_port = 8888;

    char ssid[] = "";
    char psk[] = "";

    set_microros_wifi_transports(ssid, psk, agent_ip, agent_port);
}

BMXROS2::~BMXROS2()
{
    // Clean up resources here if needed
}

void BMXROS2::handle()
{
    Serial.print("Handling ROS2 messages on core ");
    Serial.println(xPortGetCoreID());
    RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
    Serial.println("Done handling ROS2 messages");
}
