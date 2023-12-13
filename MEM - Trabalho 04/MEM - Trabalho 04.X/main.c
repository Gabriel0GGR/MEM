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

#define RS PORTEbits.RE0
#define RW PORTEbits.RE1
#define EN PORTEbits.RE2
#define DD PORTD

unsigned char act=0;
void delay_ms(unsigned int a);
void LCD(unsigned char a);
void LCD_DB(unsigned char a);

void ext(void)
{
    if(INTCONbits.INT0IF==1)
    {
        act=1;
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
}

void main()
{
    ADCON0bits.ADON=0;
    ADCON1=0xFF;
    DDRB=0b00000111;
    DDRD=0x00;
    DDRE=0x00;
	DDRC=0x00;
    delay_ms(15);
    LCD(0x30);
    LCD(0x38);
    LCD(0x0F);
    LCD(0x06);
    LCD(0x01);
    delay_ms(2);
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
        if(act==1)
        {
            LCD_DB(' ');
            LCD_DB(' ');
            LCD_DB(' ');
            LCD_DB(' ');
            LCD_DB(' ');
            LCD_DB(' ');
            LCD_DB('I');
            LCD_DB('F');
            LCD_DB('P');
            LCD_DB('R');
            LCD(0x02);
            act=0;
        }
        if(act==2)
        {
            LCD(0xC1);
            LCD_DB(' ');
            LCD_DB(' ');
            LCD_DB('E');
            LCD_DB('L');
            LCD_DB('E');
            LCD_DB('T');
            LCD_DB('R');
            LCD_DB('O');
            LCD_DB('N');
            LCD_DB('I');
            LCD_DB('C');
            LCD_DB('A');
            LCD(0x02);
            act=0;
        }
        if(act==3)
        {
            LCD(0x01);
            LCD(0x02);
            act=0;
        }
    }
}

void delay_ms(unsigned int a)
{
    for(a; a>0; a--)
        Delay100TCYx(5);
}

void LCD(unsigned char a)
{
    RW=0;
    RS=0;
    DD=a;
	PORTC=a;
    EN=1;
    Delay1TCY();
    Delay1TCY();
    EN=0;
    Delay10TCYx(20);
}

void LCD_DB(unsigned char a)
{
    RW=0;
    RS=1;
    DD=a;
	PORTC=a;
    EN=1;
    Delay1TCY();
    Delay1TCY();
    EN=0;
    Delay10TCYx(20);
}