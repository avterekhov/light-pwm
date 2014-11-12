#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include "pwm_control.h"

const char* pwm_pin_to_string(pwm_pin_t pin) {
  switch (pin) {
  case PIN_P8_13: return &PIN_P8_13_STR;
  case PIN_P8_19: return &PIN_P8_19_STR;
  case PIN_P8_34: return &PIN_P8_34_STR;
  case PIN_P8_36: return &PIN_P8_36_STR;
  case PIN_P9_14: return &PIN_P9_14_STR;
  case PIN_P9_16: return &PIN_P9_16_STR;
  case PIN_P9_21: return &PIN_P9_21_STR;
  case PIN_P9_22: return &PIN_P9_22_STR;
  default: return NULL;
  }
}

const char* pwm_pin_to_driver_string(pwm_pin_t pin) {
  switch (pin) {
  case PIN_P8_13: return &PIN_P8_13_DRIVER_STR;
  case PIN_P8_19: return &PIN_P8_19_DRIVER_STR;
  case PIN_P8_34: return &PIN_P8_34_DRIVER_STR;
  case PIN_P8_36: return &PIN_P8_36_DRIVER_STR;
  case PIN_P9_14: return &PIN_P9_14_DRIVER_STR;
  case PIN_P9_16: return &PIN_P9_16_DRIVER_STR;
  case PIN_P9_21: return &PIN_P9_21_DRIVER_STR;
  case PIN_P9_22: return &PIN_P9_22_DRIVER_STR;
  default: return NULL;
  }
}

const char* pwm_file_to_string(pwm_file_t file) {
  switch (file) {
  case PWM_RUN:       return &PWM_RUN_STR;
  case PWM_PERIOD:    return &PWM_PERIOD_STR;
  case PWM_DUTY:      return &PWM_DUTY_STR;
  case PWM_POLARITY:  return &PWM_POLARITY_STR;
  default: return NULL;
  }
}

int pwm_file_name(pwm_pin_t pin,  pwm_file_t file, char* buffer) {
  char str[1024];
  sprintf(str, "/sys/devices/ocp.*/%s.*/%s", pwm_pin_to_string(pin), pwm_file_to_string(file));
  if (!glob_path(str, buffer)) {
    printf("Cannot resolve the path: %s\n", str);
    return 0;
  }
  return -1;
}

int pwm_open_file(pwm_pin_t pin,  pwm_file_t file, int attributes) {
  char str[1024];
  if (!pwm_file_name(pin, file, str)) {
    printf("Cannot open %s file for pin %s\n", pwm_file_to_string(file), pwm_pin_to_string(pin));
    return 0;
  }
  /*printf("Opening %s\n", str);*/
  return open(str, attributes);
}

int pwm_device_is_ready(pwm_pin_t pin) {
  int foo;
  return pwm_read_run_file(pin, &foo);
}

int pwm_prepare_device(pwm_pin_t pin) {
  char str[1024];
  int nbytes;
  int file_id;
  int status;
  if (pwm_device_is_ready(pin))
    return -1;
  if (!glob_path("/sys/devices/bone_capemgr.*/slots", str)) {
    printf("Cannot resolve path: /sys/devices/bone_capemgr.*/slots\n");
    return 0;
  }
  file_id = open(str, O_WRONLY | O_SYNC);
  if (file_id < 0) {
    printf("Cannot open file %s for writing\n", str);
    return 0;
  }
  nbytes = sprintf(str, "%s", pwm_pin_to_driver_string(pin));
  if (nbytes != write(file_id, str, nbytes)) {
    if (sizeof(PWM_DRIVER_STR) != write(file_id, PWM_DRIVER_STR, sizeof(PWM_DRIVER_STR))) {
      printf("Cannot install driver: %s\n", PWM_DRIVER_STR);
      close(file_id);
      return 0;
    }
    sleep(1);
    if (nbytes != write(file_id, str, nbytes)) {
      printf("Cannot install driver: %s\n", str);
      close(file_id);
      return 0;
    }
  }
  close(file_id);
  sleep(1);
  return -1;
}

int pwm_write_period_file(pwm_pin_t pin, long period) {
  char str[16];
  int pwm_period_file = pwm_open_file(pin, PWM_PERIOD, O_WRONLY | O_SYNC);
  if (!pwm_period_file)
    return 0;
  int nbytes = sprintf(str, "%ld", period);
  if ( nbytes != write(pwm_period_file, str, nbytes) ) {
    printf("Cannot write run file for %s\n", pwm_pin_to_string(pin));
    return 0;
  }
  close(pwm_period_file);
  return -1;
}  

int pwm_read_period_file(pwm_pin_t pin, long* period) {
  char str[16];
  int pwm_period_file = pwm_open_file(pin, PWM_PERIOD, O_RDONLY | O_SYNC);
  if (!pwm_period_file)
    return 0;
  int nbytes = read(pwm_period_file, str, sizeof(str));
  close(pwm_period_file);
  sscanf(str, "%ld", period);
  return -1;
}  

int pwm_write_run_file(pwm_pin_t pin, int run) {
  char str[16];
  int pwm_run_file = pwm_open_file(pin, PWM_RUN, O_WRONLY | O_SYNC);
  if (!pwm_run_file)
    return 0;
  if ( 1 != write(pwm_run_file, (!run)?"0":"1", 1) ) {
    printf("Cannot write run file for %s\n", pwm_pin_to_string(pin));
    return 0;
  }
  close(pwm_run_file);
  return -1;
}

int pwm_read_run_file(pwm_pin_t pin, int* run) {
  char str[16];
  int pwm_run_file = pwm_open_file(pin, PWM_RUN, O_RDONLY | O_SYNC);
  if (!pwm_run_file)
    return 0;
  int nbytes = read(pwm_run_file, str, sizeof(str));
  close(pwm_run_file);
  sscanf(str, "%d", run);
  return -1;
}  

int pwm_write_polarity_file(pwm_pin_t pin, int polarity) {
  char str[16];
  int pwm_polarity_file = pwm_open_file(pin, PWM_POLARITY, O_WRONLY | O_SYNC);
  if (!pwm_polarity_file)
    return 0;
  if ( 1 != write(pwm_polarity_file, (!polarity)?"0":"1", 1) ) {
    printf("Cannot write polarity file for %s\n", pwm_pin_to_string(pin));
    return 0;
  }
  close(pwm_polarity_file);
  return -1;
}

int pwm_read_polarity_file(pwm_pin_t pin, int* polarity) {
  char str[16];
  int pwm_polarity_file = pwm_open_file(pin, PWM_POLARITY, O_RDONLY | O_SYNC);
  if (!pwm_polarity_file)
    return 0;
  int nbytes = read(pwm_polarity_file, str, sizeof(str));
  close(pwm_polarity_file);
  sscanf(str, "%d", polarity);
  return -1;
}  

int pwm_run(pwm_t* pwm, int run) {
  return pwm_write_run_file(pwm->pin, !!run);
}

int pwm_set_duty(pwm_t* pwm, long duty) {
  char str[16];
  int nbytes = sprintf(str, "%ld", duty);
  if ( nbytes != write(pwm->duty_file, str, nbytes) ) {
    printf("Cannot write \"%d\" to the duty file for %s\n", duty, pwm_pin_to_string(pwm->pin));
    return 0;
  }
  return -1;
}

int pwm_set_period(pwm_t* pwm, long period) {
  int status = pwm_write_period_file(pwm->pin, period);
  if (status)
    pwm->period = period;
  return status;
}

int pwm_get_period(pwm_t* pwm, long* period) {
  int status = pwm_read_period_file(pwm->pin, period);
  if (status)
    pwm->period = *period;
  return status;
}

pwm_t* pwm_open(pwm_pin_t pin, long period)
{
  char str[1024];
  pwm_t* pwm = malloc(sizeof(pwm_t));
  pwm->zero = 0;
  pwm->period = period;
  pwm->pin = pin;

  if (!pwm_prepare_device(pin) ||	    \
      !pwm_write_period_file(pin, pwm->period) ||	\
      !pwm_write_polarity_file(pin, 0) ) {
    free(pwm);
    return NULL;
  }
  
  int pwm_duty_file = pwm_open_file(pin, PWM_DUTY, O_WRONLY | O_SYNC);
  if (pwm_duty_file < 0) {
    printf("Cannot open %s file for pin %s\n", pwm_file_to_string(PWM_DUTY), pwm_pin_to_string(pin));
    free(pwm);
    return NULL;
  }
  pwm->duty_file = pwm_duty_file;

  return pwm;
}

void pwm_close(pwm_t* pwm)
{
  if (pwm == NULL)
    return;
  int nbytes = sprintf(pwm->buffer, "%ld", pwm->zero);
  write(pwm->duty_file, pwm->buffer, nbytes);
  close(pwm->duty_file);
  free(pwm);
}
