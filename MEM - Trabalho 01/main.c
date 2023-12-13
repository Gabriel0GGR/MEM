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

void main()
{
    unsigned char a=0;
    unsigned char b=0;
    unsigned char c=0;
    unsigned char d=0;
    
    ADCON0bits.ADON=0;
    ADCON1=0xFF;
    DDRB=0;
    
    while(1)
    {
        for(a=0; a<3; a++)
        {
            PORTB=0xFF;
            Delay10KTCYx(100);
            PORTB=0x00;
            Delay10KTCYx(100);
        }
        d=0b00000001;
        Delay10KTCYx(255);
        for(b=8; b>0; b--)
        {
            for(c=b-1; c>0; c--)
            {
                PORTB=(d<<c);
                Delay10KTCYx(100);
            }
            for(c=0; c<b-1; c++)
            {
                PORTB=(d<<c);
                Delay10KTCYx(100);
            }
        }
        PORTB=0b01010101;
        Delay10KTCYx(55);
        PORTB=0b10101010;
        Delay10KTCYx(55);
        PORTB=0;
        Delay10KTCYx(255);
    }
}