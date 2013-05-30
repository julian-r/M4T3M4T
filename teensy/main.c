#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdint.h>

#include "usb_serial.h"

#include "twi_master.h"


int main(void)
{
  // set clock prescaler zero, clock 16 MHz
  CLKPR = (1 << CLKPCE);
  CLKPR = 0;

  // initialize subsystems
  usb_init();

  // enable interrupts
  sei();

  // wait for enumeration
  //while (!usb_enumerated());

  // wait for the user to run their terminal emulator program
  // which sets DTR to indicate it is ready to receive.
  //while (!(usb_serial_get_control() & USB_SERIAL_DTR));

  stdout = &usb_serial_output;
  stdin  = &usb_serial_input;

  // configure as output
  DDRD |= (1 << PORTD6);
  uint8_t on = 0;

  //output B0 is for cooling aggregate 
  //B1 is for the internal fan
  DDRB |= (1 << PORTB0)|(1 << PORTB1);
  //
  i2c_init();

  while (1) {

    // blink teensy on board LED
    if (on)
    {
      PORTD &= ~(1 << PORTD6);
      on = 0;
    }
    else
    {
      PORTD |=  (1 << PORTD6);
      on = 1;
    }


    // address 1001 000  0x48

    i2c_start((0x48 << 1) + I2C_WRITE);
    i2c_write(0xac);
    i2c_rep_start((0x48 << 1) + I2C_WRITE);
    i2c_write(0xee);

    i2c_start((0x48 << 1) + I2C_WRITE);
    i2c_write(0xaa);
    i2c_rep_start((0x48 << 1) + I2C_READ);
    uint8_t high = i2c_readAck();
    printf("temp %u", high);
    uint8_t low  = i2c_readNak();
    if (low)
      printf(".5 °C\r\n");
    else
      printf("   °C\r\n");

    _delay_ms(1000);
  }
}

