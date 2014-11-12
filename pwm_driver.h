/**
 * Aliases for pwm driver types and functions.
 *
 * The name of the driver should be defined in PWM_DRIVER_NAME
 * The default is set to 1
 */

#ifndef __PWM_DRIVER_H
#define __PWM_DRIVER_H

#ifndef PWM_DRIVER_NAME
#define PWM_DRIVER_NAME 1
#endif

#define STRINGIFY(A) _STRINGIFY(A)
#define _STRINGIFY(A) #A

#define __include_pwm_driver(driver_name) pwm_driver##driver_name
#define _include_pwm_driver(driver_name) __include_pwm_driver(driver_name)
#define include_pwm_driver _include_pwm_driver(PWM_DRIVER_NAME)
#define _add_dot_h(str) str.h
#define _pwm_driver_filename _add_dot_h(include_pwm_driver)

#include STRINGIFY(_pwm_driver_filename)

#define __pwm_driver_descriptor_t(driver_name)   pwm_driver##driver_name##_descriptor_t
#define __pwm_driver_descriptor_ptr(driver_name) pwm_driver##driver_name##_descriptor_ptr
#define __pwm_driver_t(driver_name)              pwm_driver##driver_name##_t
#define __pwm_driver_prepare_device(driver_name) pwm_driver##driver_name##_prepare_device
#define __pwm_driver_open(driver_name)           pwm_driver##driver_name##_open
#define __pwm_driver_close(driver_name)          pwm_driver##driver_name##_close
#define __pwm_driver_enable(driver_name)         pwm_driver##driver_name##_enable
#define __pwm_driver_disable(driver_name)        pwm_driver##driver_name##_disable
#define __pwm_driver_set_command(driver_name)    pwm_driver##driver_name##_set_command

#define _pwm_driver_descriptor_t(driver_name)   __pwm_driver_descriptor_t(driver_name)
#define _pwm_driver_descriptor_ptr(driver_name) __pwm_driver_descriptor_ptr(driver_name)
#define _pwm_driver_t(driver_name)              __pwm_driver_t(driver_name)
#define _pwm_driver_prepare_device(driver_name) __pwm_driver_prepare_device(driver_name)
#define _pwm_driver_open(driver_name)           __pwm_driver_open(driver_name)
#define _pwm_driver_close(driver_name)          __pwm_driver_close(driver_name)
#define _pwm_driver_enable(driver_name)         __pwm_driver_enable(driver_name)
#define _pwm_driver_disable(driver_name)        __pwm_driver_disable(driver_name)
#define _pwm_driver_set_command(driver_name)    __pwm_driver_set_command(driver_name)

#define pwm_driver_descriptor_t   _pwm_driver_descriptor_t(PWM_DRIVER_NAME)
#define pwm_driver_descriptor_ptr _pwm_driver_descriptor_ptr(PWM_DRIVER_NAME)
#define pwm_driver_t              _pwm_driver_t(PWM_DRIVER_NAME)
#define pwm_driver_prepare_device _pwm_driver_prepare_device(PWM_DRIVER_NAME)
#define pwm_driver_open           _pwm_driver_open(PWM_DRIVER_NAME)
#define pwm_driver_close          _pwm_driver_close(PWM_DRIVER_NAME)
#define pwm_driver_enable         _pwm_driver_enable(PWM_DRIVER_NAME)
#define pwm_driver_disable        _pwm_driver_disable(PWM_DRIVER_NAME)
#define pwm_driver_set_command    _pwm_driver_set_command(PWM_DRIVER_NAME)

#endif
