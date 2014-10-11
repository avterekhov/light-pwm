#ifndef __PWM_CONTROL_H
#define __PWM_CONTROL_H

static const char PIN_P8_13_STR[] = "pwm_test_P8_13";
static const char PIN_P8_19_STR[] = "pwm_test_P8_19";
static const char PIN_P8_34_STR[] = "pwm_test_P8_34";
static const char PIN_P8_36_STR[] = "pwm_test_P8_36";
static const char PIN_P9_14_STR[] = "pwm_test_P9_14";
static const char PIN_P9_16_STR[] = "pwm_test_P9_16";
static const char PIN_P9_21_STR[] = "pwm_test_P9_21";
static const char PIN_P9_22_STR[] = "pwm_test_P9_22";

static const char PWM_DRIVER_STR[] = "am33xx_pwm";

static const char PIN_P8_13_DRIVER_STR[] = "bone_pwm_P8_13";
static const char PIN_P8_19_DRIVER_STR[] = "bone_pwm_P8_19";
static const char PIN_P8_34_DRIVER_STR[] = "bone_pwm_P8_34";
static const char PIN_P8_36_DRIVER_STR[] = "bone_pwm_P8_36";
static const char PIN_P9_14_DRIVER_STR[] = "bone_pwm_P9_14";
static const char PIN_P9_16_DRIVER_STR[] = "bone_pwm_P9_16";
static const char PIN_P9_21_DRIVER_STR[] = "bone_pwm_P9_21";
static const char PIN_P9_22_DRIVER_STR[] = "bone_pwm_P9_22";

static const char PWM_RUN_STR[] = "run";
static const char PWM_PERIOD_STR[] = "period";
static const char PWM_DUTY_STR[] = "duty";
static const char PWM_POLARITY_STR[] = "polarity";

typedef enum {PIN_P8_13 = 1, PIN_P8_19, PIN_P8_34, PIN_P8_36, PIN_P9_14, PIN_P9_16, PIN_P9_21, PIN_P9_22} pwm_pin_t;
typedef enum {PWM_RUN = 1, PWM_PERIOD, PWM_DUTY, PWM_POLARITY} pwm_file_t;

typedef struct {
  int        duty_file;
  long       period;
  long       zero;
  pwm_pin_t  pin;
  char       buffer[64];
} pwm_t;

const char* pwm_pin_to_string(pwm_pin_t pin);
const char* pwm_pin_to_driver_string(pwm_pin_t pin);
const char* pwm_file_to_string(pwm_file_t file);

int pwm_file_name(pwm_pin_t pin,  pwm_file_t file, char* buffer);
int pwm_open_file(pwm_pin_t pin,  pwm_file_t file, int attributes);
int pwm_device_is_ready(pwm_pin_t pin);
int pwm_prepare_device(pwm_pin_t pin);
int pwm_write_period_file(pwm_pin_t pin, long period);
int pwm_read_period_file(pwm_pin_t pin, long* period);
int pwm_write_run_file(pwm_pin_t pin, int run);
int pwm_read_run_file(pwm_pin_t pin, int* run);
int pwm_write_polarity_file(pwm_pin_t pin, int polarity);
int pwm_read_polarity_file(pwm_pin_t pin, int* polarity);
int pwm_run(pwm_t* pwm, int run);
int pwm_set_duty(pwm_t* pwm, long duty);
pwm_t* pwm_open(pwm_pin_t pin, long period);
void pwm_close(pwm_t* pwm);

#endif
