/*******************************************************
This program was created by the CodeWizardAVR V3.31 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 07-02-2018
Author  : 
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/
#include <delay.h>
#include <io.h>
#include <stdlib.h>
// Alphanumeric LCD functions
#include <alcd.h>


unsigned char f[20],l[20];
// Declare your global variables here
    int k=1;
 int tz1=0,tz2=0,tz3=0,gozain=0; 
     
 int x,y,linter=0,finter=0,p=0,er=0;
 float kp=4;
 unsigned char ch[20];     
 
 
   void procedure1();
   void procedure2();
   int goforward(int a,int b);
   int gobackward(int a,int b);
   int goleft(int a,int b);
   int comeback(int a,int b); 
   void stop(); 
   void update();
  
// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
   (PIND.0==1&&PINF.7==0&&PINF.6==1)? (finter++) : (0);                 
   (PIND.0==1&&PINF.6==0&&PINF.7==1)? (finter--) : (0);                  
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
  (PIND.1==1&&PINF.2==0&&PINF.0==0)? (linter++) : (0);                    
  (PIND.1==1&&PINF.3==0&&PINF.1==0)? (linter--) : (0);                   
}

// External Interrupt 3 service routine
interrupt [EXT_INT3] void ext_int3_isr(void)
{
// Place your code here

}

// External Interrupt 4 service routine
interrupt [EXT_INT4] void ext_int4_isr(void)
{
// Place your code here
   (PINE.4==1&&PINC.7==0&&tz1==0&&tz2==0&&tz3==0)? (tz1=1,tz2=0,tz3=0,PORTC.7=1) : (0);
}

// External Interrupt 5 service routine
interrupt [EXT_INT5] void ext_int5_isr(void)
{
// Place your code here
    (PINE.5==1&&PINC.7==0&&tz2==0&&tz1==0&&tz3==0)? (tz2=1,tz1=0,tz3=0,PORTC.7=1) : (0);
}

// External Interrupt 6 service routine
interrupt [EXT_INT6] void ext_int6_isr(void)
{
// Place your code here
    (PINE.6==1&&PINC.7==0&&tz3==0&&tz2==0&&tz1==0)? (tz3=1,tz1=0,tz2=0,PORTC.7=1) : (0);
}

// External Interrupt 7 service routine
interrupt [EXT_INT7] void ext_int7_isr(void)
{
// Place your code here
     (PINE.7==1)? (gozain=1) : (0);
}

#define DATA_REGISTER_EMPTY (1<<UDRE0)
#define RX_COMPLETE (1<<RXC0)
#define FRAMING_ERROR (1<<FE0)
#define PARITY_ERROR (1<<UPE0)
#define DATA_OVERRUN (1<<DOR0)

// Get a character from the USART1 Receiver
#pragma used+
char getchar1(void)
{
unsigned char status;
char data;
while (1)
      {
      while (((status=UCSR1A) & RX_COMPLETE)==0);
      data=UDR1;
      if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
         return data;
      }
}
#pragma used-

  void main(void)
  {
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=Out Bit0=Out 
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (0<<DDB3) | (0<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=T Bit2=T Bit1=0 Bit0=0 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(1<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (1<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Port E initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (1<<DDE2) | (0<<DDE1) | (0<<DDE0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (0<<PORTE1) | (0<<PORTE0);

// Port F initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRF=(1<<DDF7) | (1<<DDF6) | (1<<DDF5) | (1<<DDF4) | (1<<DDF3) | (1<<DDF2) | (1<<DDF1) | (1<<DDF0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTF=(0<<PORTF7) | (0<<PORTF6) | (0<<PORTF5) | (0<<PORTF4) | (0<<PORTF3) | (0<<PORTF2) | (0<<PORTF1) | (0<<PORTF0);

// Port G initialization
// Function: Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRG=(0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (0<<DDG1) | (0<<DDG0);
// State: Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTG=(0<<PORTG4) | (0<<PORTG3) | (0<<PORTG2) | (0<<PORTG1) | (0<<PORTG0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Fast PWM top=0xFF
// OC0 output: Non-Inverted PWM
// Timer Period: 2.048 ms
// Output Pulse(s):
// OC0 Period: 2.048 ms Width: 0 us
ASSR=0<<AS0;
TCCR0=(1<<WGM00) | (1<<COM01) | (0<<COM00) | (1<<WGM01) | (0<<CS02) | (1<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Fast PWM top=0x00FF
// OC1A output: Non-Inverted PWM
// OC1B output: Non-Inverted PWM
// OC1C output: Non-Inverted PWM
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 2.048 ms
// Output Pulse(s):
// OC1A Period: 2.048 ms Width: 0 us
// OC1B Period: 2.048 ms Width: 0 us
// OC1C Period: 2.048 ms Width: 0 us
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0) | (1<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (1<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
TCCR2=(0<<WGM20) | (0<<COM21) | (0<<COM20) | (0<<WGM21) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer/Counter 3 initialization
// Clock source: System Clock
// Clock value: Timer3 Stopped
// Mode: Normal top=0xFFFF
// OC3A output: Disconnected
// OC3B output: Disconnected
// OC3C output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer3 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR3A=(0<<COM3A1) | (0<<COM3A0) | (0<<COM3B1) | (0<<COM3B0) | (0<<COM3C1) | (0<<COM3C0) | (0<<WGM31) | (0<<WGM30);
TCCR3B=(0<<ICNC3) | (0<<ICES3) | (0<<WGM33) | (0<<WGM32) | (0<<CS32) | (0<<CS31) | (0<<CS30);
TCNT3H=0x00;
TCNT3L=0x00;
ICR3H=0x00;
ICR3L=0x00;
OCR3AH=0x00;
OCR3AL=0x00;
OCR3BH=0x00;
OCR3BL=0x00;
OCR3CH=0x00;
OCR3CL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);
ETIMSK=(0<<TICIE3) | (0<<OCIE3A) | (0<<OCIE3B) | (0<<TOIE3) | (0<<OCIE3C) | (0<<OCIE1C);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Rising Edge
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
// INT3: On
// INT3 Mode: Rising Edge
// INT4: On
// INT4 Mode: Rising Edge
// INT5: On
// INT5 Mode: Rising Edge
// INT6: On
// INT6 Mode: Rising Edge
// INT7: On
// INT7 Mode: Rising Edge
EICRA=(1<<ISC31) | (1<<ISC30) | (0<<ISC21) | (0<<ISC20) | (1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00);
EICRB=(1<<ISC71) | (1<<ISC70) | (1<<ISC61) | (1<<ISC60) | (1<<ISC51) | (1<<ISC50) | (1<<ISC41) | (1<<ISC40);
EIMSK=(1<<INT7) | (1<<INT6) | (1<<INT5) | (1<<INT4) | (1<<INT3) | (0<<INT2) | (1<<INT1) | (1<<INT0);
EIFR=(1<<INTF7) | (1<<INTF6) | (1<<INTF5) | (1<<INTF4) | (1<<INTF3) | (0<<INTF2) | (1<<INTF1) | (1<<INTF0);

// USART0 initialization
// USART0 disabled
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (0<<RXEN0) | (0<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);

// USART1 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART1 Receiver: On
// USART1 Transmitter: Off
// USART1 Mode: Asynchronous
// USART1 Baud Rate: 9600 (Double Speed Mode)
UCSR1A=(0<<RXC1) | (0<<TXC1) | (0<<UDRE1) | (0<<FE1) | (0<<DOR1) | (0<<UPE1) | (1<<U2X1) | (0<<MPCM1);
UCSR1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (1<<RXEN1) | (0<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);
UCSR1C=(0<<UMSEL1) | (0<<UPM11) | (0<<UPM10) | (0<<USBS1) | (1<<UCSZ11) | (1<<UCSZ10) | (0<<UCPOL1);
UBRR1H=0x00;
UBRR1L=0x0C;

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 3
// D5 - PORTC Bit 4
// D6 - PORTC Bit 5
// D7 - PORTC Bit 6
// Characters/line: 16
lcd_init(16);

// Globally enable interrupts
#asm("sei")
       
      while(y<71)
      {   
       lcd_gotoxy(0,1);
       lcd_puts("go left loop");
       goleft(100,100);   
       k=0;
      }    
       delay_ms(500);
       linter=0;
     if(k==0)                 //going at N1
      {   
        lcd_gotoxy(0,1);
        lcd_puts("go forward loop");
        while(finter!=1)
         {
          goforward(170,110);
         }   
         stop();  
         while(finter!=0)
         {
         gobackward(150,80);
         }
           stop();
         while (finter!=1)
         {
         goforward(200,110);
         }
         // stop();
          k=1;
       } 

   while (1)
      {   
       update();
       PORTC.7=0;
       if((tz1==1)&&(finter==1))     //going to tz1 from N1   //PINE.6==1
       {   delay_ms(1000);
           lcd_gotoxy(0,1);
           lcd_printf("going tz1 via N1");  
           procedure1();  
       }        
       
       else if((tz1==1)&&(finter==2))     //going to tz1 from N2   //PINE.6==1
       {   delay_ms(1000);  
           lcd_gotoxy(0,1);
           lcd_printf("going tz1 via N2");
         while(finter!=0)
         {
           gobackward(120,80);           //to reach N1
         }  
          stop(); 
         while(finter!=1)
         {
          goforward(120,80);
         }  
           stop();
           procedure1();
       }   
           
       else if((finter==2)&&(tz2==1))        //going to TZ2 from N2     //PINF.6==1
       {   delay_ms(1000);
           lcd_gotoxy(0,1);
           lcd_printf("going tz2 via N2");   
           procedure1();
       }
             
       else if((finter==1)&&(tz2==1))         //going to TZ2 from N1
       {   delay_ms(1000);     
           lcd_gotoxy(0,1);
           lcd_printf("going tz2 via N1");    
        while(finter!=2)
        {
          goforward(105,80);       //to reach N2
        } 
          stop();
          procedure1();
       }   
             
       else if((tz3==1)&&(finter==2))        //going TZ3 from N2   //PINF.7==1
       {   delay_ms(1000);  
           lcd_gotoxy(0,1);
           lcd_printf("going tz3 via N2");     
           procedure2();
       }
          
       else if((tz3==1)&&(finter==1))             //going TZ3 from N1
       {   delay_ms(1000);      
           lcd_gotoxy(0,1);
           lcd_printf("going tz3 via N1");
         while(finter!=2)
         {
           goforward(105,80);
         } 
           stop();
           procedure2();
         }
         
        else
        {
        stop();
        }                      
      }
    }



 void procedure1()
   {       PORTC.7=1;
        while(linter!=1)
         {
          goleft(150,100);          //going to tz1 or tz2
         }
             
        while(linter!=2)
         {
          goleft(70,80); //70,80
         }  
         
        while(linter!=1)
         {
         comeback(80 ,80);          //adjusting at TZ1 ot TZ2....90,80
         } 
          stop(); 
          delay_ms(500);         
          //send a signal to launcher                            
          //while(finished!=1);   //write an interrupt code to make finished=1
          //finished=0;
          //here write the code to wait till the launch of shuttlecock TZ1 or TZ2  
         while(gozain!=1)        //pe7
         {
           PORTE.2=1;
          }
          PORTE.2=0; 
         // gozain=0; tz1=0; tz2=0; tz3=0; 
          delay_ms(500);  
          
         while(linter!=-1)      //comeback at neutral position 1
         {
          comeback(200,110);
         }
          stop(); 
          
         while(linter!=0)     //adjusting
         {
          goleft(140,100);
         }  
          stop(); 
          gozain=0; tz1=0; tz2=0; tz3=0; 
          
   } 


  void procedure2()
   {     PORTC.7=1;
         while(linter!=5)
           {
             goleft(150,100);
           }
         
         while(linter!=4)
           {
            comeback(80,80);          //adjusting at TZ3
           } 
             stop(); 
         //while(finished!=1);
         //finished=0;
         //here write the code to wait till the launch of shuttlecock TZ3
          delay_ms(500); 
          
        while(gozain!=1)        //pe7
          {
            PORTE.2=1;
          }
            PORTE.2=0;
        
           //gozain=0; tz1=0; tz2=0; tz3=0;
          
            delay_ms(500);
         while(linter!=-1)      //comeback at neutral position 2
         {
          comeback(200,110);
         }
         stop();
         
         while(linter!=0)     //adjusting
         {
          goleft(140,100);
         }
          stop();  
          gozain=0; tz1=0; tz2=0; tz3=0;
   }
   
     int goforward(int a,int b)
   {    
        update();
        PORTD.6=0;
        PORTD.7=1; 
        
        x=getchar1(); 
        
        er=35-x;
        p=kp*er;
        if(x<71)
        { 
        PORTF=0b01010000; OCR0=0;OCR1AL=0; //simply forward
                           OCR1BL=a;OCR1CL=a;   
          
          if(x<33)
          {  
           PORTF=0b01011010; OCR0=b+p;OCR1AL=b-p; //left
                             OCR1BL=a;OCR1CL=a;
          }  
          else if(x>38)
          { 
            PORTF=0b01010101; OCR0=b-p;OCR1AL=b+p; //right
                              OCR1BL=a;OCR1CL=a;
          }    
          else
          {
           PORTF=0b01010000;  OCR0=0;OCR1AL=0;
                              OCR1BL=a;OCR1CL=a;
          } 
        }  
        else 
        {
         PORTF=0b11111111; OCR0=255;OCR1AL=255;
                           OCR1BL=255;OCR1CL=255;
        }   
    }
         
  
     int gobackward(int a,int b)
    {     
        update();
        PORTD.6=0;
        PORTD.7=1; 
       
        x=getchar1(); 
        
        er=35-x;
        p=kp*er;
        if(x<71)
        { 
        PORTF=0b10100000; OCR0=0;OCR1AL=0; //simply forward
                           OCR1BL=a;OCR1CL=a;   
          
          if(x<33)
          {  
           PORTF=0b10101010; OCR0=b-p;OCR1AL=b+p; //left
                             OCR1BL=a;OCR1CL=a;
          }  
          else if(x>38)
          { 
            PORTF=0b10100101; OCR0=b+p;OCR1AL=b-p; //right
                              OCR1BL=a;OCR1CL=a;
          }    
          else
          {
           PORTF=0b10100000;  OCR0=0;OCR1AL=0;
                              OCR1BL=a;OCR1CL=a;
          } 
        }  
        else 
        {
         PORTF=0b11111111; OCR0=255;OCR1AL=255;
                           OCR1BL=255;OCR1CL=255;
        }
        }    
   
    
     int goleft(int a,int b)
    {    
        update();
        PORTD.7=0;
        PORTD.6=1; 
        
        
        y=getchar1(); 
        er=35-y;
        p=kp*er;
        if(y<71)
        { 
         PORTF=0b00001010; OCR0=a;OCR1AL=a; //simply forward
                           OCR1BL=0;OCR1CL=0;   
          
          if(y<33)
          {  
           PORTF=0b10101010; OCR0=a;OCR1AL=a; //left
                             OCR1BL=b+p;OCR1CL=b-p;
          }  
          else if(y>38)
          { 
            PORTF=0b01011010; OCR0=a;OCR1AL=a; //right
                              OCR1BL=b-p;OCR1CL=b+p;
          }    
          else
          {
           PORTF=0b00001010;  OCR0=a;OCR1AL=a;
                              OCR1BL=0;OCR1CL=0;
          } 
        }  
        else 
        {
         PORTF=0b11111111; OCR0=255;OCR1AL=255;
                           OCR1BL=255;OCR1CL=255;
        }   
    }
    
      int comeback(int a,int b)
    {    
        update();
        PORTD.7=0;
        PORTD.6=1; 
         
        y=getchar1(); 
        er=35-y;
        p=kp*er;
        if(y<71)
        { 
         PORTF=0b00000101; OCR0=a;OCR1AL=a; //comeback
                           OCR1BL=0;OCR1CL=0;   
          
          if(y<33)
          {  
           PORTF=0b10100101; OCR0=a;OCR1AL=a; //left
                             OCR1BL=b-p;OCR1CL=b+p;
          }  
          else if(y>38)
          { 
            PORTF=0b01010101; OCR0=a;OCR1AL=a; //right
                              OCR1BL=b+p;OCR1CL=b-p;
          }    
          else
          {
           PORTF=0b00000101;  OCR0=a;OCR1AL=a;
                              OCR1BL=0;OCR1CL=0;
          } 
        }  
        else 
        {
         PORTF=0b11111111; OCR0=255;OCR1AL=255;
                           OCR1BL=255;OCR1CL=255;
        }   
    }
    
     void stop()
    {    
      update();
      PORTF=0b11111111; OCR0=255;OCR1AL=255;
                     OCR1BL=255;OCR1CL=255;
      delay_ms(500);
    }
    
    void update()
    {      
      //  PORTD.6=1; 
      //  PORTD.7=0;
     // x=getchar1();
     //  itoa(x,ch);
     // lcd_gotoxy(0,0);
     // lcd_puts(ch);
      
       lcd_gotoxy(0,0);
        itoa(finter,f);
        lcd_puts(f);
         lcd_gotoxy(7,0);
        itoa(linter,l);
        lcd_puts(l); 
    }
