#include <PS2X_lib.h>
#define PS2_DAT       53
#define PS2_CMD       51
#define PS2_SEL       49
#define PS2_CLK       47
#define pressures   false
#define rumble      false
int motor1a = 48, motor1b = 46, pwm1 = 12;
int motor2a = 44, motor2b = 42, pwm2 = 11;
int motor3a = 40, motor3b = 38, pwm3 = 10;
int motor4a = 34, motor4b = 36, pwm4 = 9;
int motor5a = 30, motor5b = 32, pwm5 = 8;
int pneumatic = 31, pneumatic_low = 33;
bool flag = 0;
int dist1, dist2;
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;
int passEncoderPin1 = 2;
int passEncoderPin2 = 3;
int kickEncoderPin1 = 18;
int kickEncoderPin2 = 19;
volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
volatile int lastEncoded1 = 0;
volatile int lastEncoded2 = 0;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial3.write(0);
  Serial3.write(128);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  type = ps2x.readType();
  pinMode(kickEncoderPin1, INPUT);
  pinMode(kickEncoderPin2, INPUT);
  digitalWrite(kickEncoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(kickEncoderPin2, HIGH); //turn pullup resistor on
  pinMode(passEncoderPin1, INPUT);
  pinMode(passEncoderPin2, INPUT);
  digitalWrite(passEncoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(passEncoderPin2, HIGH); //turn pullup resistor on
//  attachInterrupt(digitalPinToInterrupt(kickEncoderPin1), updateEncoder1, CHANGE);
//  attachInterrupt(digitalPinToInterrupt(kickEncoderPin2), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(passEncoderPin1), updateEncoder2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(passEncoderPin2), updateEncoder2, CHANGE);
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(motor3a, OUTPUT);
  pinMode(motor3b, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(motor4a, OUTPUT);
  pinMode(motor4b, OUTPUT);
  pinMode(pwm4, OUTPUT);
  pinMode(motor5a, OUTPUT);
  pinMode(motor5b, OUTPUT);
  pinMode(pwm5, OUTPUT);
  pinMode(pneumatic, OUTPUT);
  pinMode(pneumatic_low, OUTPUT);
}

void loop()
{
  if (error == 0) //skip loop if no controller found
  {
    ps2x.read_gamepad(false, vibrate);
    Serial.println(encoderValue2);


    
    if (ps2x.Button(PSB_CROSS))                                                  //Kick ke liye set
    {
      Serial3.write(90);
      Serial.println("move down");
      if (ps2x.Button(PSB_L2))
      {
        digitalWrite(pneumatic, LOW);
        digitalWrite(pneumatic_low, LOW);
        Serial.println("rel");    
        delay(50);
      }
      else if (ps2x.Button(PSB_R2))
      {
        digitalWrite(pneumatic, HIGH);
        digitalWrite(pneumatic_low, LOW);
        Serial.println("grab");
        delay(50);
      }
    }


    else if (ps2x.Button(PSB_SQUARE))                                             //throw during pasiing
    {
      while(encoderValue2 > -590)
      {
      Serial3.write(63);
      Serial.println("pass");
      if (encoderValue2 < -590)
      {
        digitalWrite(pneumatic, HIGH);
        digitalWrite(pneumatic_low, LOW);
        Serial.println("rel");
        Serial3.write(30);
        delay(80);
        Serial3.write(0);
        delay(50);
        Serial3.write(70);
        delay(100);
        Serial3.write(0);
       }
        
    }
    }


    else if (ps2x.Button(PSB_TRIANGLE))                                                //Passing
    {
      Serial3.write(20);
      Serial.println("upward");
      Serial.println(encoderValue2);
      delay(50);
    }

    
    else if (ps2x.Button(PSB_L2))                                         //Passing ke liye set
    {
      digitalWrite(pneumatic, LOW);
      digitalWrite(pneumatic_low, LOW);
      Serial.println("r1");
      delay(50);
    }
    else if (ps2x.Button(PSB_R2))                                         //Passing ke liye set
    {
      digitalWrite(pneumatic, HIGH);
      digitalWrite(pneumatic_low, LOW);
      Serial.println("r2");
      delay(50);
    }
    else
    {
      Serial3.write(0);
      Serial3.write(128);
    }


  }
  else
  {
    Serial.println("stop_controller");
    Serial3.write(0);
    Serial3.write(128);
  }
}


void updateEncoder2()
{
  int MSB = digitalRead(passEncoderPin1); //MSB = most significant bit
  int LSB = digitalRead(passEncoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded2 << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue2 ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue2 --;

  lastEncoded2 = encoded; //store this value for next time
}
