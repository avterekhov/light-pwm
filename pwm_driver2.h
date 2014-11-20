#ifndef __PWM_DRIVER2_H
#define __PWM_DRIVER2_H

#include "pwm_control.h"
#include "gpio_control.h"

/**
 * @struct pwm_driver2_descriptor_t
 * 
 * @brief Driver2 descriptor
 *
 * @var pwm_driver2_descriptor_t::id
 * driver ID - exclusively for reporting purpose
 * @var pwm_driver2_descriptor_t::pwm
 * pwm pin
 * @var pwm_driver2_descriptor_t::direction
 * gpio pin for direction
 * @var pwm_driver2_descriptor_t::enable
 * gpio pin for enables
 */
typedef const struct {
  int        id;
  pwm_pin_t  pwm;
  gpio_pin_t direction;
  gpio_pin_t enable;
} pwm_driver2_descriptor_t;

typedef pwm_driver2_descriptor_t* pwm_driver2_descriptor_ptr;

/**
 * @struct pwm_driver2_t
 * 
 * @brief Driver2 structure
 *
 * @var pwm_driver2_t::pwm
 * pwm controller pointer
 * @var pwm_driver2_t::direction
 * gpio controller pointer
 * @var pwm_driver2_t::enable
 * gpio "enable" pin
 */
typedef struct {
  pwm_t*     pwm;
  gpio_t*    direction;
  gpio_pin_t enable;
} pwm_driver2_t;

/**
 * pwm_driver2_prepare_device
 *
 * @brief Prepares sysfs files for gpio and pwm
 * @param driver: driver descriptor
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver2_prepare_device(pwm_driver2_descriptor_ptr driver_id);

/**
 * pwm_driver2_open
 *
 * @brief creates and initializes driver struct
 *
 * @param driver: driver descriptor
 * @return pointer to the driver struct or NULL if failed
 */
pwm_driver2_t* pwm_driver2_open(pwm_driver2_descriptor_ptr driver_id);

/**
 * pwm_driver2_close
 *
 * @brief Destroys driver struct; sets PWM duty to 0 and enable pin to 0
 *
 * @param pwm_driver2: pointer to the driver
 */
void pwm_driver2_close(pwm_driver2_t* pwm_driver2);

/**
 * pwm_driver2_enable
 *
 * @brief Enables the driver; sets PWM run to 1 and enable pin to 1.
 *
 * @param pwm_driver2: pointer to the driver
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver2_enable(pwm_driver2_t* pwm_driver2);

/**
 * pwm_driver2_disable
 *
 * @brief Disables the driver; sets PWM run to 0 and enable pin to 0.
 *
 * @param pwm_driver2: pointer to the driver
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver2_disable(pwm_driver2_t* pwm_driver2);

/**
 * pwm_driver2_set_period
 *
 * @brief Sets the period value
 *
 * !!! Notice that with ti_ehr_pwm patch changing the period of a
 * !!! driver also changes the period of the other pwm driver sitting
 * !!! on the same chip. For normal functioning be sure to execute the
 * !!! pwm_driver2_set_period for both drivers sharing the same chip.
 *
 * @param pwm_driver2: pointer to the driver
 * @param period:      desired valur of the period
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver2_set_period(pwm_driver2_t* pwm_driver2, long period);

/**
 * pwm_driver2_set_command
 *
 * @brief Sets the command value
 * @param pwm_driver2: pointer to the driver
 * @param command:     the commond between -1 and 1
 * @return -1 on success and 0 otherwise.
 */
int pwm_driver2_set_command(pwm_driver2_t* pwm_driver2, float command);

#endif
