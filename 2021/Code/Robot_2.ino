#include<Servo.h>
#include <PS2X_lib.h>

//Robotic arm pins



int Rarm_dir = 42 ;
int Rarm_pwm = 7;
int pwm = 255;
int Auto = 0;
int bump1pin = 23;
int bump2pin = 35;
int count = 0;

//Robotic arm pins
//Motorpins
int motor1DIR = 52;
int motor1PWM = 11;
int motor2DIR = 50;
int motor2PWM = 10;
int motor3DIR = 48;
int motor3PWM = 9;
int motor4DIR = 44;
int motor4PWM = 8;

const int launcher1DIR = 34 ;
const int launcher1PWM = 5;

int launcher2DIR = 38;
int launcher2PWM = 6;

int irPin = digitalRead(3);
int irPin2 = digitalRead(4);
int flag_1 = 0;
int flag_2 = 0;


int LX = 0, LY = 0, b = 0, f = 0,  r = 0, l = 0;
//Motorpins

int Sflag1 = 0, Sflag2 = 0, flag3 = 0, flag4 = 0;
//servo pins


//ps2 pins
#define PS2_DAT        53 //14    
#define PS2_CMD        51  //15
#define PS2_SEL        49  //16
#define PS2_CLK        47  //17
#define pressures   false
#define rumble      false

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;
//ps2 pins

void setup() {

  Serial.begin(9600);
  pinMode( motor1DIR, OUTPUT);
  pinMode( motor1PWM, OUTPUT);
  pinMode( motor2DIR, OUTPUT);
  pinMode( motor2PWM, OUTPUT);
  pinMode( motor3DIR, OUTPUT);
  pinMode( motor3PWM, OUTPUT);
  pinMode( motor4DIR, OUTPUT);
  pinMode( motor4PWM, OUTPUT);
  pinMode( Rarm_dir, OUTPUT);
  pinMode(Rarm_pwm, OUTPUT);

  

  pinMode(3, INPUT);
   pinMode(4, INPUT);

  pinMode(launcher1DIR, OUTPUT) ; //we have to set PWM pin as output
  pinMode(launcher1PWM, OUTPUT) ;//Logic pins are also set as output

  pinMode(launcher2DIR, OUTPUT) ; //we have to set PWM pin as output
  pinMode(launcher2PWM, OUTPUT) ;

 


  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

}
              
void loop() {

  
  if (error == 0)
  {
 ps2x.read_gamepad(false, vibrate);

 irPin = digitalRead(3);
 irPin2 = digitalRead(4);
 
 
   if ( irPin2 == 1 )

    {

      digitalWrite(launcher2DIR, LOW);
      analogWrite(launcher2PWM, 200);
     
    }

    if (irPin2 == 0 )
    {
        digitalWrite(launcher2DIR, LOW);
      analogWrite(launcher2PWM, 0);

    }

    if (ps2x.Button(PSB_CROSS))
     {
        if (irPin2 ==0 )
        {
        digitalWrite(launcher2DIR, LOW);
      analogWrite(launcher2PWM, 200);

        Serial.println("Arrow Shot");

       // flag_1 = 0;
       
      }
      }

     
    if (irPin == 1 && flag_1 == 0)
    {
      digitalWrite(launcher1DIR, LOW);
      analogWrite(launcher1PWM, 200);
     

     // flag_1 = 1;
      flag_2 = 0;

      Serial.println("Loading");
     
    }

    if (irPin == 0 && flag_2 == 0) {
      digitalWrite(launcher1DIR, LOW);
      analogWrite(launcher1PWM, 0);

      //flag_2 = 1;

      Serial.println("Loaded");

     
    }
   
      if (ps2x.Button(PSB_TRIANGLE))
      {
        if (irPin ==0 )
        {
        digitalWrite(launcher1DIR, LOW);
      analogWrite(launcher1PWM, 200);

        Serial.println("Arrow Shot");

        flag_1 = 0;
       
      }
      }


  if (ps2x.ButtonPressed(PSB_R1)) {
    pwm = pwm + 20;
    if (pwm > 255) {
      pwm = 255;
    }
    //Serial.println(pwm);
  }
  if (ps2x.ButtonPressed(PSB_L1)) {
    pwm = pwm - 20;
    if (pwm < 0) {
      pwm = 0;
    }
    //Serial.println(pwm);
  }


  int BP1 = digitalRead(bump1pin);

  int BP2 = digitalRead(bump2pin);

  LY = ps2x.Analog(PSS_RY);
  LX = ps2x.Analog(PSS_RX);
  f = map(LY, 127, 0, 0, pwm);
  f = constrain(f, 0, pwm);
  b = map(LY, 128, 255, 0, pwm);
  b = constrain(b, 0, pwm);
  l = map(LX, 127, 0, 0, pwm);
  l = constrain(l, 0, pwm);
  r = map(LX, 128, 255, 0, pwm);
  r = constrain(r, 0, pwm);

  //  Serial.print("    f-");
  //  Serial.print(f);
  //
  //  Serial.print("    b-");
  //  Serial.print(b);
  //
  //  Serial.print("    r-");
  //  Serial.print(r);
  //
  //  Serial.print("    l-");
  //  Serial.println(l);



  if (l > 40 && f > 40) {
    motor1(LOW, 127);
    motor2(LOW, 0);
    motor3(LOW, 127);
    motor4(HIGH, 0);
    Serial.println("-up");
  }
  else if (r > 40 && f > 40) {
    motor1(HIGH, 0);
    motor2(LOW, 127);
    motor3(LOW, 0);
    motor4(LOW, 127);
    Serial.println("+up");
  }
  else if (l > 40 && b > 40) {
    motor1(LOW, 0);
    motor2(HIGH, 127);
    motor3(HIGH, 0);
    motor4(HIGH, 127);
    Serial.println("-down");
  }
  else if (r > 40 && b > 40) {
    motor1(HIGH, 127);
    motor2(HIGH, 0);
    motor3(HIGH, 127);
    motor4(LOW, 0);
    Serial.println("+down");
  }
  else if (f > 40 && b < 10 && r < 10 && l < 10 ) {
    motor1(LOW, f);
    motor2(LOW, f);
    motor3(LOW, f);
    motor4(LOW, f);
    Serial.println("for");
  }
  else if (b > 40 && f < 10 && r < 10 && l < 10 ) {
    motor1(HIGH, b);
    motor2(HIGH, b);
    motor3(HIGH, b);
    motor4(HIGH, b);
    Serial.println("back");
  }
  else if (r > 40 && b < 10 && f < 10 && l < 10 ) {
    motor1(HIGH, r);
    motor2(LOW, r);
    motor3(HIGH, r);
    motor4(LOW, r);
    Serial.println("right");
  }
  else if (l > 40 && f < 10 && b < 10 && r < 10) {
    motor1(LOW, l);
    motor2(HIGH, l);
    motor3(LOW, l);
    motor4(HIGH, l);
    Serial.println("left");
  }
  else if (ps2x.Button(PSB_L2) )
  {

    motor1(LOW, 200);
    motor2(LOW, 200);
    motor3(HIGH,200);
    motor4(HIGH, 200);
    Serial.print("clockwise rotation");

  }

  else if (ps2x.Button(PSB_R2) )
  {
    motor1(HIGH, 200);
    motor2(HIGH, 200);
    motor3(LOW, 200);
    motor4(LOW, 200);
    Serial.print("clockwise rotation");
  }




  else  {
    motor1(LOW, 0);
    motor2(LOW, 0);
    motor3(LOW, 0);
    motor4(LOW, 0);

  }
}
}

void launcher1(int x , int y)
{
  digitalWrite(launcher1DIR, x);
  analogWrite(launcher1PWM, y);
}

void launcher2(int x , int y)
{
  digitalWrite(launcher2DIR, x);
  analogWrite(launcher2PWM, y);
}

void motor1(int one_a, int one_b) {
  digitalWrite(motor1DIR, one_a);
  analogWrite(motor1PWM, one_b);
}
void motor2(int two_a, int two_b) {
  digitalWrite(motor2DIR, two_a);
  analogWrite(motor2PWM, two_b);
}
void motor3(int three_a, int three_b) {
  digitalWrite(motor3DIR, three_a);
  analogWrite(motor3PWM, three_b);
}
void motor4(int four_a, int four_b) {
  digitalWrite(motor4DIR, four_a);
  analogWrite(motor4PWM, four_b);
}
