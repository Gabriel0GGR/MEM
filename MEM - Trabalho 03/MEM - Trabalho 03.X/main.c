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

unsigned int global_value=0;
void delay(unsigned int a);
void display_value(char a);
void display_selection(char a);

void ext(void)
{
    if(INTCONbits.INT0IF==1)
    {
        if(global_value>=999)
            global_value=0;
        else
            global_value++;
        INTCONbits.INT0IF=0;
    }
    if(INTCON3bits.INT1IF==1)
    {
        if(global_value<=0)
            global_value=999;
        else
            global_value--;
        INTCON3bits.INT1IF=0;
    }
    if(INTCON3bits.INT2IF==1)
    {
        for(global_value=0; global_value<3; global_value++)
        {
            display_selection(0);
            display_value(0);
            delay(100);
            display_value(-1);
            display_selection(-1);
        }
        global_value=0;
        INTCON3bits.INT2IF=0;
    }
}

void main()
{
    unsigned char a=0;
    unsigned char _3, _2, _1;
    ADCON0bits.ADON=0;
    ADCON1=0xFF;
    DDRB=0b00000111;
    DDRD=0x00;
    for(a=0; a<10; a++)
    {
        display_selection(0);
        display_value(0);
        delay(100);
        display_value(-1);
        display_selection(-1);
    }
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
    while(1)
    {
        _3=global_value/100;
        _2=(global_value%100)/10;
        _1=(global_value%100)%10;
        display_value(-1);
        display_selection(1);
        display_value(_3);
        delay(1);
        display_value(-1);
        display_selection(2);
        display_value(_2);
        delay(1);
        display_value(-1);
        display_selection(3);
        display_value(_1);
        delay(1);
    }
}

void delay(unsigned int a)
{
    for(a; a!=0; a--)
    {
        Delay1KTCYx(5);
    }
}

void display_selection(char a)
{
    if(a==-1)
        PORTB=0b00000000;
    if(a==0)
        PORTB=0b11100000;
    if(a==1)
        PORTB=0b00100000;
    if(a==2)
        PORTB=0b01000000;
    if(a==3)
        PORTB=0b10000000;
}

void display_value(char a)
{
    if(a==-1)
        PORTD=0b00000000;
    if(a==0)
        PORTD=0b00111111;
    if(a==1)
        PORTD=0b00000110;
    if(a==2)
        PORTD=0b01011011;
    if(a==3)
        PORTD=0b01001111;
    if(a==4)
        PORTD=0b01100110;
    if(a==5)
        PORTD=0b01101101;
    if(a==6)
        PORTD=0b01111101;
    if(a==7)
        PORTD=0b00000111;
    if(a==8)
        PORTD=0b01111111;
    if(a==9)
        PORTD=0b01101111;
}
