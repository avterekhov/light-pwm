#ifndef __PWM_DRIVER_H
#define __PWM_DRIVER_H

#include "pwm_control.h"
#include "gpio_control.h"

typedef const struct {
  int        id;
  pwm_pin_t  pwm;
  gpio_pin_t gpio;
} pwm_driver_descriptor_t;

typedef pwm_driver_descriptor_t* pwm_driver_descriptor_ptr;

static pwm_driver_descriptor_t PWM_DRIVER1_DSC = {1, PIN_P9_14, PIN_P9_12};
static pwm_driver_descriptor_t PWM_DRIVER2_DSC = {2, PIN_P9_16, PIN_P9_42};
static pwm_driver_descriptor_t PWM_DRIVER3_DSC = {3, PIN_P9_21, PIN_P9_42};
static pwm_driver_descriptor_t PWM_DRIVER4_DSC = {4, PIN_P9_22, PIN_P8_46};
static pwm_driver_descriptor_t PWM_DRIVER5_DSC = {5, PIN_P8_19, PIN_P8_30};
static pwm_driver_descriptor_t PWM_DRIVER6_DSC = {6, PIN_P8_13, PIN_P8_4};

static pwm_driver_descriptor_ptr PWM_DRIVER1 = &PWM_DRIVER1_DSC;
static pwm_driver_descriptor_ptr PWM_DRIVER2 = &PWM_DRIVER2_DSC;
static pwm_driver_descriptor_ptr PWM_DRIVER3 = &PWM_DRIVER3_DSC;
static pwm_driver_descriptor_ptr PWM_DRIVER4 = &PWM_DRIVER4_DSC;
static pwm_driver_descriptor_ptr PWM_DRIVER5 = &PWM_DRIVER5_DSC;
static pwm_driver_descriptor_ptr PWM_DRIVER6 = &PWM_DRIVER6_DSC;

typedef struct {
  pwm_t* pwm;
  gpio_pin_t gpio_pin;
} pwm_driver_t;

pwm_driver_t* pwm_driver_open(pwm_driver_descriptor_ptr driver_id);
int pwm_driver_prepare_device(pwm_driver_descriptor_ptr driver_id);
void pwm_driver_close(pwm_driver_t* pwm_driver);
int pwm_driver_enable(pwm_driver_t* pwm_driver);
int pwm_driver_disable(pwm_driver_t* pwm_driver);
int pwm_driver_set_period(pwm_driver_t* pwm_driver, long period);
int pwm_driver_set_command(pwm_driver_t* pwm_driver, float command);

#endif
