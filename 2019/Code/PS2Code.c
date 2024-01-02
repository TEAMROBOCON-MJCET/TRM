/*******************************************************
  This program was created by the CodeWizardAVR V3.33
  Automatic Program Generator
  © Copyright 1998-2018 Pavel Haiduc, HP InfoTech s.r.l.
  http://www.hpinfotech.com

  Project :Ps2withatmega8
  Version :18.0.5
  Date    : 9/19/2018
  Author  :AsadZeeshan
  Company :
  Comments:


  Chip type               : ATmega8A
  Program type            : Application
  AVR Core Clock frequency: 1.000000 MHz
  Memory model            : Small
  External RAM size       : 0
  Data Stack size         : 256
**************************` *****************************/

#include<mega8.h>
#include<spi.h>
#include<alcd.h>
#include<io.h>
#include<stdio.h>
#include<delay.h>
#include<stdlib.h>
intdata0,data1,data2,data3,data4,data5,a,b,c,d;
unsignedcharx[10],y[10],z[10],g[10],h[10],f[10];

#defineDATA_REGISTER_EMPTY(1<<UDRE)
#defineRX_COMPLETE(1<<RXC)
#defineFRAMING_ERROR(1<<FE)
#definePARITY_ERROR(1<<UPE)
#defineDATA_OVERRUN(1<<DOR)
#pragmaused-
#define_ALTERNATE_PUTCHAR_
#pragmaused+
voidputchar(charc)
{
  while((UCSRA&DATA_REGISTER_EMPTY)==0);
  UDR=c;
}

voidmain(void)
{
  // Input/Output Ports initialization
  // Port B initialization
  // Function: Bit7=In Bit6=In Bit5=Out Bit4=In Bit3=Out Bit2=Out Bit1=In Bit0=In
  DDRB=(0<<DDB7)|(0<<DDB6)|(1<<DDB5)|(0<<DDB4)|(1<<DDB3)|(1<<DDB2)|(0<<DDB1)|(0<<DDB0);
  // State: Bit7=T Bit6=T Bit5=0 Bit4=T Bit3=0 Bit2=0 Bit1=T Bit0=T
  PORTB=(0<<PORTB7)|(0<<PORTB6)|(0<<PORTB5)|(0<<PORTB4)|(0<<PORTB3)|(0<<PORTB2)|(0<<PORTB1)|(0<<PORTB0);

  // Port C initialization
  // Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
  DDRC=(0<<DDC6)|(0<<DDC5)|(0<<DDC4)|(0<<DDC3)|(0<<DDC2)|(0<<DDC1)|(0<<DDC0);
  // State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
  PORTC=(0<<PORTC6)|(0<<PORTC5)|(0<<PORTC4)|(0<<PORTC3)|(0<<PORTC2)|(0<<PORTC1)|(0<<PORTC0);

  // Port D initialization
  // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
  DDRD=(0<<DDD7)|(0<<DDD6)|(0<<DDD5)|(0<<DDD4)|(0<<DDD3)|(0<<DDD2)|(0<<DDD1)|(0<<DDD0);
  // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
  PORTD=(0<<PORTD7)|(0<<PORTD6)|(0<<PORTD5)|(0<<PORTD4)|(0<<PORTD3)|(0<<PORTD2)|(0<<PORTD1)|(0<<PORTD0);

  // Timer/Counter 0 initialization
  // Clock source: System Clock
  // Clock value: Timer 0 Stopped
  TCCR0=(0<<CS02)|(0<<CS01)|(0<<CS00);
  TCNT0=0x00;

  // Timer/Counter 1 initialization
  // Clock source: System Clock
  // Clock value: Timer1 Stopped
  // Mode: Normal top=0xFFFF
  // OC1A output: Disconnected
  // OC1B output: Disconnected
  // Noise Canceler: Off
  // Input Capture on Falling Edge
  // Timer1 Overflow Interrupt: Off
  // Input Capture Interrupt: Off
  // Compare A Match Interrupt: Off
  // Compare B Match Interrupt: Off
  TCCR1A=(0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10);
  TCCR1B=(0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(0<<WGM12)|(0<<CS12)|(0<<CS11)|(0<<CS10);
  TCNT1H=0x00;
  TCNT1L=0x00;
  ICR1H=0x00;
  ICR1L=0x00;
  OCR1AH=0x00;
  OCR1AL=0x00;
  OCR1BH=0x00;
  OCR1BL=0x00;

  // Timer/Counter 2 initialization
  // Clock source: System Clock
  // Clock value: Timer2 Stopped
  // Mode: Normal top=0xFF
  // OC2 output: Disconnected
  ASSR=0<<AS2;
  TCCR2=(0<<PWM2)|(0<<COM21)|(0<<COM20)|(0<<CTC2)|(0<<CS22)|(0<<CS21)|(0<<CS20);
  TCNT2=0x00;
  OCR2=0x00;

  // Timer(s)/Counter(s) Interrupt(s) initialization
  TIMSK=(0<<OCIE2)|(0<<TOIE2)|(0<<TICIE1)|(0<<OCIE1A)|(0<<OCIE1B)|(0<<TOIE1)|(0<<TOIE0);

  // External Interrupt(s) initialization
  // INT0: Off
  // INT1: Off
  MCUCR=(0<<ISC11)|(0<<ISC10)|(0<<ISC01)|(0<<ISC00);

  // USART initialization
  // Communication Parameters: 8 Data, 1 Stop, No Parity
  // USART Receiver: On
  // USART Transmitter: On
  // USART Mode: Asynchronous
  // USART Baud Rate: 9600 (Double Speed Mode)
  UCSRA=(0<<RXC)|(0<<TXC)|(0<<UDRE)|(0<<FE)|(0<<DOR)|(0<<UPE)|(1<<U2X)|(0<<MPCM);
  UCSRB=(0<<RXCIE)|(0<<TXCIE)|(0<<UDRIE)|(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2)|(0<<RXB8)|(0<<TXB8);
  UCSRC=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);
  UBRRH=0x00;
  UBRRL=0x0C;

  // Analog Comparator initialization
  // Analog Comparator: Off
  // The Analog Comparator's positive input is
  // connected to the AIN0 pin
  // The Analog Comparator's negative input is
  // connected to the AIN1 pin
  ACSR=(1<<ACD)|(0<<ACBG)|(0<<ACO)|(0<<ACI)|(0<<ACIE)|(0<<ACIC)|(0<<ACIS1)|(0<<ACIS0);
  SFIOR=(0<<ACME);

  // ADC initialization
  // ADC disabled
  ADCSRA=(0<<ADEN)|(0<<ADSC)|(0<<ADFR)|(0<<ADIF)|(0<<ADIE)|(0<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);

  // SPI initialization
  // SPI Type: Master
  // SPI Clock Rate: 2*15.625 kHz
  // SPI Clock Phase: Cycle Half
  // SPI Clock Polarity: High
  // SPI Data Order: LSB First
  SPCR=(0<<SPIE)|(1<<SPE)|(1<<DORD)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<SPR1)|(0<<SPR0);
  SPSR=(1<<SPI2X);

  // TWI initialization
  // TWI disabled
  TWCR=(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWEN)|(0<<TWIE);

  // Alphanumeric LCD initialization
  // Connections are specified in the
  // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
  // RS - PORTB Bit 6
  // RD - PORTB Bit 7
  // EN - PORTD Bit 5
  // D4 - PORTD Bit 6
  // D5 - PORTD Bit 7
  // D6 - PORTB Bit 0
  // D7 - PORTB Bit 1
  // Characters/line: 16
  lcd_init(16);
  while(1)
  {

    while(d!=0x73)
    {

      PORTB|=(1<<PORTB3)|(1<<PORTB5);//set

      PORTB&=~(1<<PORTB2);//clr
      //config mode
      spi(0x01);
      spi(0x43);
      spi(0x00);
      spi(0x01);

      spi(0x00);

      PORTB|=(1<<PORTB3);
      delay_ms(1);
      PORTB|=(1<<PORTB2);

      delay_ms(10);


      PORTB|=(1<<PORTB3)|(1<<PORTB5);

      PORTB&=~(1<<PORTB2);

      spi(0x01);
      spi(0x44);
      spi(0x00);                                 //analogmode
      spi(0x01);
      spi(0x03);
      spi(0x00);
      spi(0x00);
      spi(0x00);
      spi(0x00);

      PORTB|=(1<<PORTB3);
      delay_ms(1);
      PORTB|=(1<<PORTB2);
      delay_ms(10);

      PORTB|=(1<<PORTB3)|(1<<PORTB5);
      PORTB&=~(1<<PORTB2);

      spi(0x01);
      spi(0x43);
      spi(0x00);
      spi(0x00);
      spi(0x5A);
      spi(0x5A);                               //exitconfig
      spi(0x5A);
      spi(0x5A);
      spi(0x5A);

      PORTB|=(1<<PORTB3);
      delay_ms(1);
      PORTB|=(1<<PORTB2);
      delay_ms(10);




      PORTB|=(1<<PORTB3)|(1<<PORTB5);
      PORTB&=~(1<<PORTB2);
      spi(0x01);
      d=spi(0x42);
      spi(0x00);
      spi(0x00);
      spi(0x00);
      spi(0x00);                                   //ack
      spi(0x00);
      spi(0x00);
      spi(0x00);



      PORTB|=(1<<PORTB3);
      delay_ms(1);
      PORTB|=(1<<PORTB2);
      delay_ms(10);

    }


    while(d==0x73)
    {




      PORTB|=(1<<PORTB3)|(1<<PORTB5);
      PORTB&=~(1<<PORTB2);
      a=spi(0x01);
      b=spi(0x42);
      c=spi(0x00);


      data0=spi(0x00);//buttons set 1 8
      data1=spi(0x00);//button set 2  8
      data2=spi(0x00);//  rx     0 right 255
      data3=spi(0x00);//  ry     0 down  255
      data4=spi(0x00);//  lx
      data5=spi(0x00);//  ly

      delay_us(10);
      PORTB|=(1<<PORTB3);
      delay_us(10);
      PORTB|=(1<<PORTB2);
      /**********************************************************************/
      //       //data0 for arrow keys set
      //       //data1 for square,circle,triangle,cross,l1,l2,r1,r2
      //       //data2 right stick(x)
      //       //data3 left stick(y)
      //       //data4 right stick(y)
      //       //data5 left stick(x)

      if(data0==0xDF)
      {
        putchar('R');     //right arrow
      }

      elseif(data0==0x7F)//left arrow
        putchar('L');

      elseif(data0==0xEF)//arrow up
        putchar('U');

      elseif(data0==0xBF)//arrow down
        putchar('D');


      elseif(data1==0xDF)
      {
        putchar('O');     //circle
      }

      elseif(data1==0x7F)//square
        putchar('Q');

      elseif(data1==0xEF)//arrow up
        putchar('T');
      elseif(data1==0xBF)//cross
        putchar('X');
      elseif(data1==0xF7)
      {
        putchar('r');     //R1
      }

      elseif(data1==0xFD)//R2
        putchar('p');
      elseif(data1==0xFB)
      {
        putchar('l');     //L1
      }

      elseif(data1==0xFE)//L2
        putchar('q');

      //sticks
      elseif(data3<81)
      {
        itoa(data3,x);      //right joystick up
        puts(x);
      }
      elseif(data3>174)//right joystick down
      {
        itoa(data3,x);
        puts(x);
      }
      elseif(data4<81)//left joystick left
      {

        data4=data4+625;
        itoa(data4,x);
        puts(x);
      }
      elseif(data4>174)
      {
        data4=data4+540;  //left joystick right
        itoa(data4,x);
        puts(x);
      }
      elseif(data2<81)
      {
        data2=data2+265;
        itoa(data2,x);
        puts(x);            //right joystick left
      }
      elseif(data2>174)//right joystick right
      {
        data2=data2+180;
        itoa(data2,x);
        puts(x);
      }
      elseif(data5<81)
      {
        data5=data5+445;
        itoa(data5,x);
        puts(x);            //left joystick up
      }
      elseif(data5>174)//left joystick down
      {
        data5=data5+360;
        itoa(data5,x);
        puts(x);
      }

    }

  }
}
