#include <math.h>
const int rot_pinA = 2;//PinA 割り込み0
const int rot_pinB = 3;//PinB 割り込み1
long int rot_count = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(rot_pinA,INPUT);
  pinMode(rot_pinB,INPUT);
  digitalWrite(rot_pinA,HIGH);
  digitalWrite(rot_pinB,HIGH);
  attachInterrupt(0, rotary_changedPinA, CHANGE); //pinAの信号変化に合わせて割り込み処理
  attachInterrupt(1, rotary_changedPinB, CHANGE); //pinBの信号変化に合わせて割り込み処理
}

void loop()
{
  //シリアルコンソールに現在の値を出力する
  Serial.println((((rot_count*M_PI*38)/360)/10/3.81));
}

//rot_countをインクリメント時に上限チェックを行う
void count_inc()
{
   ++rot_count;
}

//rot_countをdecrement時に下限チェックを行う
void count_dec()
{
  --rot_count;
}

//pinAの割り込み処理
void rotary_changedPinA()
{
  if(digitalRead(rot_pinA))
  {
    if(digitalRead(rot_pinB)) count_dec();
    else count_inc();
  } else {
    if(digitalRead(rot_pinB)) count_inc();
    else count_dec();
  }
}

//pinBの割り込み処理
void rotary_changedPinB()
{
  if(digitalRead(rot_pinB))
  {
    if(digitalRead(rot_pinA)) count_inc();
    else count_dec();
  } else {
    if(digitalRead(rot_pinA)) count_dec();
    else count_inc();
  }
}

