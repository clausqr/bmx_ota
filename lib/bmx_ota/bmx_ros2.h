#ifndef BMX_ROS2
#define BMX_ROS2

#include <Arduino.h>
#include <WiFi.h>

#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/string.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float32.h>
#include <std_msgs/msg/bool.h>

#define RCCHECK(fn)                  \
    {                                \
        rcl_ret_t temp_rc = fn;      \
        if ((temp_rc != RCL_RET_OK)) \
        {                            \
            error_loop();            \
        }                            \
    }
#define RCSOFTCHECK(fn)              \
    {                                \
        rcl_ret_t temp_rc = fn;      \
        if ((temp_rc != RCL_RET_OK)) \
        {                            \
        }                            \
    }

class BMXROS2 {
public:
    BMXROS2();
    ~BMXROS2();

    void handle();

    // Static method for timer callback wrapper
    static void timer_callback_wrapper(rcl_timer_t *timer, int64_t last_call_time);

private:
    void error_loop();
    void timer_callback(rcl_timer_t *timer, int64_t last_call_time);

    rclc_support_t support;
    rcl_node_t node;
    rcl_publisher_t publisher;
    rcl_timer_t timer;
    rcl_allocator_t allocator;
    rclc_executor_t executor;
    std_msgs__msg__Int32 int_msg;
    

    // Static instance pointer
    static BMXROS2 *instance;

    void setup_transport();
};

#endif /* BMX_ROS2 */
