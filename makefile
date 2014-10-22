all: test_pwm

test_pwm: test_pwm.c pwm_control pwm_driver gpio_control system
	gcc -o test_pwm test_pwm.c -L. -lpwm_driver

pwm_driver: pwm_driver.c pwm_driver pwm_control gpio_control system
	gcc -c pwm_driver.c -o pwm_driver.o
	ar rcs libpwm_driver.a pwm_driver.o pwm_control.o gpio_control.o system.o

pwm_control: pwm_control.c pwm_control.h system.h
	gcc -c pwm_control.c -o pwm_control.o

gpio_control: gpio_control.c gpio_control.h
	gcc -c gpio_control.c -o gpio_control.o

system: system.c system.h
	gcc -c system.c -o system.o
