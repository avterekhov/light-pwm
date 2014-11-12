#ifndef __PWM_DRIVER1_H
#define __PWM_DRIVER1_H

#include "pwm_control.h"
#include "gpio_control.h"

/**
 * pwm_driver1_descriptor_t
 * 
 * Driver1 descriptor
 *
 * @id:   driver ID - exclusively for reporting purpose
 * @pwm:  pwm pin
 * @gpio: gpio pin for enables
 */
typedef const struct {
  int        id;
  pwm_pin_t  pwm;
  gpio_pin_t gpio;
} pwm_driver1_descriptor_t;

typedef pwm_driver1_descriptor_t* pwm_driver1_descriptor_ptr;

/**
 * pwm_driver1_t
 * 
 * Driver1 structure
 *
 * @pwm:       pwm controller pointer
 * @gpio_pin:  gpio enable pin
 */
typedef struct {
  pwm_t* pwm;
  gpio_pin_t gpio_pin;
} pwm_driver1_t;

pwm_driver1_t* pwm_driver1_open(pwm_driver1_descriptor_ptr driver_id);
int pwm_driver1_prepare_device(pwm_driver1_descriptor_ptr driver_id);
void pwm_driver1_close(pwm_driver1_t* pwm_driver1);
int pwm_driver1_enable(pwm_driver1_t* pwm_driver1);
int pwm_driver1_disable(pwm_driver1_t* pwm_driver1);
int pwm_driver1_set_period(pwm_driver1_t* pwm_driver1, long period);
int pwm_driver1_set_command(pwm_driver1_t* pwm_driver1, float command);

#endif
