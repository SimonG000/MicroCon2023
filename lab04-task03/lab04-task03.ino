// Test 3: Photocell PID with setPoint variable
float Kp=0.1, Ki=0, Kd=0;
float error=0, previous_error=0;
float P=0, I=0, D=0;
float PID_value=0;
int setPoint=502;
float initialValue=10;
//bool buttonState;
//bool lastButtonState;

int buttonState;
int lastButtonState;
void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
  analogWrite(3,initialValue);
  Serial.begin(9600);
}
void loop() {
  setPointChange();
  int photoSignal=analogRead(A0);
  error=setPoint-photoSignal;
  P=error;
  I+=error;
  D=error-previous_error;
  previous_error=error;
  PID_value=PID_value+Kp*P+Ki*I+Kd*D; 
  analogWrite(3,PID_value);
  Serial.print(setPoint);
  Serial.print(", "); 
  Serial.println(photoSignal);
}

void setPointChange(){ // state detection (edge detection) works. 
  buttonState=digitalRead(7);
  if (buttonState!=lastButtonState){
    delay(10);
    if (buttonState==HIGH){
      if (setPoint<900){
        setPoint+=20;
      }
    }
  }
  lastButtonState=buttonState;
}




//void setPointChange(){ // button push detection, why this won't work?
//  int setPointPin=digitalRead(4);
//  if (setPointPin==HIGH){
//    delay(10);
//    if (setPointPin==HIGH){
//      if (setPoint<950){
//        setPoint+=10;
//      }
//    }
//  }
//}
