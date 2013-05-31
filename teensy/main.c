#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdint.h>

#include "usb_serial.h"

#include "twi_master.h"


struct temperature
{
    uint8_t high;
    uint8_t low;
};

struct 
{
    uint8_t target_temperature;
    uint8_t hysteresis;
    uint8_t timer_counter;
    uint8_t timer_cycles;
} g_temperature_control = { 
    .target_temperature = 16,
    .hysteresis = 2,
    .timer_counter = 0,
    .timer_cycles = 6       //71~~5 Minutes
};


// prototypes
void read_temp(struct temperature* temp);

ISR(INT2_vect)
{
    EIMSK &= ~(1 << INT2);
    //EIFR &= ~(1 << INT2);
    EIFR |= (1 << INT2);

    // shut off motor
    PORTC &= ~(1 << PORTC7);

    printf("int\r\n");
    _delay_ms(500);

    EIMSK |= (1 << INT2);
}


ISR(TIMER1_OVF_vect)
{
    struct temperature temp;

    read_temp(&temp);

    printf("temp %u", temp.high);
    if (temp.low)
      printf(".5 °C\r\n");
    else
      printf("   °C\r\n");

    // control system ;)
    g_temperature_control.timer_counter++;
    
    if(g_temperature_control.timer_counter >=
            g_temperature_control.timer_cycles)
    {
        g_temperature_control.timer_counter = 0;

        int8_t temp_diff = temp.high - g_temperature_control.target_temperature; 
        if(temp_diff >= g_temperature_control.hysteresis)
        {
            //PORTB &= ~((1 << PORTB0)|(1 << PORTB1)); //inverse logic!
            printf("aggregate on\r\n");
        }
        else if(temp_diff < g_temperature_control.hysteresis)
        {
            //PORTB |= (1 << PORTB0)|(1 << PORTB1); //inverse logic
            printf("aggregate off\r\n");
            //cool off
            //
        }
    }
}


void read_temp(struct temperature* temp)
{
    // address 1001 000  0x48
    i2c_start((0x48 << 1) + I2C_WRITE);
    i2c_write(0xac);
    i2c_rep_start((0x48 << 1) + I2C_WRITE);
    i2c_write(0xee);

    i2c_start((0x48 << 1) + I2C_WRITE);
    i2c_write(0xaa);
    i2c_rep_start((0x48 << 1) + I2C_READ);
    temp->high = i2c_readAck();
    temp->low  = i2c_readNak();
}

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
  while (!usb_enumerated());

  // wait for the user to run their terminal emulator program
  // which sets DTR to indicate it is ready to receive.
  while (!(usb_serial_get_control() & USB_SERIAL_DTR));

  stdout = &usb_serial_output;
  stdin  = &usb_serial_input;

  // configure as output
  DDRD |= (1 << PORTD6);
  uint8_t on = 0;

  //output B0 is for cooling aggregate 
  //B1 is for the internal fan
  //DDRB |= (1 << PORTB0)|(1 << PORTB1);
  //test motor slot
  DDRC |= (1 << PORTC7);

  //
  //
  

  i2c_init();

    // 16 bit timer for cooling control
    // set prescaler to 1024
    // (2^16)/(16000000/1024) = 4.194s
    //TCCR1B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
    // start timer
    //TIMSK1 |= (1 << TOIE1);

    // use as input
    DDRD &= ~(1 << PORTD2);
    // enable internal pull-up
    PORTD |= (1 << PORTD2);
    // trigger on falling edge
    EICRA |= (1 << ISC21) | (0 << ISC20);

  while (1) {
      uint8_t shaft;
      printf("shaft\r\n");
      //int16_t chr = usb_serial_getchar();
      //printf("shaft %c\r\n", chr);
      int8_t chr;
      scanf("%d", &chr);
      printf("shaft %d\r\n", chr);

      // disable interrupt (switch perm on)
      EIMSK &= ~(1 << INT2);
      // turn on motor
      PORTC |=  (1 << PORTC7);

      // avoid position on switch
      _delay_ms(1500);

      // clear interrupt flag
      //EIFR &= ~(1 << INT2);
      EIFR |= (1 << INT2);
      // reenable interrupt
      EIMSK |= (1 << INT2);
  }
}

