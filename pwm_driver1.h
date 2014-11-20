#ifndef __PWM_DRIVER1_H
#define __PWM_DRIVER1_H

#include "pwm_control.h"
#include "gpio_control.h"

/**
 * @struct pwm_driver1_descriptor_t
 * 
 * @brief Driver1 descriptor
 *
 * @var pwm_driver1_descriptor_t::id
 * driver ID - exclusively for reporting purpose
 * @var pwm_driver1_descriptor_t::pwm
 * pwm pin
 * @var pwm_driver1_descriptor_t::gpio
 * gpio "enable" pin
 */
typedef const struct {
  int        id;
  pwm_pin_t  pwm;
  gpio_pin_t gpio;
} pwm_driver1_descriptor_t;

typedef pwm_driver1_descriptor_t* pwm_driver1_descriptor_ptr;

/**
 * @struct pwm_driver1_t
 * 
 * @brief Driver1 structure
 *
 * @var pwm_driver1_t::pwm
 * pwm controller pointer
 * @var pwm_driver1_t::gpio_pin
 * gpio enable pin
 */
typedef struct {
  pwm_t* pwm;
  gpio_pin_t gpio_pin;
} pwm_driver1_t;


/**
 * pwm_driver1_prepare_device
 *
 * @brief Prepares sysfs files for gpio and pwm
 * @param driver: driver descriptor
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver1_prepare_device(pwm_driver1_descriptor_ptr driver_id);

/**
 * pwm_driver1_open
 *
 * @brief Creates and initializes driver struct; sets zero to 50% duty cycle
 *
 * @param driver: driver descriptor
 * @return pointer to the driver struct or NULL if failed
 */
pwm_driver1_t* pwm_driver1_open(pwm_driver1_descriptor_ptr driver_id);

/**
 * pwm_driver1_close
 *
 * @brief Destroys driver struct; sets PWM duty to 50% and enable pin to 0
 * @param pwm_driver1: pointer to the driver
 */
void pwm_driver1_close(pwm_driver1_t* pwm_driver1);

/**
 * pwm_driver1_enable
 *
 * @brief Enables the driver; sets PWM run to 1 and enable pin to 1.
 *
 * @param pwm_driver1: pointer to the driver
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver1_enable(pwm_driver1_t* pwm_driver1);

/**
 * pwm_driver1_disable
 *
 * @brief Disables the driver; sets PWM run to 0 and enable pin to 0. 
 *
 * @param pwm_driver1: pointer to the driver
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver1_disable(pwm_driver1_t* pwm_driver1);

/**
 * pwm_driver1_set_period
 *
 * @brief Sets the period value
 *
 * !!! Notice that with ti_ehr_pwm patch changing the period of a
 * !!! driver also changes the period of the other pwm driver sitting
 * !!! on the same chip. For normal functioning be sure to execute the
 * !!! pwm_driver2_set_period for both drivers sharing the same chip.
 *
 * @param pwm_driver1: pointer to the driver
 * @param period:      desired valur of the period
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver1_set_period(pwm_driver1_t* pwm_driver1, long period);

/**
 * pwm_driver1_set_command - sets the command value
 *
 * @param pwm_driver1: pointer to the driver
 * @param command:     the commond between -1 and 1
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver1_set_command(pwm_driver1_t* pwm_driver1, float command);

#endif
