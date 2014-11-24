#ifndef __GPIO_CONTROL_H
#define __GPIO_CONTROL_H

static const char GPIO_DIRECTION_STR[] = "direction";
static const char GPIO_VALUE_STR[] = "value";

static const char GPIO_IN_STR[] = "in";
static const char GPIO_OUT_STR[] = "out";

typedef enum {
  PIN_P8_4  = 39, /* used by MMC by default */
  PIN_P8_7  = 66, /* freely availble */
  PIN_P8_8  = 67, /* freely availble */
  PIN_P8_9  = 69, /* freely availble */
  PIN_P8_10 = 68, /* freely availble */
  PIN_P8_11 = 45, /* freely availble */
  PIN_P8_12 = 44, /* freely availble */
  PIN_P8_14 = 26, /* freely availble */
  PIN_P8_15 = 47, /* freely availble */
  PIN_P8_16 = 46, /* freely availble */
  PIN_P8_17 = 27, /* freely availble */
  PIN_P8_18 = 65, /* freely availble */
  PIN_P8_26 = 61, /* freely availble */
  PIN_P8_30 = 89, /* used by LCD by default */
  PIN_P8_46 = 71, /* used by LCD by default */

  PIN_P9_12 = 60, /* freely availble */
  PIN_P9_15 = 48, /* freely availble */
  PIN_P9_23 = 49, /* freely availble */
  PIN_P9_25 = 117,/* freely availble */
  PIN_P9_27 = 115,/* freely availble */
  PIN_P9_30 = 122,/* freely availble */
  PIN_P9_41 = 20  /* freely availble */
} gpio_pin_t;

typedef enum {GPIO_DIRECTION = 1, GPIO_VALUE} gpio_file_t;
typedef enum {GPIO_IN = 0, GPIO_OUT = 1} gpio_direction_t;

typedef struct {
  int               value_file;
  gpio_direction_t  direction;
  gpio_pin_t        pin;
  char              buffer[64];
} gpio_t;

const char* gpio_file_to_string(gpio_file_t pin);

int gpio_device_is_ready(gpio_pin_t pin);
int gpio_prepare_device(gpio_pin_t pin);
int gpio_open_file(gpio_pin_t pin,  gpio_file_t file, int attributes);
int gpio_write_direction_file(gpio_pin_t pin, gpio_direction_t direction);
int gpio_read_direction_file(gpio_pin_t pin, gpio_direction_t* direction);
int gpio_write_value_file(gpio_pin_t pin, int value);
int gpio_read_value_file(gpio_pin_t pin, int* value);
int gpio_set_value(gpio_t* gpio, int value);
int gpio_get_value(gpio_t* gpio, int* value);
gpio_t* gpio_open(gpio_pin_t pin, gpio_direction_t direction);
void gpio_close(gpio_t* gpio);
  
#endif
