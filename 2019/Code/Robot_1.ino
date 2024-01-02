#include<PS2X_lib.h>
#definePS2_DAT       53
#definePS2_CMD       51
#definePS2_SEL       49
#definePS2_CLK       47
#definepressures   false
#definerumble      false

PS2Xps2x;
int  w=0;
interror=0;
bytetype=0;
bytevibrate=0;
intencoderPinR1=18;//Channel A
intencoderPinR2=19;//Channel B
intencoderPin1=20;//Channel A
intencoderPin2=21;//Channel B
volatileintlastEncoded=0;
volatilelongev=0,count=0;
voidsetup()
{
  // put your setup code here, to run once:
  Serial.begin(57600);
  error=ps2x.config_gamepad(PS2_CLK,PS2_CMD,PS2_SEL,PS2_DAT,pressures,rumble);
  type=ps2x.readType();

  digitalWrite(encoderPin1,HIGH);//turn pullup resistor on
  digitalWrite(encoderPin2,HIGH);//turn pullup resistor on
  digitalWrite(encoderPinR1,HIGH);//turn pullup resistor on
  digitalWrite(encoderPinR2,HIGH);//turn pullup resistor on
  attachInterrupt(digitalPinToInterrupt(18),pull,CHANGE);
  attachInterrupt(digitalPinToInterrupt(19),pull,CHANGE);
  attachInterrupt(digitalPinToInterrupt(20),updateEncoder,CHANGE);
  attachInterrupt(digitalPinToInterrupt(21),updateEncoder,CHANGE);
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);
  pinMode(40,OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
}

voidloop()
{
  if(error==0)//skip loop if no controller found
  {
    ps2x.read_gamepad(false,vibrate);
    inty=ps2x.Analog(PSS_RY);
    intx=ps2x.Analog(PSS_LX);
    intr=map(x,127,255,0,255);
    intb=map(y,127,255,0,255);
    intl=map(x,0,126,255,0);
    intf=map(y,0,126,255,0);


    if(x>=180)//right
    {
      Serial.println(r);
      Serial.println("right");
      mot1(0,1,r);
      mot2(0,1,r);
      mot3(1,0,r);
      mot4(1,0,r);
    }

    elseif(x<=100)//left
    {
      Serial.println(l);
      Serial.println("left");
      mot1(1,0,l);
      mot2(1,0,l);
      mot3(0,1,l);
      mot4(0,1,l);
    }

    elseif(y<=100)//forward
    {
      Serial.println(f);
      Serial.println("forward");
      mot1(0,1,f);
      mot2(1,0,f);
      mot3(1,0,f);
      mot4(0,1,f);
    }

    elseif(y>180)//backward
    {
      Serial.println(b);
      Serial.println("back");
      mot1(1,0,b);
      mot2(0,1,b);
      mot3(0,1,b);
      mot4(1,0,b);
    }

    else  if(ps2x.Button(PSB_PAD_RIGHT))
    {
      mot1(0,1,125);
      mot2(0,1,125);
      mot3(0,1,125);
      mot4(0,1,125);
    }

    elseif(ps2x.Button(PSB_PAD_LEFT))
    {
      mot1(1,0,125);
      mot2(1,0,125);
      mot3(1,0,125);
      mot4(1,0,125);
    }


    elseif(ps2x.Button(PSB_PAD_UP))//lift
      mot_e(0,1,210);


    else  if(ps2x.Button(PSB_PAD_DOWN))//return
      mot_e(1,0,160);

    else  if(ps2x.Button(PSB_L1)&&w==1)//lift
    {
      mot_p(1,0);
      while(ev<=0&&ev>-810)
      {
        while(ev<=0&&ev>-680)
        {
          mot_e(0,1,210);
        }
        while(ev<-670&&ev>-810)
        {
          mot_e(0,1,40);
        }
        w=0;
      }
    }


    else  if(ps2x.Button(PSB_R1)&&w==0)//return
    {
      while(ev<840&&ev>=0)
      {
        while(ev>=0&&ev<200)
        {
          mot_e(1,0,90);
        }
        while(ev>200&&ev<850)
        {
          mot_e(1,0,40);
        }
        w=1;
      }
    }


    else  if(ps2x.Button(PSB_CROSS)
  {
    while(count>=-13100)
      {
        mot_r(0,1,255);//wind
      }
    }

    else  if(ps2x.Button(PSB_TRIANGLE))
  {
    while(count<=13200)
      {
        mot_r(1,0,255);//unwwind
      }
    }

    else  if(ps2x.Button(PSB_CIRCLE))
    mot_r(0,1,255);//wind

    else  if(ps2x.Button(PSB_SQUARE))
      mot_r(1,0,255);//unwind


      else  if(ps2x.Button(PSB_R2))
        mot_t(1,0);

        else  if(ps2x.Button(PSB_L2))
          mot_t(0,1);


          else//stop
          {
            count=0;
            ev=0;
            mot1(1,1,255);
            mot2(1,1,255);
            mot3(1,1,255);
            mot4(1,1,255);
            mot_e(0,0,255);
            mot_r(0,0,255);
            mot_p(0,0);
            mot_t(0,1);
           }
  }
}

voidmot1(intp,intq,intr)
{
  digitalWrite(48,p);
  digitalWrite(46,q);
  analogWrite(12,r);
}

voidmot2(intp,intq,intr)
{
  digitalWrite(44,p);
  digitalWrite(42,q);
  analogWrite(11,r);
}

voidmot3(intp,intq,intr)
{
  digitalWrite(40,p);
  digitalWrite(38,q);
  analogWrite(10,r);
}

voidmot4(intp,intq,intr)
{
  digitalWrite(36,p);
  digitalWrite(34,q);
  analogWrite(9,r);
}

voidmot_e(intp,intq,intr)
{
  digitalWrite(32,p);
  digitalWrite(30,q);
  analogWrite(8,r);
}


voidmot_p(intp,intq)
{
  digitalWrite(45,p);
  digitalWrite(43,q);
}

voidmot_t(intp,intq)
{
  digitalWrite(41,p);
  digitalWrite(39,q);
}

voidmot_r(intp,intq,intr)
{
  digitalWrite(31,p);
  digitalWrite(33,q);
  analogWrite(7,r);
}


voidupdateEncoder()
{
  intMSB=digitalRead(encoderPin1);//MSB = most significant bit
  intLSB=digitalRead(encoderPin2);//LSB = least significant bit

  intencoded=(MSB<<1)|LSB;//converting the 2 pin value to single number
  intsum  =(lastEncoded<<2)|encoded;//adding it to the previous  value

  if(sum==0b1101||sum==0b0100||sum==0b0010||sum==0b1011)ev++;
  if(sum==0b1110||sum==0b0111||sum==0b0001||sum==0b1000)ev--;
  lastEncoded=encoded;//store this value for next time
}

voidpull()
{
  intMSB=digitalRead(encoderPinR1);//MSB = most significant bit
  intLSB=digitalRead(encoderPinR2);//LSB = least significant bit

  intencoded=(MSB<<1)|LSB;//converting the 2 pin value to single number
  intsum  =(lastEncoded<<2)|encoded;//adding it to the previous value

  if(sum==0b1101||sum==0b0100||sum==0b0010||sum==0b1011)count++;
  if(sum==0b1110||sum==0b0111||sum==0b0001||sum==0b1000)count--;
  lastEncoded=encoded;//store this value for next time
}
