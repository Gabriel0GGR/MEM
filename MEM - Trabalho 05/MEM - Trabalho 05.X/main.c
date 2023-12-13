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
#pragma code end=0x08
#pragma interrupt ext

unsigned char act=0;
unsigned char tmr=0;
unsigned char res=0;
unsigned char bbon=0;
unsigned char count=0;
unsigned char a=0;
unsigned char b=0;
unsigned char c=0;

void display(char value);

void ext(void)
{
    if(INTCONbits.INT0IF==1)
    {
        act=1;
        if(bbon==0)
        {
            bbon=1;
            res=0;
        }
        else
            bbon=0;
        INTCONbits.INT0IF=0;
    }
    if(INTCON3bits.INT1IF==1)
    {
        act=2;
        INTCON3bits.INT1IF=0;
    }
    if(INTCON3bits.INT2IF==1)
    {
        act=3;
        INTCON3bits.INT2IF=0;
    }
    if (PIR1bits.TMR2IF==1)
    {
        tmr++;
        PIR1bits.TMR2IF=0;
    }
}

void main()
{
    ADCON0bits.ADON=0;
    ADCON1=0xFF;
    DDRA=0x00;
    DDRB=0b00000111;
    DDRC=0x00;
    DDRD=0x00;
    DDRE=0x00;
    RCONbits.IPEN=0;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    INTCONbits.INT0IE=1;
    INTCON3bits.INT1IE=1;
    INTCON3bits.INT2IE=1;
    INTCONbits.INT0IF=0;
    INTCON3bits.INT1F=0;
    INTCON3bits.INT2IF=0;
    INTCON2bits.INTEDG0=0;
    INTCON2bits.INTEDG1=0;
    INTCON2bits.INTEDG2=0;
    T2CON=0b01010001;
    TMR2=0b00000000;
    PR2=0b11111010;
    PIR1bits.TMR2IF=0;
    PIE1bits.TMR2IE=1;
    display(count);
    while(1)
    {
        pause:
        if(act==1 & bbon==1)
        {
            T2CONbits.TMR2ON=1;
            if(res==0)
                c=0b00000001;
            if(tmr!=0 & res==1)
                goto resume1;
            if(tmr!=0 & res==2)
                goto resume2;
            for(a=8; a>0; a--)
            {
                for(b=a-1; b>0; b--)
                {
                    res=1;
                    PORTD=(c<<b);
                    resume1:
                    while(tmr!=100 & act==1);
                    if(act!=1 | bbon==0)
                        goto pause;
                    if(tmr=100)
                        tmr=0;
                }
                for(b=0; b<a-1; b++)
                {
                    res=2;
                    PORTD=(c<<b);
                    resume2:
                    while(tmr!=100 & act==1);
                    if(act!=1 | bbon==0)
                        goto pause;
                    if(tmr=100)
                        tmr=0;
                }
            }
        }
        if(act==2)
        {
            if(count<9)
                count++;
            else
                count=0;
            display(count);
            if(bbon==1)
                act=1;
            else
                act=0;
        }
        if(act==3)
        {
            if(count>0)
                count--;
            else
                count=9;
            display(count);
            if(bbon==1)
                act=1;
            else
                act=0;
        }
    }
}

void display(char value)
{
    if(value==-1)
    {
        PORTA=0b0000000;
        PORTE=0;
    }
    if(value==0)
    {
        PORTA=0b0111111;
        PORTE=0;
    }
    if(value==1)
    {
        PORTA=0b0000110;
        PORTE=0;
    }
    if(value==2)
    {
        PORTA=0b1011011;
        PORTE=255;
    }
    if(value==3)
    {
        PORTA=0b1001111;
        PORTE=255;
    }
    if(value==4)
    {
        PORTA=0b1100110;
        PORTE=255;
    }
    if(value==5)
    {
        PORTA=0b1101101;
        PORTE=255;
    }
    if(value==6)
    {
        PORTA=0b1111101;
        PORTE=255;
    }
    if(value==7)
    {
        PORTA=0b0000111;
        PORTE=0;
    }
    if(value==8)
    {
        PORTA=0b1111111;
        PORTE=255;
    }
    if(value==9)
    {
        PORTA=0b1101111;
        PORTE=255;
    }
}