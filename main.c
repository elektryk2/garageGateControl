//#include <avr/io.h>
//#include <avr/interrupt.h>
#include "iodef.h"
#include <avr/eeprom.h>
#include <util/delay.h>

#include <stdlib.h>
#include <avr/interrupt.h> 

#define BUTTON		PD.PIN.B6

#define OCPIN		PD.PIN.B4



#define OUTPORT		PD.PORT.B3

#define DIRPORT		PD.PORT.B5
	
int main (void)
{

	PD.DDR.B3=1;
	//OUTPORT=1;
	
	PD.DDR.B5=1;
	
	
	PD.PORT.B2=1;
	
	PD.PORT.B6=1;
	
	int pressTime=0, notPressedTime=0;
	int buttonTime=0;
	
	int oCtime=0;
	
	int8_t action=0, prevAction=0;
	
	uint8_t pressed=0, pressedEdge=0;
	uint8_t dir=0;
	
	
	
	
	int retryTime=0;
	uint8_t closeRetry=0;
	
	_delay_ms(2000);
	
	
	while(1)
	{
	/*	if(!BUTTON && !pressedEdge)
		{
			pressedEdge=1;
			
			
			if(pressed)
				pressed=0;
			
			else
			{
				pressed=1;
				
				if(dir==1) dir=0;
				else dir=1;
			}
			

			
			
			_delay_ms(100);
			//action++;
		}
		if(BUTTON) pressedEdge=0;
		
		while(!BUTTON){}*/
		
		
		
		if(!BUTTON)
			buttonTime++;
			
		if(buttonTime>200 && !pressedEdge)
		{
			//buttonTime=0;
			pressedEdge=1;

			if(pressed)
			pressed=0;
			
			else
			{
				pressed=1;
				
				if(dir==1) dir=0;
				else dir=1;
			}
		}
		
		if(BUTTON)
		{
			buttonTime=0;
			pressedEdge=0;
		}
		
		/*if(action>2) action=0;
		
		if(action!=prevAction)
		{
			if(action==0)
			{
				pressed=1;
				dir=0;
			}
			
			if(action==1)
			{
				pressed=0;
				//dir=0;
			}
			
			if(action==2)
			{
				pressed=1;
				dir=1;
			}
			prevAction=action;
		}
		*/
		
		
		if(pressed)
		{
			pressTime++;
			notPressedTime=0;
			
			if(pressTime>14000) //20000 zmienione na 14000
			{
				pressTime=0;
				pressed=0;
				//if(dir==1) dir=0;
				//else dir=1;
			}
			if(dir) DIRPORT=1;
			else DIRPORT=0;
			
			//if(pressTime>100)
				OUTPORT=1;
		}
		else
		{
			
			if(closeRetry)
			{
				retryTime++;
				OUTPORT=0;
				if(retryTime>1000)
				{
					if(retryTime<2000)
					{
						OUTPORT=1;
					}
					else
						closeRetry=0;
				}
			}
			else
			{		
				pressTime=0;
				//DIRPORT=0;
				OUTPORT=0;
			}

			
			if(notPressedTime>300)
			{
				DIRPORT=0;
			}
			else
				notPressedTime++;
		}
			
		
		if((!OCPIN))
		{
			oCtime++;
			
			if(pressTime>2000/* && pressTime<10000*/) //2000 zmienione na 1000
			{
				pressed=0;
				closeRetry=1;
			}
		}
		else 
			oCtime=0;
			
			
		if(oCtime>5) //300 zmienione na 100
			pressed=0;
		
		_delay_ms(1);
	}
	
}