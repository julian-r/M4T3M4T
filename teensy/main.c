#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdint.h>

#include "usb_serial.h"


int main(void)
{
  // set clock prescaler zero, clock 16 MHz
  CLKPR = (1 << CLKPCE);
  CLKPR = 0;
  
  // initialize subsystems
  usb_init();
  
  // enable interrupts
  sei();
  
  // configure as output
  DDRD |= (1 << PORTD6);
  uint8_t on = 0;
  
  while (1) {
    
    // blink teensy on board LED
    if (on)
    {
      PORTD &= (0 << PORTD6);
      on = 0;
    }
    else
    {
      PORTD |= (1 << PORTD6);
      on = 1;
    }
    
    _delay_ms(100);
  }
}

