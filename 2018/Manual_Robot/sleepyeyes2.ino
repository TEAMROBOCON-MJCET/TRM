int xc = 0;
int ti = 0;
int za = 30;
int i = 0;
int lsa = 0, er = 0; float kp = 4, p = 0;
#include <PS2X_lib.h>  //for v1.6

#define PS2_DAT        50//14    53
#define PS2_CMD        51 //15    51
#define PS2_SEL        53//16    49
#define PS2_CLK        52      // 47

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;
int minVal = 265;
int maxVal = 402;
int an = 0, gi, az;

int x;
int y;
int z;
int o22, o11, o1, o2, o3, o4, o5, o6, o7;

void setup() {

  pinMode(34, OUTPUT);
  // set up the LCD's number of columns and rows:
  //lcd.begin(20, 4);
  //ps2 interfacing


 // Serial.begin(19200);
  Serial2.begin(9600);
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  type = ps2x.readType();

  pinMode(40, OUTPUT); //digital cytron

  pinMode(38, OUTPUT); //analog pwm cytron
  //inclination

  pinMode(36, OUTPUT); // digital
  pinMode(34, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(11, OUTPUT);
  // pushing citron

  pinMode(46, OUTPUT); pinMode(48, OUTPUT); pinMode(12, OUTPUT); //Left gripper
  pinMode(0, OUTPUT); pinMode(15, OUTPUT); pinMode(14, OUTPUT); //Right gripper
  //pinMode(42,OUTPUT);pinMode(44,OUTPUT);pinMode(11,OUTPUT);


  //extra pins for zaroorat
  pinMode(7, OUTPUT); pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(8, OUTPUT);


  pinMode(24, OUTPUT);
  digitalWrite(24, LOW);
}
 
void loop() {

  if (error == 0) //skip loop if no controller found
  {
    //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed


    if (ps2x.Analog(PSS_RY) >= 180 && ps2x.Button(PSB_PAD_DOWN))                      //Backward
    {
      o1 = map(ps2x.Analog(PSS_RY), 180, 255, 100, 255);
      digitalWrite(40, 1); digitalWrite(38, 0);
      analogWrite(10, o1); analogWrite(9, o1);
      digitalWrite(36, 0); digitalWrite(34, 0);
      analogWrite(8, 100); analogWrite(7, 100);
    }
    else if (ps2x.Analog(PSS_RY) >= 180 && ps2x.Button(PSB_PAD_UP))                      //Backward
    {
      o1 = map(ps2x.Analog(PSS_RY), 180, 255, 100, 255);
      digitalWrite(40, 1); digitalWrite(38, 0);
      analogWrite(10, o1); analogWrite(9, o1);
      digitalWrite(36, 1); digitalWrite(34, 1);
      analogWrite(8, 100); analogWrite(7, 100);
    }
    else if (ps2x.Analog(PSS_RY) <= 75 && ps2x.Button(PSB_PAD_UP)) //Forward //The Base OCR value has been changed from 60 to 75 so now the ranges has a resolution of 75
    {
      o1 = map(ps2x.Analog(PSS_RY), 75, 0, 100, 255);
      digitalWrite(40, 0); digitalWrite(38, 1);
      analogWrite(10, o1); analogWrite(9, o1);
      digitalWrite(36, 1); digitalWrite(34, 1);
      analogWrite(8, 100); analogWrite(7, 100);
    }
    else if (ps2x.Analog(PSS_RY) <= 75 && ps2x.Button(PSB_PAD_DOWN)) //Forward //The Base OCR value has been changed from 60 to 75 so now the ranges has a resolution of 75
    {
      o1 = map(ps2x.Analog(PSS_RY), 75, 0, 100, 255);
      digitalWrite(40, 0); digitalWrite(38, 1);
      analogWrite(10, o1); analogWrite(9, o1);
      digitalWrite(36, 0); digitalWrite(34, 0);
      analogWrite(8, 100); analogWrite(7, 100);
    }
    else if (ps2x.Analog(PSS_RY) >= 180)                      //Backward
    {
      o1 = map(ps2x.Analog(PSS_RY), 180, 255, 100, 255);
      digitalWrite(40, 1); digitalWrite(38, 0);
      analogWrite(10, o1); analogWrite(9, o1);
    }
    else if (ps2x.Analog(PSS_RY) <= 75) //Forward //The Base OCR value has been changed from 60 to 75 so now the ranges has a resolution of 75
    {
      o1 = map(ps2x.Analog(PSS_RY), 75, 0, 100, 255);
      digitalWrite(40, 0); digitalWrite(38, 1);
      analogWrite(10, o1); analogWrite(9, o1);
    }
    else if ((ps2x.Analog(PSS_LX)) <= 75) //Left lateral/strafe
    {
      o2 = map(ps2x.Analog(PSS_LX), 75, 0, 100, 255);
      digitalWrite(34, 1);
      digitalWrite(36, 0);
      xc = o2 + 20;
      analogWrite(7, o2); analogWrite(8, o2);
    }
    else if ((ps2x.Analog(PSS_LX)) >= 180) //Right lateral/strafe
    {
      o2 = map(ps2x.Analog(PSS_LX), 180, 255, 100, 255);
      digitalWrite(34, 0);
      digitalWrite(36, 1);
      analogWrite(7, o2); analogWrite(8, o2);
    }

    else if (ps2x.Button(PSB_PAD_DOWN))
    {
      digitalWrite(36, 0); digitalWrite(34, 0);
      analogWrite(8, 210); analogWrite(7, 210);
    }
    else if (ps2x.Button(PSB_PAD_UP))
    {
      digitalWrite(36, 1); digitalWrite(34, 1);
      analogWrite(8, 210); analogWrite(7, 210);
    }
    else if (ps2x.Button(PSB_PAD_LEFT))  //Grippers move left
    {
      digitalWrite(46, HIGH);
      digitalWrite(48, LOW);
      analogWrite(12, 90);
    }
    else if (ps2x.Button(PSB_PAD_RIGHT))  //Grippers move right
    { 
      digitalWrite(46, LOW);
      digitalWrite(48, HIGH);
      analogWrite(12, 90);
    }
    else if (ps2x.Button(PSB_TRIANGLE)) //gripper middle open  buttonpressed
    {
      digitalWrite(14, LOW);
    }
    else if (ps2x.Button(PSB_CROSS))   //all grippers close
    {
      digitalWrite(15, HIGH);
      digitalWrite(0, HIGH);
      digitalWrite(14, HIGH);
    }
    else if (ps2x.Button(PSB_SQUARE))  //gripper left open
    {
      digitalWrite(0, LOW);
    }
    else if (ps2x.Button(PSB_CIRCLE)) //gripper right open
    {
      digitalWrite(15, LOW);
    }




    //******************************Semi autonomous region"




    else if (ps2x.Button(PSB_L2))  //forward and lin followin
    {

       digitalWrite(40, 0); digitalWrite(38, 1);
      analogWrite(10, 160); analogWrite(9, 210);
      Serial.println("L2");
      digitalWrite(24, LOW);
      if (Serial2.available() > 0)
      {

        lsa = Serial2.read();
        if (lsa < 70)
        {
          er = 35 - lsa;
          p = kp * er;

          if (lsa > 40) //adjusting bot,moving right
          {

            digitalWrite(34, 0);
            digitalWrite(36, 1);
            analogWrite(7,130 +p);
            analogWrite(8,100+p);
          }
          else if (lsa < 30) //adjusting bot,moving left
          {
            digitalWrite(34, 1);
            digitalWrite(36, 0);
            analogWrite(7, 130+ p);
            analogWrite(8, 100+p );        //down wheel
          }
          else
          {

            digitalWrite(34, 0); //bot shoud not move anywhere
            digitalWrite(36, 0);
            analogWrite(7, 0);
            analogWrite(8, 0);
          }
        }
        else
        {
          digitalWrite(34, 0); //bot shoud not move anywhere
          digitalWrite(36, 0);
          analogWrite(7, 0);
          analogWrite(8, 0);
        }
      }
    }


    else
    {
      analogWrite(10, 0);
      analogWrite(9, 0);
      analogWrite(12, 0);
      analogWrite(8, 0);
      analogWrite(7, 0);
      analogWrite(11, 0);
    }
  }
}
