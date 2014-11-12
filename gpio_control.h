#ifndef __GPIO_CONTROL_H
#define __GPIO_CONTROL_H

static const char GPIO_DIRECTION_STR[] = "direction";
static const char GPIO_VALUE_STR[] = "value";

static const char GPIO_IN_STR[] = "in";
static const char GPIO_OUT_STR[] = "out";

typedef enum {			\
  PIN_P8_4  = 39,		\
  PIN_P8_8  = 67,		\
  PIN_P8_30 = 89,		\
  PIN_P8_46 = 71,		\
				\
  PIN_P9_12 = 60,		\
  PIN_P9_42 =  7,		\
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
