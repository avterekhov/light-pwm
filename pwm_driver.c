#include <stdio.h>
#include <malloc.h>
#include "pwm_driver.h"

int pwm_driver_prepare_device(pwm_driver_descriptor_ptr driver) {
  return pwm_prepare_device(driver->pwm) &	\
    gpio_prepare_device(driver->gpio);
}

pwm_driver_t* pwm_driver_open(pwm_driver_descriptor_ptr driver) {
  if (!pwm_driver_prepare_device(driver)) {
    printf("Cannot prepare driver %s\n", driver->id);
    return NULL;
  }
  pwm_driver_t* pwm_driver = malloc(sizeof(pwm_driver_t));
  pwm_driver->pwm = pwm_open(driver->pwm, 50000);
  if (!pwm_driver->pwm) {
    free(pwm_driver);
    return NULL;
  }
  pwm_driver->gpio_pin = driver->gpio;
  if (!gpio_write_direction_file(pwm_driver->gpio_pin, GPIO_OUT)) {
    pwm_close(pwm_driver->pwm);
    free(pwm_driver);
    return NULL;
  }
  pwm_driver->pwm->zero = .5*pwm_driver->pwm->period;
  pwm_set_duty(pwm_driver->pwm, pwm_driver->pwm->zero);
  gpio_write_value_file(pwm_driver->gpio_pin, 0);
  return pwm_driver;
}

void pwm_driver_close(pwm_driver_t* pwm_driver) {
  if (pwm_driver == NULL)
    return;
  gpio_write_value_file(pwm_driver->gpio_pin, 0);
  gpio_write_direction_file(pwm_driver->gpio_pin, GPIO_IN);
  pwm_close(pwm_driver->pwm);
  free(pwm_driver);
}

int pwm_driver_enable(pwm_driver_t* pwm_driver) {
  if (!pwm_write_run_file(pwm_driver->pwm->pin, 1))
    return 0;
  if (!gpio_write_value_file(pwm_driver->gpio_pin, 1)) {
    pwm_write_run_file(pwm_driver->pwm->pin, 0);
    return 0;
  }
  return -1;
}

int pwm_driver_disable(pwm_driver_t* pwm_driver) {
  if ( pwm_write_run_file(pwm_driver->pwm->pin, 0) && gpio_write_value_file(pwm_driver->gpio_pin, 1) )
    return -1;
  else
    return 0;
}

int pwm_driver_set_period(pwm_driver_t* pwm_driver, long period) {
  int status = pwm_write_period_file(pwm_driver->pwm->pin, period);
  if (status)
    pwm_driver->pwm->zero = .5*pwm_driver->pwm->period;
  return status;
}

int pwm_driver_set_command(pwm_driver_t* pwm_driver, float command) {
  long duty = pwm_driver->pwm->zero + .5 * command * pwm_driver->pwm->period;
  duty = duty > 0 ? duty : 0;
  duty = duty < pwm_driver->pwm->period ? duty : pwm_driver->pwm->period;
  return pwm_set_duty(pwm_driver->pwm, duty);
}
