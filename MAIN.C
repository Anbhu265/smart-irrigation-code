

	 /* Hardware:

    LPC2129 microcontroller
    Soil moisture sensor
    Relay module or a transistor circuit to control the irrigation pump
    Power supply
    Breadboard	 */


#include <LPC21xx.h> // Include the LPC21xx definitions
#include "LCD.H"
#include "SMS.H"
#define MOISTURE_SENSOR_PIN 22 // Change this based on your setup
#define PUMP_CONTROL_PIN 17    // Change this based on your setup

void delay(unsigned int time) {
    while (time--) {
	int i;
        for (i = 0; i < 1000; i++); // Simple delay loop
    }
}
  void delay_s(int msec)
{
	T0PR=15000000-1;
	T0TCR=0X01;
	while(T0TC<msec);
	T0TCR=0X03;
	T0TCR=0X00;
}


void init() {
    // Set P0.0 as input for the moisture sensor
    IODIR0 &= ~(1 << MOISTURE_SENSOR_PIN);
    
    // Set P0.1 as output for pump control
    IODIR0 |= (1 << PUMP_CONTROL_PIN);
	IOCLR0 |= (1 << PUMP_CONTROL_PIN);
}

int readMoistureSensor() {
    // Read moisture sensor value
    return (IOPIN0 & (1 << MOISTURE_SENSOR_PIN)) ? 1 : 0; // 1 if dry, 0 if wet
}

void controlPump(int status) {
    if (status) {
        // Turn off the pump
       	  IOCLR0 |= (1 << PUMP_CONTROL_PIN); // Assuming active LOW relay
        } else {
        // Turn on the pump
        
		 IOSET0 |= (1 << PUMP_CONTROL_PIN); // Assuming active LOW relay
    }
}

int main() {
 int count1=0,count2=0;
unsigned char s[]="//Welcome To Smart Irrigation System//";
    init();
	LCD_Init();

	//	lcdcmd(0X01);
		lcdcmd(0X80);				 
	   LCD_STRING_ROTATE(s);
     delay_s(50);
	 lcdcmd(0X01);
	 	UART_INITIALIZE();
    //lcdstring("SMART IRRIGATION SYSTEM");
    while (1) 
	{
	     
		 int moistureLevel = readMoistureSensor();
	    // LCD_STRING_ROTATE(s);			
         
			 
			  			
					if (moistureLevel)
				 {
				 
            // Soil is dry, turn on the pump
			    lcdcmd(0X01);
			    lcdcmd(0xc0);
		    	lcdstring("MOTOR ON");
                controlPump(0); // Turn on
			 	 if(count1<3)
			    SMS_ALERT1();
				count1++;
			    
			//	UART0_integer(count);
			   // delay_ms(50);
			
			    }
				
		        	  	if(moistureLevel==0)
		        {
					 count1=0;
            // Soil is wet, turn off the pump
		     	lcdcmd(0X01);
		    	lcdcmd(0xc0);
		    	lcdstring("MOTOR OFF");
                controlPump(1); // Turn off
			
				//  if(count2<3)
			  //  SMS_ALERT2();
					count2++;
			   
			//	UART0_integer(count);
			   //delay_ms(50);
					 
                }

        delay(1000); // Check every 10 seconds
    }

    return 0;
}

