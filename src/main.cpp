#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU = 16000000
int count = 0;
//enable as input
void init()
{
  //SET AS INPUT
  DDRD &= ~(_BV(DDD2) |_BV(DDD3));
  //Enable Pullup
  PORTD |= (_BV(PD3) |_BV(PD2));
  //led output all outputs
  DDRA |= 0xFF;
  PORTA |= 0xFF;
  
  // Initialize the setting of the interrupt. Current 11, rising one 
    // When you press, only after releasing it triggers
    //ISC21 and ISC20 are for INT2
  EICRA |= _BV(ISC21) | _BV(ISC20) | _BV(ISC31) | _BV(ISC30);
  // Enable INT2 in the Externalinterruptregister/int2 represents pin location basically each pin has different interupt so pin pd3 and pd2 in this case
	EIMSK |= (_BV(INT2)| _BV(INT3));
  //enable global interupts mandatory
  sei();
}
//interupt service routine
//turning on the led
ISR(INT2_vect)
{
  if(count <= 7){
  //  PORTA = PORTA ^ 0xFF;
   PORTA &= ~_BV(count);
   count++;
  }
}
//turning off leds
ISR(INT3_vect)
{
  if(count >= 0){
  //  PORTA = PORTA ^ 0xFF;
   PORTA |= _BV(count);
   count--;
  }
}
int main(int argc, char const *argv[])
{
	init();
	while (1)
    {
	/* code that does random stuff */
	}
  return 0;
}


