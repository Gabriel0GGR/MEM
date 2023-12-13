#include <p18f4550.h>
#include <delays.h>

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
#define RW PORTEbits.RE2
#define EN PORTEbits.RE1

unsigned int print=0;
unsigned float pwm=0;
void delay_ms(unsigned int a);
void LCD(unsigned char a);
void LCD_DB(unsigned char a);
void PWM(unsigned int a);

void ext(void)
{
    if(INTCONbits.INT0IF==1)
    {
        if(pwm<100)
            pwm=pwm+10;
        INTCONbits.INT0IF=0;
    }
    if(INTCON3bits.INT1IF==1)
    {
        if(pwm>0)
            pwm=pwm-10;
        INTCON3bits.INT1IF=0;
    }
    if(INTCON3bits.INT2IF==1)
    {
        pwm=0;
        INTCON3bits.INT2IF=0;
    }
    if (PIR1bits.TMR2IF==1)
    {
        print++;
        PIR1bits.TMR2IF=0;
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
    DDRCbits.RC1=0;
    T2CONbits.T2CKPS0=1;
    T2CONbits.T2CKPS1=1;
    TMR2=0x00;
    PR2=0xFF;
    PIR1bits.TMR2IF=0;
    PIE1bits.TMR2IE=1;
    CCP2CONbits.CCP2M0=1;
    CCP2CONbits.CCP2M1=1;
    CCP2CONbits.CCP2M2=1;
    CCP2CONbits.CCP2M3=1;
    T2CONbits.TMR2ON=1;
    PWM(0);
    while(1)
    {
        if(print>=855)
        {
            LCD(0x02);
            LCD_DB(' ');
            LCD_DB('P');
            LCD_DB('W');
            LCD_DB('M');
            LCD_DB(':');
            if(pwm<100)
            {
                LCD_DB('0');
                LCD_DB((pwm/10)+48);
                LCD_DB('0');
            }
            if(pwm>=100)
            {
                LCD_DB('1');
                LCD_DB('0');
                LCD_DB('0');
            }
            LCD_DB('%');
            if(pwm==00)
            {
                LCD(0xC1);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
            }
            if(pwm==10)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);                
            }
            if(pwm==20)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);                
            }
            if(pwm==30)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);                
            }
            if(pwm==40)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);                
            }
            if(pwm==50)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);                
            }
            if(pwm==60)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);                
            }
            if(pwm==70)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);                
            }
            if(pwm==80)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);
                LCD_DB(0b11011011);                
            }
            if(pwm==90)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11011011);                
            }
            if(pwm==100)
            {
                LCD(0xC1);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);
                LCD_DB(0b11111111);                
            }
            PWM(1023/(100/pwm));
            print=0;
        }
    }
}

void delay_ms(unsigned int a)
{
    for(a; a>0; a--)
        Delay100TCYx(50);
}

void LCD(unsigned char a)
{
    RW=0;
    RS=0;
    PORTD=a;
    EN=1;
    Delay1TCY();
    Delay1TCY();
    EN=0;
    Delay100TCYx(20);
}

void LCD_DB(unsigned char a)
{
    RW=0;
    RS=1;
    PORTD=a;
    EN=1;
    Delay1TCY();
    Delay1TCY();
    EN=0;
    Delay100TCYx(20);
}

void PWM(unsigned int a)
{
    CCP2CON=(0b00001111)|(a<<4);
    CCPR2L=a>>2;
}