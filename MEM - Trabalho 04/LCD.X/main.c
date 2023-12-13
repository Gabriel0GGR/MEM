#include <p18f4550.h>
#include <delays.h>

#define RS PORTEbits.RE0
#define RW PORTEbits.RE1
#define EN PORTEbits.RE2
#define DD PORTD

void delay_ms(unsigned int a);
void LCD(unsigned char a);

void main()
{
    ADCON0bits.ADON=0;
    ADCON1=0x0F;
    DDRD=0x00;
    DDRE=0x00;
    delay_ms(15);
    LCD(0x30);
    LCD(0x38);
    LCD(0x0F);
    LCD(0x06);
    LCD(0x01);
    delay_ms(2);
    
    while(1)
    {

    }
}

void delay_ms(unsigned int a)
{
    for(a; a>0; a--)
        Delay100TCYx(5);
}

void LCD(unsigned char a)
{
    RS=0;
    DD=a;
    EN=1;
    Delay1TCY();
    Delay1TCY();
    EN=0;
    Delay10TCYx(20);
}