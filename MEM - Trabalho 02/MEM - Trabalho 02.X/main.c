#include<p18f4550.h>
#include<delays.h>

#pragma config CPUDIV = OSC1_PLL2 // System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config FOSC = HS         // Oscillator Selection bits (HS oscillator (HS))
#pragma config PWRT = OFF        // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF         // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config VREGEN = OFF      // USB Voltage Regulator Enable bit (USB voltage regulator disabled)
#pragma config WDT = OFF         // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config CCP2MX = ON       // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF       // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config MCLRE = ON        // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)

void delay(unsigned int a);
char display(char a);

void main()
{
    unsigned char S1=1;
    unsigned char S2=1;
    unsigned char A=0;
    unsigned char a=0;

    ADCON0bits.ADON=0;
    ADCON1=0xFF;
    DDRD=0b00000011;
    DDRB=0b00000000;

    while(1)
    {
		start:
        S1=PORTD&0b00000001;
        S2=PORTD&0b00000010;
        if(S1==0)
        {
			for(A=0; A<10; A++)
            {
				while(S1==0)
					S1=PORTD&0b00000001;
                a=display(A);
                PORTB=a;
                S1=PORTD&0b00000001;
                delay(300);
				while(S1==0)
				{
					S1=PORTD&0b00000001;
					if(S1==1)
						goto start;
					S1=0;
				}
            }
        }
        if(S2==0)
        {
            for(A=10; A>0; A--)
            {
				while(S2==0)
					S2=PORTD&0b00000010;
                a=display(A-1);
                PORTB=a;
                S2=PORTD&0b00000010;
                delay(300);
				while(S2==0)
				{
					S2=PORTD&0b00000010;
					if(S2==2)
						goto start;
					S2=0;
				}
            }
        }
    }
}

void delay(unsigned int a)
{
    for(a; a!=0; a--)
    {
        Delay1KTCYx(5);
    }
}

char display(char a)
{
    if(a==0)
        return 0b00111111;
    if(a==1)
        return 0b00000110;
    if(a==2)
        return 0b01011011;
    if(a==3)
        return 0b01001111;
    if(a==4)
        return 0b01100110;
    if(a==5)
        return 0b01101101;
    if(a==6)
        return 0b01111101;
    if(a==7)
        return 0b00000111;
    if(a==8)
        return 0b01111111;
    if(a==9)
        return 0b01101111;
}