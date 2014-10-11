#include <fcntl.h>
#include <malloc.h>
#include "gpio_control.h"

const char* gpio_file_to_string(gpio_file_t pin) {
  switch (pin) {
  case GPIO_DIRECTION: return &GPIO_DIRECTION_STR;
  case GPIO_VALUE: return &GPIO_VALUE_STR;
  default: return NULL;
  }
}

int gpio_open_file(gpio_pin_t pin,  gpio_file_t file, int attributes) {
  char str[1024];
  int file_id;
  sprintf(str, "/sys/class/gpio/gpio%d/%s", pin, gpio_file_to_string(file));
  file_id = open(str, attributes);
  if (file_id < 0) {
    printf("Cannot open %s file for gpio%d\n", gpio_file_to_string(file), pin);
  }
  return file_id;
}

int gpio_device_is_ready(gpio_pin_t pin) {
  gpio_direction_t foo;
  return gpio_read_direction_file(pin, &foo);
}

int gpio_prepare_device(gpio_pin_t pin) {
  char str[1024];
  int nbytes;
  int file_id;
  int status;
  if (gpio_device_is_ready(pin))
    return -1;
  file_id = open("/sys/class/gpio/export", O_WRONLY | O_SYNC);
  if (file_id < 0) {
    printf("Cannot open /sys/class/gpio/export for writing\n");
  }
  nbytes = sprintf(str, "%d", pin);
  if (nbytes != write(file_id, str, nbytes)) {
    printf("Cannot export gpio%s\n", str);
    status = 0;
  }
  else {
    sleep(1);
    status = -1;
  }
  close(file_id);
  return status;
}

int gpio_write_direction_file(gpio_pin_t pin, gpio_direction_t direction) {
  char str[16];
  int status;
  int gpio_direction_file = gpio_open_file(pin, GPIO_DIRECTION, O_WRONLY | O_SYNC);
  if (!gpio_direction_file)
    return 0;
  switch(direction) {
  case GPIO_IN:
    status = (sizeof(GPIO_IN_STR) == write(gpio_direction_file, GPIO_IN_STR, sizeof(GPIO_IN_STR)));
    break;
  case GPIO_OUT:
    status = (sizeof(GPIO_OUT_STR) == write(gpio_direction_file, GPIO_OUT_STR, sizeof(GPIO_OUT_STR)));
    break;
  default:
    printf("Unrecognized direction value: %d\n", direction);
  }

  if ( !status ) {
    printf("Cannot write direction file for gpio%d\n", pin);
    return 0;
  }
  close(gpio_direction_file);
  return -1;
}

int gpio_read_direction_file(gpio_pin_t pin, gpio_direction_t* direction) {
  char str[16];
  int status;
  int nbytes;
  int gpio_direction_file = gpio_open_file(pin, GPIO_DIRECTION, O_RDONLY | O_SYNC);
  if (!gpio_direction_file)
    return 0;
  nbytes = read(gpio_direction_file, str, sizeof(str));
  str[nbytes-1] = '\0';
  if (!strcmp(str, GPIO_IN_STR)) {
    *direction = GPIO_IN;
    close(gpio_direction_file);
    return -1;
  }
  if (!strcmp(str, GPIO_OUT_STR)) {
    *direction = GPIO_OUT;
    close(gpio_direction_file);
    return -1;
  }
  printf("Unrecognized direction for gpio%d: %s\n", pin, str);
  close(gpio_direction_file);
  return 0;
}

int gpio_write_value_file(gpio_pin_t pin, int value) {
  char str[16];
  int gpio_value_file = gpio_open_file(pin, GPIO_VALUE, O_WRONLY | O_SYNC);
  if (!gpio_value_file)
    return 0;
  if ( 1 != write(gpio_value_file, (!value)?"0":"1", 1) ) {
    printf("Cannot write value file for %d\n", pin);
    return 0;
  }
  close(gpio_value_file);
  return -1;
}

int gpio_read_value_file(gpio_pin_t pin, int* value) {
  char str[16];
  int gpio_value_file = gpio_open_file(pin, GPIO_VALUE, O_RDONLY | O_SYNC);
  if (!gpio_value_file)
    return 0;
  int nbytes = read(gpio_value_file, str, sizeof(str));
  str[nbytes-1] = '\0';
  close(gpio_value_file);
  sscanf(str, "%d", value);
  return -1;
}  

int gpio_set_value(gpio_t* gpio, int value) {
  if ( (gpio->direction != GPIO_OUT) || (1 != write(gpio->value_file, !value?"0":"1", 1)) ) {
    printf("Cannot write \"%d\" to the value file for gpio%d\n", value, gpio->pin);
    return 0;
  }
  return -1;
}

int gpio_get_value(gpio_t* gpio, int* value) {
  if ( 1 != read(gpio->value_file, gpio->buffer, sizeof(gpio->buffer)) ) {
    printf("Error reading the value file for gpio%d\n", gpio->pin);
    return 0;
  }
  gpio->buffer[1] = '\0';
  sscanf(gpio->buffer, "%d", value);
  return -1;
}

gpio_t* gpio_open(gpio_pin_t pin, gpio_direction_t direction) {
  char str[1024];
  gpio_t* gpio = malloc(sizeof(gpio_t));
  gpio->direction = direction;
  gpio->pin = pin;

  if (!gpio_prepare_device(pin) ||					\
      !gpio_write_direction_file(pin, direction) ||			\
      ( (direction == GPIO_IN) && (!gpio_write_value_file(pin, 0)) )) {
    free(gpio);
    return NULL;
  }

  /* Prepare value file */
  int gpio_value_file;
  switch(direction) {
  case GPIO_IN:
    gpio_value_file = gpio_open_file(pin, GPIO_VALUE, O_RDONLY | O_SYNC);
  case GPIO_OUT:
    gpio_value_file = gpio_open_file(pin, GPIO_VALUE, O_WRONLY | O_SYNC);
  }
  if (gpio_value_file < 0) {
    free(gpio);
    return NULL;
  }
  gpio->value_file = gpio_value_file;

  if (direction == GPIO_OUT) {
    gpio_set_value(gpio, 0);
  }

  return gpio;
}

void gpio_close(gpio_t* gpio) {
  if (gpio == NULL)
    return;
  if (gpio->direction == GPIO_OUT)
    gpio_set_value(gpio, 0);
  close(gpio->value_file);
  free(gpio);
}
