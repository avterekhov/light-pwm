#include <stdio.h>
#include <unistd.h>
#include "pwm_driver.h"
#include "pwm_control.h"
#include "gpio_control.h"

int main(void) {
  /* pwm_t* pwm; */
  /* pwm = pwm_open(PIN_P9_22, 50000); */
  /* if (pwm == NULL) { */
  /*   printf("Cannot open PWM\n"); */
  /*   return 0; */
  /* } */
  /* printf("PWM opened\n"); */
  /* pwm_set_duty(pwm, 77); */
  /* sleep(10); */
  /* pwm_close(pwm); */
  /* printf("PWM closed\n"); */
  /* gpio_t* gpio; */
  /* gpio = gpio_open(PIN_P8_46, GPIO_OUT); */
  /* if (gpio == NULL) { */
  /*   printf("Cannot open GPIO\n"); */
  /*   return 0; */
  /* } */
  /* gpio_set_value(gpio, 1); */
  /* sleep(10); */
  /* gpio_close(gpio); */
  pwm_driver_t* pwm_driver = pwm_driver_open(PWM_DRIVER6);
  if (NULL == pwm_driver) {
    printf("Cannot open driver1");
    return 0;
  }
  pwm_driver_enable(pwm_driver);
  pwm_driver_set_command(pwm_driver, .5);
  sleep(10);
  pwm_driver_close(pwm_driver);
  return 0;
}
