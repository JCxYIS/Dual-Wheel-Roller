#include <SoftwareSerial.h>
#include <AFMotor.h> //guide: https://learn.adafruit.com/adafruit-motor-shield/af-dcmotor-class
#include <Servo.h>

SoftwareSerial BT(2, 13); // RX | TX , (2,13) are not used by motor shield
AF_DCMotor motorL(1), motorR(4), motorM(2); //接腳座及頻率
Servo servo;

char command[20];
int commandBuffer = 0;//income command should be written on which pos of command[]?
int speedL = 0, speedR = 0, speedM = 0;
int servoAngle = 0, servoPreAngle = 0;

void setup() 
{
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT(Bluetooth) is ready! type AT to set func:");

  BT.begin(9600);// 設定藍牙模組的連線速率
  servo.attach(10);
  command[0] = ' ';

  motorL.setSpeed(0);    //可調轉速約150~到255
  motorL.run(RELEASE);
  motorR.setSpeed(0);    //可調轉速約150~到255
  motorR.run(RELEASE);
  motorM.setSpeed(0);    //可調轉速約150~到255
  motorM.run(RELEASE);
}

void loop() 
{
  BlueToothHandler();
  MotorMovement(speedL, speedR, speedM);
  ServoBehavior();
}

//這裡處理藍芽事宜
void BlueToothHandler()
{
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) 
  {
    char val = Serial.read();
    BT.print(val);
  }
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」，並加入command。注意結尾一定要是'\n'
  if (BT.available())
  {
    int inSize = BT.available();
    for (int i = 0; i < inSize; i++)
    {
        char tmp = BT.read();
        command[commandBuffer] = tmp;
        if(tmp == '\n')//this command is done
        {
          commandBuffer = 0;
          CommandHandler();
        }
        else
          commandBuffer += 1;
        
        Serial.print(tmp);
    }
 
  }
  

}
//把command轉化為各參數
void CommandHandler()
{
  switch(command[0])
  {
    case ' ':
    break;

    case 'M'://mod Motor speed, 001~255 //EX: M-048+163
      speedL = ((int)command[2]-'0')*100 + ((int)command[3]-'0')*10 + ((int)command[4]-'0');
      speedR = ((int)command[6]-'0')*100 + ((int)command[7]-'0')*10 + ((int)command[8]-'0');
      speedM = ((int)command[10]-'0')*100 + ((int)command[11]-'0')*10 + ((int)command[12]-'0');
      if(command[1] == '-'){speedL *= -1;}
      if(command[5] == '-'){speedR *= -1;}
      if(command[9] == '-'){speedM *= -1;}//
    break;

    case 'S': //set servo angle  //EX: S+152
      servoAngle = ((int)command[2]-'0')*100 + ((int)command[3]-'0')*10 + ((int)command[4]-'0');
      break;
      

    default:
      Serial.println("CommandNotSupportError: Doesn't support this function!");
      break;
  }
  for(int i = 0; i<20; i++)
  {
    command[i] = ' ';
  }
}
//負責馬達
void MotorMovement(int l, int r, int m)
{
  if(l < 0)
  {
    l *= -1;
    motorL.setSpeed(l);
    motorL.run(BACKWARD);
  }
  else if(l > 0)
  {
    motorL.setSpeed(l);
    motorL.run(FORWARD);
  }
  else
  {
    motorL.setSpeed(0);
    motorL.run(RELEASE);
  }
  if(r < 0)
  {
    r *= -1;
    motorR.setSpeed(r);
    motorR.run(BACKWARD);
  }
  else if(r > 0)
  {
    motorR.setSpeed(r);
    motorR.run(FORWARD);
  }
  else
  {
    motorR.setSpeed(0);
    motorR.run(RELEASE);
  }
  if(m < 0)
  {
    m *= -1;
    motorM.setSpeed(m);
    motorM.run(BACKWARD);
  }
  else if(m > 0)
  {
    motorM.setSpeed(m);
    motorM.run(FORWARD);
  }
  else
  {
    motorM.setSpeed(0);
    motorM.run(RELEASE);
  }
  //Serial.print("MOTOR=");Serial.print(l);Serial.print(",");Serial.print(r);Serial.print("\n");
}

void ServoBehavior()
{
  if(servoAngle != servoPreAngle)
  {
    servo.write(servoAngle);
    servoPreAngle = servoAngle;
  }
}




