#include <PS2X_lib.h>
#include<Servo.h>
#define PS2_DAT        53
#define PS2_CMD        51
#define PS2_SEL        49
#define PS2_CLK        47
PS2X ps2x;
bool prg;
int error = 1;
float pwm = 255;
byte type = 0;
byte vibrate = 0;
int LX = 0, LY = 0, b = 0, f = 0, r = 0, l = 0, ef = 0, er = 0, left = 0, right = 0, L2 = 0, R2 = 0, i = 0;
int p1 = 8, p2 = 9, p3 = 10, p4 = 11;
int quad1 = 0, quad2 = 0, quad3 = 0, quad4 = 0;
int stop_flag = 0, flag = 0;
const int pistonP1 = 4;
const int pistonP2 = 5;
int rackBump = A6;
bool rackFlag = 0;
int steps = 0, angle = 0, spots_flag=0;
Servo clockwiseServo;
Servo anticlockwiseServo;

#define launcher1_steppin A10
#define launcher2_steppin A12
#define launcher3_steppin A14
#define launcher1_dirpin A11
#define launcher2_dirpin A13
#define launcher3_dirpin A15
#define yaw_steppin 35
#define yaw_dirpin 37

int spot1_red_pitch = 600;
int spot1_red_yaw = 600;
int spot2_red_pitch = 750;
int spot2_red_yaw = 750;
int spot3_red_pitch = 600;
int spot3_red_yaw = 600;
int spot4_red_pitch = 650;
int spot4_red_yaw = 650;
int spot4_blue_pitch = 650;
int spot4_blue_yaw = 650;


#define dirPin A3
#define stepPin A2
int rackAngle = 0;
int launcherAngle = 180;
int launcherSteps = 1000;
int stepsDelay = 50;
bool pistonFlag = 0;
void M110(int g) {
  digitalWrite(26, 1);
  digitalWrite(28, 0);
  analogWrite(p1, g);
}
void M101(int g) {
  digitalWrite(26, 0);
  digitalWrite(28, 1);
  analogWrite(p1, g);
}
void M210(int g) {
  digitalWrite(30, 1);
  digitalWrite(32, 0);
  analogWrite(p2, g);
}
void M201(int g) {
  digitalWrite(30, 0);
  digitalWrite(32, 1);
  analogWrite(p2, g);
}
void M310(int g) {
  digitalWrite(34, 1);
  digitalWrite(36, 0);
  analogWrite(p3, g);
}
void M301(int g) {
  digitalWrite(34, 0);
  digitalWrite(36, 1);
  analogWrite(p3, g);
}
void M410(int g) {
  digitalWrite(42, 1);
  digitalWrite(44, 0);
  analogWrite(p4, g);
}
void M401(int g) {
  digitalWrite(42, 0);
  digitalWrite(44, 1);
  analogWrite(p4, g);
}
void M1(int x, int y, int z)
{
  digitalWrite(30, x);
  digitalWrite(32, y);
  analogWrite(p1, z);
}
void M2(int x, int y, int z)
{
  digitalWrite(34, x);
  digitalWrite(36, y);
  analogWrite(p2, z);
}
void M3(int x, int y, int z)
{
  digitalWrite(38, x);
  digitalWrite(40, y);
  analogWrite(p3, z);
}
void M4(int x, int y, int z)
{
  digitalWrite(42, x);
  digitalWrite(44, y);
  analogWrite(p4, z);
}

void piston(int terminal_1, int terminal_2)
{
  digitalWrite(pistonP1, terminal_1);
  digitalWrite(pistonP2, terminal_2);
}
void dadelay(int d, int x, int y, int z, int w) {
  M1(0, 0, 0);
  M2(0, 0, 0);
  M3(0, 0, 0);
  M4(0, 0, 0);
  delay(d);
  quad1 = x;
  quad2 = y;
  quad3 = z;
  quad4 = x;
}

void setup() {

  Serial.begin (57600);
  while (error != 0)
    error = ps2x.config_gamepad(47, 51, 49, 53, false, false);
  type = ps2x.readType();
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(launcher1_steppin, OUTPUT);
  pinMode(launcher2_steppin, OUTPUT);
  pinMode(launcher3_steppin, OUTPUT);
  pinMode(launcher1_dirpin, OUTPUT);
  pinMode(launcher2_dirpin, OUTPUT);
  pinMode(launcher3_dirpin, OUTPUT);
  pinMode(yaw_steppin, OUTPUT);
  pinMode(yaw_dirpin,OUTPUT);

  L2 = ps2x.ButtonPressed(PSB_L2);
  R2 = ps2x.ButtonPressed(PSB_R2);
  LY = ps2x.Analog(PSS_LY);
  LX = ps2x.Analog(PSS_LX);
  left = ps2x.Button(PSB_L1);
  right = ps2x.Button(PSB_R1);

  pinMode(pistonP1, OUTPUT);
  pinMode(pistonP2, OUTPUT);

  digitalWrite(pistonP1, LOW);
  digitalWrite(pistonP2, HIGH);

  pinMode(rackBump, INPUT);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);



  clockwiseServo.attach(6);
  anticlockwiseServo.attach(3);

  clockwiseServo.write(90);
  anticlockwiseServo.write(90);
  L2 = ps2x.Button(PSB_L2);
  R2 = ps2x.Button(PSB_R2);
  LY = ps2x.Analog(PSS_LY);
  LX = ps2x.Analog(PSS_LX);
  left = ps2x.Button(PSB_L1);

}
void loop() {
  prg = ps2x.read_gamepad(false, vibrate);
  if (error == 0 and prg == 1)
  {
    ps2x.read_gamepad();
    right = ps2x.Button(PSB_R1);
    //int a[5] = {255, 127, 63};

    f = map(LY, 125, 0, 0, pwm);
    f = constrain(f, 0, pwm);
    b = map(LY, 130, 255, 0, pwm);
    b = constrain(b, 0, pwm);
    l = map(LX, 125, 0, 0, pwm);
    l = constrain(l, 0, pwm);
    r = map(LX, 130, 255, 0, pwm);
    r = constrain(r, 0, pwm);


    /*---------LOCOMOTION---------*/
    if (L2) {
      pwm = floor(pwm / 2);
      if (pwm < 63)pwm = 63;
    }
    if (R2) {
      pwm = floor((pwm * 2) + 1);
      if (pwm > 255)pwm = 255;
    }
    if (f >= 0 and r == 0 and l == 0 and b == 0) { //just fffffff
      stop_flag == 0;
      M110(f);
      M201(f);
      M310(f);
      M401(f);
      if (ps2x.Button(PSB_L1)) {
        M1(0, 1, pwm);
        M2(0, 1, pwm);
        M3(1, 0, pwm);
        M4(1, 0, pwm);
      }
      else if (ps2x.Button(PSB_R1)) {
        M1(1, 0, pwm);
        M2(1, 0, pwm);
        M3(0, 1, pwm);
        M4(0, 1, pwm);
      }
    }

    else if (f > 0 and r >= 0 and l <= 0 and b <= 0) { //first quadrant diagonal (f and r)
      stop_flag == 0;
      if (ps2x.Button(PSB_L1)) {
        M1(0, 1, pwm);
        M2(0, 1, pwm);
        M3(1, 0, pwm);
        M4(1, 0, pwm);
      }
      else if (ps2x.Button(PSB_R1)) {
        M1(1, 0, pwm);
        M2(1, 0, pwm);
        M3(0, 1, pwm);
        M4(0, 1, pwm);
      }
      else if (f = r) {
        if (quad1 == 0)
        {
          dadelay(150, 1, 0, 0, 0);
        }
        M110(f);
        M201(0);
        M310(f);
        M401(0);
      }
    }
    else if (l >= 0 and f == 0 and b == 0 and r == 0) { //just lllllll
      stop_flag == 0;
      M101(l);
      M201(l);
      M301(l);
      M401(l);
      if (ps2x.Button(PSB_L1)) {
        M1(0, 1, pwm);
        M2(0, 1, pwm);
        M3(1, 0, pwm);
        M4(1, 0, pwm);
      }
      else if (ps2x.Button(PSB_R1)) {
        M1(1, 0, pwm);
        M2(1, 0, pwm);
        M3(0, 1, pwm);
        M4(0, 1, pwm);
      }
    }
    else if (f >= 0 and l > 0 and b <= 0 and r <= 0) { //fourth quadrant diagonal (f and l)
      stop_flag == 0;
      if (ps2x.Button(PSB_L1)) {
        M1(0, 1, pwm);
        M2(0, 1, pwm);
        M3(1, 0, pwm);
        M4(1, 0, pwm);
      }
      else if (ps2x.Button(PSB_R1)) {
        M1(1, 0, pwm);
        M2(1, 0, pwm);
        M3(0, 1, pwm);
        M4(0, 1, pwm);
      }
      else if (f = l) {
        if (quad2 == 0)
        {
          dadelay(150, 0, 1, 0, 0);
        }
        M110(0);
        M201(f);
        M310(0);
        M401(f);
      }
    }
    else if (b >= 0 and f == 0 and l == 0 and r == 0) { //just bbbbbbb
      stop_flag == 0;
      M101(b);
      M210(b);
      M301(b);
      M410(b);
      if (ps2x.Button(PSB_L1)) {
        M1(0, 1, pwm);
        M2(0, 1, pwm);
        M3(1, 0, pwm);
        M4(1, 0, pwm);
      }
      else if (ps2x.Button(PSB_R1)) {
        M1(1, 0, pwm);
        M2(1, 0, pwm);
        M3(0, 1, pwm);
        M4(0, 1, pwm);
      }
    }
    else if (b > 0 and r >= 0 and l <= 0 and f <= 0) { //second quadrant diagonal (b and r)
      stop_flag == 0;
      if (ps2x.Button(PSB_L1)) {
        M1(0, 1, pwm);
        M2(0, 1, pwm);
        M3(1, 0, pwm);
        M4(1, 0, pwm);
      }
      else if (ps2x.Button(PSB_R1)) {
        M1(1, 0, pwm);
        M2(1, 0, pwm);
        M3(0, 1, pwm);
        M4(0, 1, pwm);
      }
      else if (b = r) {
        if (quad3 == 0)
        {
          dadelay(150, 0, 0, 1, 0);

        }
        M101(0);
        M210(b);
        M301(0);
        M410(b);
      }
    }
    else if (r >= 0 and l == 0 and b == 0 and f == 0) { //just rrrrrrr
      stop_flag == 0;
      M110(r);
      M210(r);
      M310(r);
      M410(r);
      if (ps2x.Button(PSB_L1)) {
        M1(0, 1, pwm);
        M2(0, 1, pwm);
        M3(1, 0, pwm);
        M4(1, 0, pwm);
        //Serial.println("leftt");
      }
      else if (ps2x.Button(PSB_R1)) {
        M1(1, 0, pwm);
        M2(1, 0, pwm);
        M3(0, 1, pwm);
        M4(0, 1, pwm);
      }
    }
    else if (b >= 0 and l > 0 and r <= 0 and f <= 0) { //third quadrant diagonal (b and l)
      stop_flag == 0;
      if (ps2x.Button(PSB_L1)) {
        M1(0, 1, pwm);
        M2(0, 1, pwm);
        M3(1, 0, pwm);
        M4(1, 0, pwm);
      }
      else if (ps2x.Button(PSB_R1)) {
        M1(1, 0, pwm);
        M2(1, 0, pwm);
        M3(0, 1, pwm);
        M4(0, 1, pwm);
      }
      else if (b = l) {
        if (quad4 == 0)
        {
          dadelay(150, 0, 0, 0, 1);

        }
        M101(b);
        M210(0);
        M301(b);
        M410(0);
      }
    }
    else if (ps2x.Button(PSB_R1)) {
      M110(pwm);
      M210(pwm);
      M310(pwm);
      M410(pwm);
    }
    else if (ps2x.Button(PSB_L1)) {
      M101(pwm);
      M201(pwm);
      M301(pwm);
      M401(pwm);
    }

    else {
      if (stop_flag == 0)
      {
        M1(1, 1, 0);
        M2(1, 1, 0);
        M3(1, 1, 0);
        M4(1, 1, 0);
        delay(150);
        stop_flag = 1;
      }
      else if (stop_flag == 1)
      {
        M1(1, 1, 255);
        M2(1, 1, 255);
        M3(1, 1, 255);
        M4(1, 1, 255);
      }
    }
    /*----------RACK AUTOMATION---------*/
    if (digitalRead(rackBump) == LOW && rackFlag == 0)
    {
      digitalWrite(dirPin, HIGH);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepsDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepsDelay);
    }
    if (digitalRead(rackBump) == HIGH)
    {
      launcherSteps = 0;
      rackFlag == 1;
    }
    if (ps2x.Button(PSB_CROSS))
    {
      piston(1, 0);
      digitalWrite(dirPin, LOW);
      for (steps = 0; steps < launcherSteps; steps++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(stepsDelay);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(stepsDelay);
      }
      for (angle = 0; angle < launcherAngle; angle++)
      {
        clockwiseServo.write(angle);
        anticlockwiseServo.write(180 - angle);
      }
      delay(100);
      piston(0, 0);
      rackFlag = 0;
    }

    /*---------LAUNCHER AUTOMATION--------*/

    if (spots_flag == 1)
    {
      digitalWrite(launcher1_dirpin, HIGH);
      for (steps = 0; steps < spot1_red_pitch; steps++)
      {
        digitalWrite(launcher1_steppin, HIGH);
        delay(500);
        digitalWrite(launcher1_steppin, LOW);
        delay(500);
      }
      digitalWrite(launcher1_dirpin, HIGH);
      for (steps = 0; steps < spot1_red_yaw; steps++)
      {
        digitalWrite(launcher1_steppin, HIGH);
        delay(500);
        digitalWrite(launcher1_steppin, LOW);
        delay(500);
      }
    }

    if (spots_flag == 2)
    {
      digitalWrite(launcher2_dirpin, HIGH);
      for (steps = 0; steps < spot4_red_pitch; steps++)
      {
        digitalWrite(launcher2_steppin, HIGH);
        delay(500);
        digitalWrite(launcher2_steppin, LOW);
        delay(500);
      }
      digitalWrite(launcher2_dirpin, HIGH);
      for (steps = 0; steps < spot4_red_yaw; steps++)
      {
        digitalWrite(launcher2_steppin, HIGH);
        delay(500);
        digitalWrite(launcher2_steppin, LOW);
        delay(500);
      }
    }


    if (spots_flag == 3)
    {
      digitalWrite(launcher3_dirpin, HIGH);
      for (steps = 0; steps < spot2_red_pitch; steps++)
      {
        digitalWrite(launcher3_steppin, HIGH);
        delay(500);
        digitalWrite(launcher3_steppin, LOW);
        delay(500);
      }
      digitalWrite(launcher3_dirpin, HIGH);
      for (steps = 0; steps < spot2_red_yaw; steps++)
      {
        digitalWrite(launcher3_steppin, HIGH);
        delay(500);
        digitalWrite(launcher3_steppin, LOW);
        delay(500);
      }
    }


    if (spots_flag == 4)
    {
      digitalWrite(launcher2_dirpin, HIGH);
      for (steps = 0; steps < spot3_red_pitch; steps++)
      {
        digitalWrite(launcher2_steppin, HIGH);
        delay(500);
        digitalWrite(launcher2_steppin, LOW);
        delay(500);
      }
      digitalWrite(launcher2_dirpin, HIGH);
      for (steps = 0; steps < spot3_red_yaw; steps++)
      {
        digitalWrite(launcher2_steppin, HIGH);
        delay(500);
        digitalWrite(launcher2_steppin, LOW);
        delay(500);
      }
    }
    if (spots_flag == 5)
    {
      digitalWrite(launcher1_dirpin, HIGH);
      for (steps = 0; steps < spot4_blue_pitch; steps++)
      {
        digitalWrite(launcher1_steppin, HIGH);
        delay(500);
        digitalWrite(launcher1_steppin, LOW);
        delay(500);
      }
      digitalWrite(launcher1_dirpin, HIGH);
      for (steps = 0; steps < spot4_blue_yaw; steps++)
      {
        digitalWrite(launcher1_steppin, HIGH);
        delay(500);
        digitalWrite(launcher1_steppin, LOW);
        delay(500);
      }
    }
    if (ps2x.ButtonPressed(PSB_CIRCLE))
    {
      spots_flag++;
      if (spots_flag > 5)spots_flag = 1;
    }


  }
  else {
    M1(1, 1, 255);
    M2(1, 1, 255);
    M3(1, 1, 255);
    M4(1, 1, 255);
  }
}
