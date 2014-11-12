#ifndef __PWM_DRIVER2_H
#define __PWM_DRIVER2_H

#include "pwm_control.h"
#include "gpio_control.h"

/**
 * pwm_driver2_descriptor_t
 * 
 * Driver2 descriptor
 *
 * @param id:        driver ID - exclusively for reporting purpose
 * @param pwm:       pwm pin
 * @param direction: gpio pin for direction
 * @param enable:    gpio pin for enables
 */
typedef const struct {
  int        id;
  pwm_pin_t  pwm;
  gpio_pin_t direction;
  gpio_pin_t enable;
} pwm_driver2_descriptor_t;

typedef pwm_driver2_descriptor_t* pwm_driver2_descriptor_ptr;

/**
 * pwm_driver2_t
 * 
 * Driver2 structure
 *
 * @param pwm:       pwm controller pointer
 * @param direction: gpio controller pointer
 * @param enable:    enable pin
 */
typedef struct {
  pwm_t*     pwm;
  gpio_t*    direction;
  gpio_pin_t enable;
} pwm_driver2_t;

pwm_driver2_t* pwm_driver2_open(pwm_driver2_descriptor_ptr driver_id);
int pwm_driver2_prepare_device(pwm_driver2_descriptor_ptr driver_id);
void pwm_driver2_close(pwm_driver2_t* pwm_driver2);
int pwm_driver2_enable(pwm_driver2_t* pwm_driver2);
int pwm_driver2_disable(pwm_driver2_t* pwm_driver2);
int pwm_driver2_set_period(pwm_driver2_t* pwm_driver2, long period);
int pwm_driver2_set_command(pwm_driver2_t* pwm_driver2, float command);

#endif
