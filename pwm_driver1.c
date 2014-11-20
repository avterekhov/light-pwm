#include <stdio.h>
#include <malloc.h>
#include "pwm_driver1.h"

int pwm_driver1_prepare_device(pwm_driver1_descriptor_ptr driver) {
  return pwm_prepare_device(driver->pwm) &	\
    gpio_prepare_device(driver->gpio);
}

pwm_driver1_t* pwm_driver1_open(pwm_driver1_descriptor_ptr driver) {
  if (!pwm_driver1_prepare_device(driver)) {
    printf("Cannot prepare driver %d\n", driver->id);
    return NULL;
  }
  pwm_driver1_t* pwm_driver1 = malloc(sizeof(pwm_driver1_t));
  pwm_driver1->pwm = pwm_open(driver->pwm, 50000);
  if (!pwm_driver1->pwm) {
    free(pwm_driver1);
    return NULL;
  }
  pwm_driver1->gpio_pin = driver->gpio;
  if (!gpio_write_direction_file(pwm_driver1->gpio_pin, GPIO_OUT)) {
    pwm_close(pwm_driver1->pwm);
    free(pwm_driver1);
    return NULL;
  }
  pwm_driver1->pwm->zero = .5*pwm_driver1->pwm->period;
  pwm_set_duty(pwm_driver1->pwm, pwm_driver1->pwm->zero);
  gpio_write_value_file(pwm_driver1->gpio_pin, 0);
  return pwm_driver1;
}

void pwm_driver1_close(pwm_driver1_t* pwm_driver1) {
  if (pwm_driver1 == NULL)
    return;
  gpio_write_value_file(pwm_driver1->gpio_pin, 0);
  pwm_close(pwm_driver1->pwm);
  free(pwm_driver1);
}

int pwm_driver1_enable(pwm_driver1_t* pwm_driver1) {
  if (!pwm_write_run_file(pwm_driver1->pwm->pin, 1))
    return 0;
  if (!gpio_write_value_file(pwm_driver1->gpio_pin, 1)) {
    pwm_write_run_file(pwm_driver1->pwm->pin, 0);
    return 0;
  }
  return -1;
}

int pwm_driver1_disable(pwm_driver1_t* pwm_driver1) {
  if ( pwm_write_run_file(pwm_driver1->pwm->pin, 0) && gpio_write_value_file(pwm_driver1->gpio_pin, 0) )
    return -1;
  else
    return 0;
}

int pwm_driver1_set_period(pwm_driver1_t* pwm_driver1, long period) {
  int status = pwm_write_period_file(pwm_driver1->pwm->pin, period);
  if (status)
    pwm_driver1->pwm->zero = .5*pwm_driver1->pwm->period;
  return status;
}

int pwm_driver1_set_command(pwm_driver1_t* pwm_driver1, float command) {
  long duty = pwm_driver1->pwm->zero + .5 * command * pwm_driver1->pwm->period;
  duty = duty > 0 ? duty : 0;
  duty = duty < pwm_driver1->pwm->period ? duty : pwm_driver1->pwm->period;
  return pwm_set_duty(pwm_driver1->pwm, duty);
}
