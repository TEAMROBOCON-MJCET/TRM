int f1 = 0,f2=0,f3=0,rot = 0, a = 0, z = 0;
int wael = 0;
int startflag = 1,i;
bool state=LOW;


void tz1()
{                                                                                                                                                             //piston on                       //tz1  //lf1                //tz2                 //tz3              //s1 on
  (digitalRead(2) == HIGH && f1 == 0 && f2 == 0 && f3 == 0) ? (digitalWrite(48,LOW), digitalWrite(50,HIGH), digitalWrite(35, HIGH), analogWrite(5, 127), delay(2000), digitalWrite(38, HIGH), digitalWrite(36, LOW), digitalWrite(34, LOW), digitalWrite(43, HIGH), f1 = 1) : ((digitalRead(2) == LOW && f1 == 1 && f2 == 0 && f3 == 0) ? (f1 = 0) : (0));
}

void tz2()
{                                                                                                              //piston on                                                                      //tz1  //lf1                //tz2                 //tz3              //s2 on
  (digitalRead(3) == HIGH && f2 == 0 && f1 == 0 && f3 == 0) ? (digitalWrite(48,LOW), digitalWrite(50,HIGH), digitalWrite(35, HIGH), analogWrite(5, 127), delay(2000), digitalWrite(38, LOW), digitalWrite(36, HIGH), digitalWrite(34, LOW), digitalWrite(47, HIGH), f2 = 1) : ((digitalRead(3) == LOW && f2 == 1 && f1 == 0 && f3 == 0) ? (f2 = 0) : (0));
}

void tz3()
{                                                                                                                               //piston on                                                     //tz1  //lf1                //tz2                 //tz3              //s3 on
  (digitalRead(19) == HIGH && f3 == 0 && f2 == 0 && f1 == 0) ? (digitalWrite(48, LOW), digitalWrite(50,HIGH), digitalWrite(35, HIGH), analogWrite(5, 127), delay(2000), digitalWrite(38, LOW), digitalWrite(36, LOW), digitalWrite(34, HIGH), digitalWrite(39, HIGH), f3 = 1) : ((digitalRead(19) == LOW && f3 == 1 && f2 == 0 && f1 == 0) ? (f3= 0) : (0));
}

void sensors()
{
  (digitalRead(18) == HIGH && a == 0) ? (rot++, a = 1, Serial.println(rot)) : ((digitalRead(18) == LOW && a == 1) ? (a = 0) : (0)); //count
}

void zainbolre()
{Serial.println("launch");
  (digitalRead(21) == HIGH)? (wael = 1) : (wael = 0);
}

void setup()
{
  startflag = 1;
  Serial.begin(9600);

  pinMode(53, OUTPUT);//Flasher
   pinMode(27, OUTPUT);//Flasher
  
  pinMode(52, OUTPUT);//ristriction piston
  pinMode(46, OUTPUT);
  
  pinMode(48, OUTPUT);//grabbing piston
  pinMode(50, OUTPUT);


  pinMode(49, OUTPUT); //gozain

  pinMode(38, OUTPUT); //tz1/lf1
  pinMode(36, OUTPUT); //tz2/lf2
  pinMode(34, OUTPUT); //tz3/lf3

  pinMode(43, OUTPUT); //s1
  pinMode(47, OUTPUT); //s2
  pinMode(39, OUTPUT); //s3

  pinMode(33, OUTPUT); //launcher motor
  pinMode(6, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(35, OUTPUT);//launcher piston
  pinMode(5, OUTPUT);


  pinMode(21, INPUT); //launch
  pinMode(18, INPUT); //sensors count
  pinMode(2, INPUT); //tz1
  pinMode(3, INPUT); //tz2
  pinMode(19, INPUT); //tz3


  attachInterrupt(digitalPinToInterrupt(2), tz1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), tz2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), tz3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(18), sensors, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), zainbolre, CHANGE);
}

void loop()
{
  
  rot = 0;
  if (startflag == 1)
  {
    delay(5000);
    digitalWrite(33, HIGH); //motor on (SLOW SPEED)
    analogWrite(6, 34);
    digitalWrite(52, HIGH);  //ristriction piston open
  digitalWrite(46, LOW);
   delay(3000);
   analogWrite(6, 0);
     startflag = 0;
  }
  digitalWrite(33, HIGH);  
  
  digitalWrite(52, HIGH);  //ristriction piston open
  digitalWrite(46, LOW);

  digitalWrite(35, LOW);   //launcher piston open
  analogWrite(5, 0);  
       
  digitalWrite(48, LOW);
  digitalWrite(50, LOW);   //grabbing piston open
  
  while (1)
  {
    if (wael == 1)
    {
      if (digitalRead(43) == HIGH && digitalRead(47) == LOW && digitalRead(39) == LOW)
      {
        
        digitalWrite(48, LOW);  // grabbing piston open
        digitalWrite(50, LOW);

        for(i=0;i<9;i++)
       {
        digitalWrite( 53, state);
        digitalWrite( 27, state);
        delay(100);
        state=!state;
       }
       state=LOW;
       digitalWrite( 53, state);
       digitalWrite( 27, state);
       
        digitalWrite(52, LOW);  // ristriction piston open
        digitalWrite(46, LOW);
        delay(200);
        digitalWrite(33, HIGH);
        analogWrite(6, 120);
        z = 1;
        wael = 0;
      }
      else if (digitalRead(43) == LOW && digitalRead(47) == HIGH && digitalRead(39) == LOW)
      {
        digitalWrite(48, LOW);
        digitalWrite(50, LOW);
        
       for(i=0;i<9;i++)
       {
         digitalWrite( 53, state);
         digitalWrite( 27, state);
         delay(100);
         state=!state;
       }
       state=LOW;
       digitalWrite( 53, state);
       digitalWrite( 27, state);
       
        digitalWrite(52, LOW);  // ristriction piston open
        digitalWrite(46, LOW);
        delay(200);
       
        digitalWrite(33, HIGH);
        analogWrite(6, 135);
        z = 1;
        wael = 0;
      }
      else if (digitalRead(43) == LOW && digitalRead(47) == LOW && digitalRead(39) == HIGH)
      {
        digitalWrite(48, LOW);
        digitalWrite(50, LOW);
       
        for(i=0;i<9;i++)
       {
        digitalWrite(53, state);
        digitalWrite( 27, state);
        delay(100);
        state=!state;
       }
       state=LOW;
       digitalWrite( 53, state);
       digitalWrite( 27, state);
        
        digitalWrite(52, LOW);  // ristriction piston open
        digitalWrite(46, LOW);
        delay(200);
        
        digitalWrite(33, HIGH);
        analogWrite(6, 145);
        z = 1;
        wael = 0;
      }
    }
    Serial.println(rot);

    if (rot == 2)
     
    {
      Serial.println(rot);
      digitalWrite(35, LOW); //piston open
      analogWrite(5, 0);    //piston open
      
      delay(100);
      analogWrite(6, 0);    //motor off

      digitalWrite(43, LOW);//sensors
      digitalWrite(47, LOW);
      digitalWrite(39, LOW);
      
      digitalWrite(38, LOW); //tz's
      digitalWrite(36, LOW);
      digitalWrite(34, LOW);
      
      digitalWrite(49, HIGH); //gozain   previously 51
       
       digitalWrite(52, LOW); //ristriction piston close
       digitalWrite(46, LOW); 

      digitalWrite(48, LOW);  //grabbing piston close
      digitalWrite(50, LOW); 
      rot = 0;
      a = 0;
      z = 0;
      f1 = 0;
      f2=0;
      f3=0;
  delay(2000);
  digitalWrite(52, HIGH); //ristriction piston open
  digitalWrite(46, LOW);  
  delay(1000);
  digitalWrite(33, HIGH); //launcher motor (SLOW SPEED)
  analogWrite(6, 34);
  delay(4000);
  digitalWrite(33, HIGH);
  analogWrite(6, 0);
      break;
    }
  }
  rot = 0;
  digitalWrite(49, LOW);  //gozain232

  //launchreset();

}

void launchreset()
{
  digitalWrite(52, HIGH); //ristriction piston open
  digitalWrite(46, LOW);
  delay(1000);
  digitalWrite(33, HIGH); //launcher motor (SLOW SPEED)
  analogWrite(6, 34);
  delay(4000);
  digitalWrite(33, HIGH);
  analogWrite(6, 0);
}

