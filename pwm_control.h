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
 * pwm_pin_t
 * @brief PWM pin ID
 * Supported values: PIN_P8_13, PIN_P8_19, PIN_P8_34, PIN_P8_36,
 *                   PIN_P9_14, PIN_P9_16, PIN_P9_21, PIN_P9_22.
 */
typedef enum {PIN_P8_13 = 1, PIN_P8_19, PIN_P8_34, PIN_P8_36, PIN_P9_14, PIN_P9_16, PIN_P9_21, PIN_P9_22} pwm_pin_t;
typedef enum {PWM_RUN = 1, PWM_PERIOD, PWM_DUTY, PWM_POLARITY} pwm_file_t;

/**
 * @strcut pwm_t
 *
 * @brief pwm controller stuct
 *
 * @var pwm_t::duty_file
 * ID of a sysfs duty file
 * @var pwm_t::period
 * current value of the period
 * @var pwm_t::zero
 * zero - duty cycle corresponing to zero output of the driver
 * @var pwm_t::pin
 * pwm pin
 * @var pwm_t::buffer
 * saved for internal usage
 */
typedef struct {
  int        duty_file;
  long       period;
  long       zero;
  pwm_pin_t  pin;
  char       buffer[64];
} pwm_t;

/**
 * pwm_pin_to_string
 *
 * @brief Returns the test_pwm string corresponding to \a pin
 *
 * @param pin: pwm pin
 * @return pointer to the string; NULL if fails
 */
const char* pwm_pin_to_string(pwm_pin_t pin);

/**
 * pwm_pin_to_string
 *
 * @brief Returns the bone_pwm driver string corresponding to \a pin
 * @param pin: pwm pin
 * @return pointer to the string; NULL if fails.
 */
const char* pwm_pin_to_driver_string(pwm_pin_t pin);

/**
 * pwm_file_to_string
 * 
 * @brief Returns string for the pwm file type
 * @param file: can be PWM_RUN, PWM_PERIOD, PWM_DUTY, PWM_POLARITY
 * @return pointer to the string; NULL if fails
 */
const char* pwm_file_to_string(pwm_file_t file);

/**
 * pwm_file_name
 *
 * @brief Returns filename (including path) for the requested pin and file type
 * @param pin:    pin id
 * @param file:   can be PWM_RUN, PWM_PERIOD, PWM_DUTY, PWM_POLARITY
 * @param buffer: buffer where the path will be written
 * @return -1 if success, 0 if failure.
 */
int pwm_file_name(pwm_pin_t pin,  pwm_file_t file, char* buffer);

/**
 * pwm_open_file
 *
 * @brief opens pwm-related sysfs for for filetype \a file and pin \a pin
 * @param pin:        pin id
 * @param file:       can be PWM_RUN, PWM_PERIOD, PWM_DUTY, PWM_POLARITY
 * @param attributes: standard open attributes
 * @return file ID (to be used with open) if success, 0 if failure.
 */
int pwm_open_file(pwm_pin_t pin,  pwm_file_t file, int attributes);

/**
 * pwm_device_is_ready
 *
 * @brief Checks if all sysfs files are prepared. The testing is done by attempting to read sysfs run file.
 * @param pin:        pin id
 * @return -1 if ready, 0 otherwise
 */
int pwm_device_is_ready(pwm_pin_t pin);


/**
 * pwm_prepare_device
 *
 * @brief prepares all sysfs files for pwm control
 *
 * !!! The function does not work properly at the moment. It prepares
 * !!! only some of the devices and causes seg fault.
 *
 * @param pin: pin id
 * @return -1 on success, 0 on failure
 */
int pwm_prepare_device(pwm_pin_t pin);

/**
 * pwm_write_period_file
 *
 * @brief writes period value to the sysfs period file
 * @param pin:    pin id
 * @param period: period value in ns
 * @return -1 on success, 0 on failure
 */
int pwm_write_period_file(pwm_pin_t pin, long period);

/**
 * pwm_read_period_file
 *
 * @brief reads period value from the sysfs period file
 * @param pin:    pin id
 * @param period: period value in ns
 * @return Returns -1 on success, 0 on failure
 */
int pwm_read_period_file(pwm_pin_t pin, long* period);

/**
 * pwm_write_run_file
 *
 * @brief writes period value to the sysfs run file
 * @param pin: pin id
 * @param run: 0 (pwm on) or 1 (pwm off)
 * @return -1 on success, 0 on failure
 */
int pwm_write_run_file(pwm_pin_t pin, int run);

/**
 * pwm_read_run_file
 *
 * @brief reads run value from the sysfs run file
 * @param pin: pin id
 * @param run: 0 (pwm on) or 1 (pwm off)
 * @return -1 on success, 0 on failure
 */
int pwm_read_run_file(pwm_pin_t pin, int* run);

/**
 * pwm_write_polarity_file 
 *
 * @brief writes polarity value to the sysfs period file
 * @param pin:      pin id
 * @param polarity: 0 (normal polarity) or 1 (inverted polarity)
 * @return -1 on success, 0 on failure
 */
int pwm_write_polarity_file(pwm_pin_t pin, int polarity);

/**
 * pwm_read_polarity_file
 *
 * @brief reads polarity value from the sysfs period file
 * @param pin:      pin id
 * @param polarity: 0 (normal polarity) or 1 (inverted polarity)
 * @return Returns -1 on success, 0 on failure
 */
int pwm_read_polarity_file(pwm_pin_t pin, int* polarity);

/**
 * pwm_run
 *
 * @brief sets run status for a pwm controller: writes 1 to run file
 * @param pwm: pointer to pwm controller
 * @param run: run status: 0 (off) or 1 (on)
 * @return -1 on success, 0 on failure
 */
int pwm_run(pwm_t* pwm, int run);

/**
 * pwm_set_duty
 *
 * @brief Sets duty cycle for a pwm controller. This function uses
 * previously opened sysfs duty file for better timing.
 *
 * @param pwm:  pointer to pwm controller
 * @param duty: duty value in ns (should be less than period)
 * @return -1 on success, 0 on failure
 */
int pwm_set_duty(pwm_t* pwm, long duty);

/**
 * pwm_set_period
 *
 * @brief sets period for a pwm controller
 *
 * !!! Notice that with ti_ehr_pwm patch changing the period of a
 * !!! driver also changes the period of the other pwm driver sitting
 * !!! on the same chip. For normal functioning be sure to execute the
 * !!! pwm_get_period for the other driver on the same chip.
 *
 * @param pwm:    pointer to pwm controller
 * @param period: period value in ns
 * @return -1 on success, 0 on failure
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
 * pwm_open
 *
 * @brief Creates and initializes a pwm controller. Initially sets 0 pwm as zero duty cycle. Change pwm->zero to set
 * the zero duty cycle (in ns).
 *
 * @param pin:    PWM pin
 * @param period: initial period value in ns
 * @return Returns a pointer to the controller or NULL if fails.
 */
pwm_t* pwm_open(pwm_pin_t pin, long period);

/**
 * pwm_close
 *
 * @brief destroys a pwm controller
 * @param pwm: pointer to pwm controller
 */
void pwm_close(pwm_t* pwm);

#endif
