#include"UART.H"
#define NUMBER +918072574213 //Here insert your number where you want to send message
//#define msg "  is OTP to login to our Multilevel security System,OTP Will Expires in 1 Minutes."

void DELAY_MILLISECONDS(int msec)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<msec);
	T0TCR=0X03;
	T0TCR=0X00;
}

void SMS_ALERT1(void)
{
  delay_ms(500);
  UART0_STR("AT\r\n");
  delay_ms(500);
  UART0_STR("AT+CMGF=1\r\n");
  delay_ms(500);
  UART0_STR("AT+CMGS=\"+918072574213\" \r\n");
  delay_ms(500);
	UART0_STR("BE ALERT \r\n");
  UART0_STR("Soil is dry, turn on the pump\r\n");
  delay_ms(500);
  UART0_TX(0X1A);
  delay_ms(500);
}

void SMS_ALERT2(void)
{
  delay_ms(500);
  UART0_STR("AT\r\n");
  delay_ms(500);
  UART0_STR("AT+CMGF=1\r\n");
  delay_ms(500);
  UART0_STR("AT+CMGS=\"+918072574213\" \r\n");
  delay_ms(500);
	UART0_STR("BE ALERT \r\n");
  UART0_STR("Soil is WET, turn off the pump\r\n");
  delay_ms(500);
  UART0_TX(0X1A);
  delay_ms(500);
}

