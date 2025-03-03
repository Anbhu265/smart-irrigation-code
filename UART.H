#include<LPC21xx.H>
#include<stdio.h>
void UART_INITIALIZE(void)
{
	PINSEL0|=5;
	U0LCR=0X83;
	//U0DLM=0X00;
	U0DLL=97;
	U0LCR=0X03;
}
unsigned char UART0_RX()
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void UART0_TX(unsigned char ch)
{
	U0THR=ch;
	while(!(U0LSR & 0X20));
	return;
}
void UART0_STR(unsigned char *str)
{
	while(*str)
	{
		UART0_TX(*str++);
	}
}
  void UART0_integer(int n)
{
	int i=0;
	unsigned char a[5];
	while(n!=0)
	{
		a[i++]=(n%10)+48;
		n=n/10;
	}
	--i;
	while(1)
	{
		UART0_TX(a[i--]);
		if(i==-1)
		break;
	}
}