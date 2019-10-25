#include "rpi_driver.hpp"

/*
    struct gpio {
        int mem_fd; // Memory file descriptor
        void *gpio_map; // Memory map
        volatile unsigned *gpio; // Access
    };
*/
struct gpio_driver::gpio mine;
struct gpio_driver::gpio gpio_driver::initialize_gpio() {
    struct gpio_driver::gpio temp;
    
    if ((temp.mem_fd = open("/dev/mem", O_RDWR|OSYNC)) < 0) {
        cout << "Cannot open the /dev/mem" << endl;
        return temp;
    }
    
    temp.gpio_map = (int *) mmap(
        NULL,
        GPIO_SIZE,
        PROT_READ|PROT_WRITE|PROT_EXEC,
        MAP_SHARED,
        temp.mem_fd,
        GPIO_BASE
    );
    
    close(temp.mem_fd);
    
    if (temp.gpio_map == MAP_FAILED) {
        cout << "MMAP failed to create, error: " << temp.gpio_map << endl;
        return temp;
    }
    
    temp.gpio = (volatile unsigned *) temp.gpio_map;
    cout << "pointer: " << temp.gpio_map << endl;
    return temp;
}

void gpio_driver::setmode(int pin, int mode) {
    if (pin == 1) {
        if (value == 1) {
            GPIO_SET(mine.gpio) = 0x02;
            /*
                *(mine.gpio + (unsigned int) 0x1C) |= 0b010; // GPIO1
            */
        } else {
            GPIO_CLR(mine.gpio) = 0x02;
            /*
                *(mine.gpio + (unsigned int) 0x28) |= 0b010; // GPIO1
            */
        }
    }
}
