
#ifndef RPI_DRIVER_HPP
#define RPI_DRIVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>

#define GPIO_ADDR 0x3F000000
#define GPIO_BASE GPIO_ADDR + 0x200000
#define GPIO_SIZE 0x00B0

class gpio_driver {
    #define INP_GPIO(c, g) *(c+((g)/10)) &= ~(7<<(((g)%10)*3))
    #define OUT_GPIO(c, g) *(c+((g)/10)) |= ~(1<<(((g)%10)*3))
    #define SET_GPIO_ALT(c, g, a) *(c+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
    
    #define GPIO_SET(c) *(c+7) // sets bits which are 0 ignores bits which are 1
    #define GPIO_CLR(c) *(c+10) // clears bits which are 1 ignores bits which are 0
    
    #define GET_GPIO(c, g) *((c+13)&(1<<g)) // 0 if LOW, 1<<g if HIGH
    
    #define GPIO_PULL(c) *(c+37)
    #define GPIO_PULLCLK0(c) *(c+38) // Pull up/pull down clock
    
public:
    struct gpio {
        int mem_fd; // Memory file descriptor
        void *gpio_map; // Memory map
        volatile unsigned *gpio; // Access
    };
    
    struct gpio initialize_gpio();
    void setmode(int pin, int mode);
    void setvalue(int pin, int value);
    
};

#endif