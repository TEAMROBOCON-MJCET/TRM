#include <SoftwareSerial.h>
#include <math.h>
 
#define packet_size 68
#define track_error_percent 5
#define theta_error_percent 7
 
unsigned int stepsw = 0;
double sin_phi, cos_phi;
double delta [4] = {0.0, 0.0, 0.0, 0.0};
double final_data [5];
double distance, distance1, track_length, heading = 0.0;
double dx [5];
double x_sw [5]={0,0,0,0,0};
int bytedata, bytedata_usb;
byte ack [5] = {0, 1, 2, 3, 4};
int line[packet_size];
uint8_t header[4]={0,0,0,0};
int newbyte = -1;
int x [4]={0,0,0,0};
int y [4]={0,0,0,0};
int z [4]={0,0,0,0};
int h [4]={0,0,0,0};
int steps[2]={0,0};
bool flag_f, flag_b = false;
unsigned int j, k, l, package_number, package_number_old, datacount = 0;
int nturn=0;
float theta;
double track;
double data_array[]= {0.5,70,0.5,70,0.5,70,0.5,70,0,0};
int data_array1[]= {};
int r, count=0;
typedef unsigned char uchar;
 
const int w_cmd[3] = {0x34, 0x00, 0x34};
//int serialdata(byte data);
 
#define pwm1 2
#define pwm2 3
#define dr1 42
#define dr2 43
#define an1 4
#define an2 5
 
/*-----------------------------
*  Function Definations
-------------------------------*/
void serialdata(int data) ;//1
byte createAck(byte ack [], int packet_number_1, int packet_number_2);//2
float bytesToFloat(uchar b0, uchar b1, uchar b2, uchar b3);//3
void stepwise_dr_tu();//4
void move_forward(int mdelay);//5
void move_backward(int mdelay);//6
void turn_left(int mdelay);//7
void turn_right(int mdelay);//8
void stop_m();//9
void motorcontrols();//10
/*-----------------------------
*          SETUP
------------------------------*/
void setup() 
{
  // put your setup code here, to run once:
 
   Serial.begin(115200);
   Serial3.begin(115200);
   pinMode(pwm1,OUTPUT);
   pinMode(pwm2,OUTPUT);
   pinMode(dr1,OUTPUT);
   pinMode(dr2,OUTPUT);
  for (int i = 0; i < packet_size; i++) 
  {
      line[i] = '\0';
  }
}
/*------------------------------
*          LOOP
--------------------------------- */
void loop()
{
  // put your main code here, to run repeatedly:
     // when characters arrive over the serial port...
  if (Serial3.available()) 
  {
    // wait a bit for the entire message to arrive
    delay(100);
    // read all the available characters
    while (Serial3.available() > 0) 
    {
       bytedata = Serial3.read();
       if (newbyte == -1) 
       {
          if (bytedata == 0xA0) 
          {
            datacount = 0;
          }
        if (bytedata == 0xD4) 
        {
          datacount++;
          newbyte = 0;
          break;
        }
      }
      else 
      {
        if (datacount) 
        {
          serialdata(bytedata);
        }
      }
    }
  }
}
void serialdata(int data) 
{
  line[j] = data;
  j++;
  if (j == 63) //line array will not fill, this condition can not be executed
  {
    //////////////////////////////////header assign///////////////
    for (int i = 0; i < 4; i++) //the first 4 bytees are of header
    {
      header[i] = line[i];
    }
    //////////////////////////////////// payload //////////////////////////
    for (int i = 0; i < 4; i++)  /////////////next 4 bytes are of dx////////////
    {
      x[i] = line[i + 4];
      dx[0] = bytesToFloat(x[0], x[1], x[2], x[3]);
    }
    for (k = 0; k < 4; k++) //////////////next 4 byte are of dy////////
    { 
      y[k] = line[k + 8];
      dx[1] = bytesToFloat(y[0], y[1], y[2], y[3]);
    }
    for (k = 0; k < 4; k++) /////////////next 4 byte are of dz////////////////
    { 
        z[k] = line[k + 12];
        dx[2] =  bytesToFloat(z[0], z[1], z[2], z[3]);
    }
    for (k = 0; k < 4; k++) /////////////next 4 byte are of da(heading)////////////////
    { 
        h[k] = line[k + 16];
        dx[3] =  bytesToFloat(h[0], h[1], h[2], h[3]);
    }
    for (k = 0; k < 1; k++) /////////////step count 2 byte////////////////
    { 
      steps[k] = line[k + 61];
    }
    int package_number1 = header[1];
    int package_number2 = header[2];
    //////////////////////////////// Create ack for next step///////////////////////////////
    ack[0] = createAck(ack, package_number1, package_number2); // Acknowledgement created
    ack[1] = createAck(ack, package_number1, package_number2); // Acknowledgement created
    ack[2] = createAck(ack, package_number1, package_number2); // Acknowledgement created
    ack[3] = createAck(ack, package_number1, package_number2); // Acknowledgement created
    ack[4] = createAck(ack, package_number1, package_number2); // Acknowledgement created
    package_number = package_number1 * 256 + package_number2;  //PACKAGE NUMBER ASSIGNED
    if (package_number_old != package_number) {
      stepsw++;
      stepwise_dr_tu();
      package_number_old = package_number;
    }
    motorcontrols();
    j = 0;
  }
}
 
byte createAck(byte ack [], int packet_number_1, int packet_number_2)
{
  ack[0] = 0x01; // 1st byte
  ack[1] = (byte)packet_number_1; // 2nd byte
  ack[2] = (byte)packet_number_2; // 3rd byte
  ack[3] = (byte)((1 + packet_number_1 + packet_number_2 - (1 + packet_number_1 + packet_number_2) % 256) / 256); // 4th byte – Quotient of {(1+P1+P2) div 256}
  ack[4] = (byte)((1 + packet_number_1 + packet_number_2) % 256); // 5th byte- Remainder of {(1+P1+P2)div 256
  return ack[4];
}
 
float bytesToFloat(uchar b0, uchar b1, uchar b2, uchar b3){
  union 
  {
    float f;
    uchar b[4];
  } u;
  u.b[3] = b0;
  u.b[2] = b1;
  u.b[1] = b2;
  u.b[0] = b3;
  return u.f;
}
 
void stepwise_dr_tu()
{
  sin_phi = (float) sin(x_sw[3]);
  cos_phi = (float) cos(x_sw[3]);
  delta[0] = cos_phi * dx[0] - sin_phi * dx[1];
  delta[1] = sin_phi * dx[0] + cos_phi * dx[1];
  delta[2] = dx[2];
  delta[3] += dx[3] * 57.3;
  x_sw[0] += delta[0];
  x_sw[1] += delta[1];
  x_sw[2] += delta[2];
  x_sw[3] += dx[3];
  final_data[0] = x_sw[0];
  final_data[1] = x_sw[1];
  final_data[2] = x_sw[2];
  final_data[3] = delta[3];
  distance1 = sqrt((delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]));//sqrt(x^2+y^2+z^2)
  heading += dx[3] * 57.3; 
  
  if(flag_f)
  {
    track_length += distance1;
    distance += distance1;
    //Serial.print(distance);
  }
  if(flag_b)
  {
    track_length -= distance1;
    distance -= distance1;
  }
}
 
void move_forward(int mdelay){
    digitalWrite(pwm1, HIGH);
    digitalWrite(dr1, LOW);
    digitalWrite(pwm2, HIGH);
    digitalWrite(dr2, LOW);
    analogWrite(an1,140);
    analogWrite(an2,125);
    delay(mdelay);
    Serial.println("forward");
    stop_m();
    flag_f = true;
    flag_b = false;
}
 
void move_backward(int mdelay){
    digitalWrite(pwm1, LOW);
    digitalWrite(dr1, HIGH);
    digitalWrite(pwm2, LOW);
    digitalWrite(dr2, HIGH);
    analogWrite(an1,140);
    analogWrite(an2,125);
    delay(mdelay);
    Serial.println("backward");
    stop_m();
    flag_b = true;
    flag_f = false;
}
 
void turn_left(int mdelay){
    digitalWrite(pwm1, HIGH);
    digitalWrite(dr1, LOW);
    digitalWrite(pwm2, LOW);
    digitalWrite(dr2, HIGH);
    analogWrite(an1,140);
    analogWrite(an2,125);
    Serial.println(heading);
    delay(mdelay);
    Serial.println("left");
    stop_m();
    flag_f = false;
    flag_b = false;
}
 
void turn_right(int mdelay){
    digitalWrite(pwm1, LOW);
    digitalWrite(dr1, HIGH);
    digitalWrite(pwm2, HIGH);
    digitalWrite(dr2, LOW);
    analogWrite(an1,140);
    analogWrite(an2,125);
    Serial.println(heading);
    delay(mdelay);
    Serial.println("right");
    stop_m();
    flag_f = false;
    flag_b = false;
}
 
void stop_m(){
   digitalWrite(pwm1, LOW);
    digitalWrite(dr1, LOW);
    digitalWrite(pwm2, LOW);
    digitalWrite(dr2, LOW);
    analogWrite(an1,0);
    analogWrite(an2,0);
    Serial.println(heading);
    Serial.println("stop");
    //delay(mdelay);
}
 
void motorcontrols() {
   
   bool turn = false;
   float dis_error = 0;
   float theta_error = 0;
   int forw_delay, back_delay = 0;
   int left_delay, right_delay = 0;
   
  track = data_array[nturn];
  theta = (float) data_array[nturn+1];
  if(heading>=360)
  {heading=heading-360;}
  else if(heading<=-360)
  {heading =heading+360;}
 
  double delta_track = fabs(track - track_length);
  float delta_theta = fabs(theta - heading);
  
  //if (nturn==0){
     dis_error = 0.015;
     theta_error = 3;
/* }
  else {
     dis_error = (track * track_error_percent)/200;
     theta_error = (theta * theta_error_percent)/200;
  }
*/
 
  if (delta_track < 0.2)
  {
        forw_delay = 300;
  }
   else if (delta_track >= 0.2 && delta_track < 0.5){
        forw_delay = 500;
  }
  else if (delta_track >= 0.5 && delta_track < 1){
        forw_delay = 600;//700
  }
   else if (delta_track >= 1){
        forw_delay = 700;//800
  }
  back_delay = forw_delay;
  
  if (delta_theta < 15){
        left_delay = 80;
  }
   else if (delta_theta >= 15 && delta_theta < 30){
        left_delay = 140;//140//
  }
  else if (delta_theta >= 30 && delta_track < 60){
        left_delay = 150;//160/
  }
   else if (delta_theta > 60)
  {
        left_delay = 170;//180/
  }
  right_delay = left_delay;
  
  if ((track_length >= (track - dis_error)) && (track_length <= (track + dis_error)))
     turn = true;
  else 
     turn = false;
 
  if (!turn)//if turn=false,i.e,(track_length <= (track - dis_error)) && (track_length >= (track + dis_error)
  {
     if (heading >= 3)//-theta+theta_error
     {
       turn_right(50);
     }
     else if (heading < -3) //theta-theta_error 1.5
     {
       turn_left(50);//40
     }
     else if ((track_length < (track - dis_error)) ) 
     {
       move_forward(forw_delay);
     }
     else if ((track_length >= (track + dis_error))) 
     {
       move_backward(150);//100
     }
  }
  else 
  {
    if(theta == 0)
    {
      stop_m();
      j = 0;
      nturn = 0;
      datacount = 0;
      newbyte = -1;
      delay(5000);
      
    }
    else if (heading < (theta - theta_error)) 
    {
     turn_left(right_delay);
    }
    else if (heading > (theta + theta_error)) 
    {
     turn_right(left_delay);
    }  
    else
    {                                                                                              
     track_length = 0;
     heading = 0;
     nturn=nturn+2;
    }
  }
}
