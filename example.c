#include "gpio_basic_driver.h"

void delay(void)
{
  for (volatile int i=0;i< 1000000;i++);  // Simple delay. Note, this is a software delay and not accurate.
}

int main(void)
{

gpio_init(2, GPIO_OUTPUT);  // This will set pin 2 as output. The inbult led ob board is connected to this pin.

  while(1)
    {
      gpio_toggle(2);  // Toggles pin 2 state
      delay();  // Simple delay
    }
  
}
