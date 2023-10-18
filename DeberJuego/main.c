#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <time.h>

int main(void)
{
	int dire;
	DDRB = 0B11111111;
	DDRD = 0B11111111;
	DDRC = 0B00000111;
	char PORT[8] =  {1,2,4,8,16,32,64,128};
	char ladoD[]={0x00,0x00,0x00,0x00,0x7E,0x7E,0x7E,0x00};
	char limpiar[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};	
	char ladoI[]={0x00,0x7E,0x7E,0x7E,0x00,0x00,0x00,0x00};
	char win[]={0x00,0x1C,0x20,0x10,0x10,0x20,0x1C,0x00,
		0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,
	0x00,0x3C,0x08,0x04,0x04,0x38,0x00,0x00};
	char lose[]={0x00,0x7E,0x40,0x40,0x40,0x40,0x40,0x00,
	0x00,0x3C,0x42,0x42,0x42,0x42,0x3C,0x00,
	0x00,0x46,0x49,0x49,0x49,0x31,0x00,0x00,
	0x00,0x7E,0x4A,0x4A,0x4A,0x42,0x00,0x00};
	while (1)
	{
	int contador=0;
	int marcador=0;
	int estadoBoton1=0;
	int estadoBoton2=0;
	while(contador<10){
		PORTC=1<<PORTC2;
		dire=rand() % (2);;
		if(dire==0){
			for(int k=0; k<250; k++)
			{
				for (int j=0; j<8;j++)//
				{
					PORTD = PORT[j];
					PORTB = ~ladoD[j];
					_delay_ms(0.10);
				}
				if((PINC & (1<<PORTC0))){
					estadoBoton1=1;
				}
				if((!(PINC&(1<<PORTC0))) && estadoBoton1==1){
					estadoBoton1=0;
					marcador++;
				}
			}
			contador++;
			_delay_ms(150);
		}
		if(dire==1){
			for(int k=0; k<200; k++)
			{
				for (int j=0; j<8;j++)
				{
					PORTD = PORT[j];
					PORTB = ~ladoI[j];
					_delay_ms(0.10);
				}
				if((PINC & (1<<PORTC1))){
					estadoBoton2=1;
				}
				if((!(PINC&(1<<PORTC1))) && estadoBoton2==1){
					estadoBoton2=0;
					marcador++;
				}
				
			}
			contador++;
			_delay_ms(150);
		}
	}
	
	PORTC=0x0;
	_delay_ms(10);
	
	if (marcador>=7){
		PORTC=0x0;
		PORTC=1<<PORTC3;
		for (int i=0;i<16;i++){
			for(int k=0; k<30; k++)
			{
				for (int j=0; j<8;j++)
				{
					PORTD = PORT[j];
					PORTB = ~win[i+j];
					_delay_ms(0.10);
				}
			}
			
		}

	}
	if(marcador<7){
		_delay_ms(50);
		PORTC=0x0;
		PORTC=1<<PORTC4;
		for (int i=0;i<24;i++){
			for(int k=0; k<30; k++)
			{
				for (int j=0; j<8;j++)
				{
					PORTD = PORT[j];
					PORTB = ~lose[i+j];
					_delay_ms(0.10);
				}
			}
			
		}
	
	}
	for(int k=0; k<100; k++)
	{
		for (int j=0; j<8;j++)//
		{
			PORTD = PORT[j];
			PORTB = ~limpiar[j];
			_delay_ms(0.10);
		}
	}
	PORTC=0x0;
	_delay_ms(100);
	
}
}
