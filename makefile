INCLUDE=/usr/local/include/freebasic/BB/
LIB=/usr/local/lib/freebasic/

all: test_pwm

test_pwm: test_pwm.c light-pwm
	gcc -o test_pwm test_pwm.c /usr/local/lib/freebasic/fbrt0.o -lpruio -L$(LIB) -lfb -lprussdrv -ltermcap -lsupc++ -pthread -lm -L. -llight-pwm

light-pwm: pwm_driver1 pwm_driver2
	ar rcs liblight-pwm.a pwm_driver1.o pwm_driver2.o pwm_control.o gpio_control.o system.o

pwm_driver1: pwm_driver1.c pwm_driver1 pwm_control gpio_control system
	gcc -c pwm_driver1.c -o pwm_driver1.o

pwm_driver2: pwm_driver2.c pwm_driver2 pwm_control gpio_control system
	gcc -c pwm_driver2.c -o pwm_driver2.o

pwm_control: pwm_control.c pwm_control.h system.h
	gcc -c pwm_control.c -o pwm_control.o

gpio_control: gpio_control.c gpio_control.h
	gcc -c gpio_control.c -o gpio_control.o

system: system.c system.h
	gcc -c system.c -o system.o
