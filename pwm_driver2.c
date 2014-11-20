#include <stdio.h>
#include <malloc.h>
#include "pwm_driver2.h"

int pwm_driver2_prepare_device(pwm_driver2_descriptor_ptr driver) {
  return pwm_prepare_device(driver->pwm) &	\
    gpio_prepare_device(driver->enable) &	\
    gpio_prepare_device(driver->direction);
}

pwm_driver2_t* pwm_driver2_open(pwm_driver2_descriptor_ptr driver) {
  if (!pwm_driver2_prepare_device(driver)) {
    printf("Cannot prepare driver %d\n", driver->id);
    return NULL;
  }
  pwm_driver2_t* pwm_driver2 = malloc(sizeof(pwm_driver2_t));
  pwm_driver2->pwm = pwm_open(driver->pwm, 50000);
  if (!pwm_driver2->pwm) {
    free(pwm_driver2);
    return NULL;
  }
  pwm_driver2->direction = gpio_open(driver->direction, GPIO_OUT);
  if (!pwm_driver2->direction) {
    pwm_close(pwm_driver2->pwm);
    free(pwm_driver2);
    return NULL;
  }
  pwm_driver2->enable = driver->enable;
  if (!gpio_write_direction_file(pwm_driver2->enable, GPIO_OUT)) {
    pwm_close(pwm_driver2->pwm);
    gpio_close(pwm_driver2->direction);
    free(pwm_driver2);
    return NULL;
  }
  pwm_driver2->pwm->zero = 0;
  pwm_set_duty(pwm_driver2->pwm, pwm_driver2->pwm->zero);
  gpio_write_value_file(pwm_driver2->enable, 0);
  return pwm_driver2;
}

void pwm_driver2_close(pwm_driver2_t* pwm_driver2) {
  if (pwm_driver2 == NULL)
    return;
  gpio_write_value_file(pwm_driver2->enable, 0);
  gpio_close(pwm_driver2->direction);
  pwm_close(pwm_driver2->pwm);
  free(pwm_driver2);
}

int pwm_driver2_enable(pwm_driver2_t* pwm_driver2) {
  if (!pwm_write_run_file(pwm_driver2->pwm->pin, 1))
    return 0;
  if (!gpio_write_value_file(pwm_driver2->enable, 1)) {
    pwm_write_run_file(pwm_driver2->pwm->pin, 0);
    return 0;
  }
  return -1;
}

int pwm_driver2_disable(pwm_driver2_t* pwm_driver2) {
  if ( pwm_write_run_file(pwm_driver2->pwm->pin, 0) && gpio_write_value_file(pwm_driver2->enable, 0) )
    return -1;
  else
    return 0;
}

int pwm_driver2_set_period(pwm_driver2_t* pwm_driver2, long period) {
  int status = pwm_write_period_file(pwm_driver2->pwm->pin, period);
  if (status)
    pwm_driver2->pwm->zero = .5*pwm_driver2->pwm->period;
  return status;
}

int pwm_driver2_set_command(pwm_driver2_t* pwm_driver2, float command) {
  long duty;
  if (command >= 0) {
    gpio_set_value(pwm_driver2->direction, 0);
    duty =  command * pwm_driver2->pwm->period;
  }
  else {
    gpio_set_value(pwm_driver2->direction, 1);
    duty = -command * pwm_driver2->pwm->period;
  }
  duty = duty < pwm_driver2->pwm->period ? duty : pwm_driver2->pwm->period;
  return pwm_set_duty(pwm_driver2->pwm, duty);
}
