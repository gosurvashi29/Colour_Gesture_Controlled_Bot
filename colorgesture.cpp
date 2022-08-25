/*
 * colorgesture.cpp
 *
 * Created: 27-06-2015 16:11:30
 *  Author: Urvashi
 */ 


#define F_CPU 8000000
#include<avr/io.h>
#include<util/delay.h>


#define USART_BAUDRATE 9600    // Baud Rate value
#define BAUD_PRESCALE ((F_CPU / (USART_BAUDRATE * 16UL)) - 1)

void usart_init(void);
void usart_putch(unsigned char send);
unsigned int usart_getch(void);


int main()
{    unsigned char value;
	DDRB=0xff;
	usart_init();        // initialization of USART
	while(1)
	{
		
		value=usart_getch();
		//usart_putch(value);
		//PORTB=value;
		if (value=='1')

		{
			
			PORTB=0b00000001;
			
		}
		else if (value=='2')
		{
			PORTB=0b00000010;
		}
		else if (value=='3')
		{
			PORTB=0b00000100;
		}
		else if (value=='4')
		{
			PORTB=0b00001000;
		}
		else
		PORTB=0b00000000;
		
		
		
		
	}
	//return 0;
}


void usart_init()
{
	UCSRB |= (1 << RXEN)|(1<<TXEN);   // Turn on the transmission and reception circuitry
	UCSRC |= (1 << URSEL)  | (1<<USBS)| (1 << UCSZ0) | (1 << UCSZ1);
	// Use 8-bit character sizes
	
	UBRRL = BAUD_PRESCALE;
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value..
	// into the high byte of the UBRR register
}

unsigned int usart_getch()
{
	while ((UCSRA & (1 << RXC)) == 0);
	{
	}    // Do nothing until data has been received and is ready to be read from UDR
	
	return UDR; // return the byte
}


void usart_putch(unsigned char send)
{    while(!(UCSRA & (1<<UDRE)))
	{
	}
	UDR=send;
}
