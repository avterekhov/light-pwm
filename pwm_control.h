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

/**
 * pwm_pin_t - PWM pin ID
 *
 * Supported values: PIN_P8_13, PIN_P8_19, PIN_P8_34, PIN_P8_36,
 *                   PIN_P9_14, PIN_P9_16, PIN_P9_21, PIN_P9_22.
 */
typedef enum {PIN_P8_13 = 1, PIN_P8_19, PIN_P8_34, PIN_P8_36, PIN_P9_14, PIN_P9_16, PIN_P9_21, PIN_P9_22} pwm_pin_t;
typedef enum {PWM_RUN = 1, PWM_PERIOD, PWM_DUTY, PWM_POLARITY} pwm_file_t;

/**
 * pwm_t - pwm controller stuct
 *
 * @param duty_file: ID of a sysfs duty file
 * @param period:    current value of the period
 * @param zero:      zero - duty cycle corresponing to zero output of the driver
 * @param pin:       pwm pin
 * @param buffer:    saved for internal usage
 */
typedef struct {
  int        duty_file;
  long       period;
  long       zero;
  pwm_pin_t  pin;
  char       buffer[64];
} pwm_t;

/**
 * pwm_pin_to_string - returns the test_pwm string corresponding to \a
 * pin
 *
 * @param pin: pwm pin
 * @return Returns NULL if fails
 */
const char* pwm_pin_to_string(pwm_pin_t pin);

/**
 * pwm_pin_to_string - returns the bone_pwm driver string
 * corresponding to \a pin
 *
 * @param pin: pwm pin
 * @return Returns NULL if fails
 */
const char* pwm_pin_to_driver_string(pwm_pin_t pin);

/**
 * pwm_file_to_string - returns the string for the pwm file
 *
 * @param file: can be PWM_RUN, PWM_PERIOD, PWM_DUTY, PWM_POLARITY
 */
const char* pwm_file_to_string(pwm_file_t file);

/**
 * pwm_file_name - returns path to the requested pin and file
 *
 * @param pin:    pin id
 * @param file:   can be PWM_RUN, PWM_PERIOD, PWM_DUTY, PWM_POLARITY
 * @param buffer: buffer where the path will be written
 * @return Returns -1 if success, 0 if failure.
 */
int pwm_file_name(pwm_pin_t pin,  pwm_file_t file, char* buffer);

/**
 * pwm_open_file - opens pwm-related sysfs \a file for \a pin
 *
 * @param pin:        pin id
 * @param file:       can be PWM_RUN, PWM_PERIOD, PWM_DUTY, PWM_POLARITY
 * @param attributes: standard open attributes
 * @return Returns file ID if success, 0 if failure.
 */
int pwm_open_file(pwm_pin_t pin,  pwm_file_t file, int attributes);

/**
 * pwm_device_is_ready - checks if all sysfs files are prepared
 *
 * The testing is done by attempting to read sysfs run file
 *
 * @param pin:        pin id
 * @return Returns -1 if ready, 0 otherwise
 */
int pwm_device_is_ready(pwm_pin_t pin);


/**
 * pwm_prepare_device - prepares all sysfs files for pwm control
 *
 * !!! The function does not work properly at the moment. It prepares
 * !!! only some of the devices and causes seg fault.
 *
 * @param pin: pin id
 * @return Returns -1 on success, 0 on failure
 */
int pwm_prepare_device(pwm_pin_t pin);

/**
 * pwm_write_period_file - writes period value to the sysfs period file
 *
 * @param pin:    pin id
 * @param period: period value in ns
 * @return Returns -1 on success, 0 on failure
 */
int pwm_write_period_file(pwm_pin_t pin, long period);

/**
 * pwm_read_period_file - reads period value from the sysfs period file
 *
 * @param pin:    pin id
 * @param period: period value in ns
 * @return Returns -1 on success, 0 on failure
 */
int pwm_read_period_file(pwm_pin_t pin, long* period);

/**
 * pwm_write_run_file - writes period value to the sysfs run file
 *
 * @param pin: pin id
 * @param run: 0 (pwm on) or 1 (pwm off)
 * @return Returns -1 on success, 0 on failure
 */
int pwm_write_run_file(pwm_pin_t pin, int run);

/**
 * pwm_read_run_file - reads run value from the sysfs run file
 *
 * @param pin: pin id
 * @param run: 0 (pwm on) or 1 (pwm off)
 * @return Returns -1 on success, 0 on failure
 */
int pwm_read_run_file(pwm_pin_t pin, int* run);

/**
 * pwm_write_polarity_file - writes polarity value to the sysfs period file
 *
 * @param pin:      pin id
 * @param polarity: 0 (normal polarity) or 1 (inverted polarity)
 * @return Returns -1 on success, 0 on failure
 */
int pwm_write_polarity_file(pwm_pin_t pin, int polarity);

/**
 * pwm_read_polarity_file - reads polarity value from the sysfs period file
 *
 * @param pin:      pin id
 * @param polarity: 0 (normal polarity) or 1 (inverted polarity)
 * @return Returns -1 on success, 0 on failure
 */
int pwm_read_polarity_file(pwm_pin_t pin, int* polarity);

/**
 * pwm_run - sets run status for a pwm controller
 *
 * @param pwm: pointer to pwm controller
 * @param run: run status: 0 (off) or 1 (on)
 * @return Returns -1 on success, 0 on failure
 */
int pwm_run(pwm_t* pwm, int run);

/**
 * pwm_set_duty - sets duty cycle for a pwm controller
 *
 * This function uses previously opened sysfs duty file for better
 * timing.
 *
 * @param pwm:  pointer to pwm controller
 * @param duty: duty value in ns (should be less than period)
 * @return Returns -1 on success, 0 on failure
 */
int pwm_set_duty(pwm_t* pwm, long duty);

/**
 * pwm_set_period - sets period for a pwm controller
 *
 * !!! Notice that with ti_ehr_pwm patch changing the period of a
 * !!! driver also changes the period of the other pwm driver sitting
 * !!! on the same chip. For normal functioning be sure to execute the
 * !!! pwm_get_period for the other driver on the same chip.
 *
 * @param pwm:    pointer to pwm controller
 * @param period: period value in ns
 * @return Returns -1 on success, 0 on failure
 */
int pwm_set_period(pwm_t* pwm, long period);

/**
 * pwm_get_period - returns the period of a pwm controller
 *
 * @param pwm:    pointer to pwm controller
 * @param period: period value in ns
 * @return Returns -1 on success, 0 on failure
 */
int pwm_get_period(pwm_t* pwm, long* period);

/**
 * pwm_open - creates and initializes a pwm controller
 *
 * Initially sets 0 pwm as zero duty cycle. Change pwm->zero to set
 * the zero duty cycle (in ns).
 *
 * @param pin:    PWM pin
 * @param period: initial period value in ns
 * @return Returns a pointer to the controller or NULL if fails.
 */
pwm_t* pwm_open(pwm_pin_t pin, long period);

/**
 * pwm_close - destroys a pwm controller
 *
 * @param pwm: pointer to pwm controller
 */
void pwm_close(pwm_t* pwm);

#endif
