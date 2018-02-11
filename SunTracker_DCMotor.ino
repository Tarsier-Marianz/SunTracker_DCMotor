#include <AnalogSmooth.h>
AnalogSmooth anagRead = AnalogSmooth();

const int TOL = 0; // steps tolerance
const int VERT_PADDING =10; // vertical padding (40 in indoor testing)
const int HORZ_PADDING =20; // horizontal padding (40 in indoor testing)
const int VERT_MAX_DEGREE =120; // -160+ vertical maximum degree
const int HORZ_MAX_DEGREE =200; // -160+ horizontal maximum degree
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
int horzDegree = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
int vertDegree = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
int vertPadding = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
int horzPadding = 0; 

int sensorTL = A0; //LDR top left
int sensorTR = A1; //LDR top right
int sensorDL = A2; //LDR down left
int sensorDR = A3; //LDR down right

boolean RESET_DEGREE = true; //state of reset degree value if exceed maximum
// motor controller pinouts
//int ENA = 5;
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
//int ENB = 10;

void setup() { 
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //pinMode(ENA, OUTPUT);
  //pinMode(ENB, OUTPUT);
  initialize();
}

void initialize(){  
  
}
void loop() {
  /*
  int lt   = anagRead.smooth(analogRead(sensorTL));
  int rt   = anagRead.smooth(analogRead(sensorTR));
  int ld  = anagRead.smooth(analogRead(sensorDL));
  int rd  = anagRead.smooth(analogRead(sensorDR));
  */

  int lt = analogRead(sensorTL); // top left
  int rt = analogRead(sensorTR); // top right
  int ld = analogRead(sensorDL); // down left
  int rd = analogRead(sensorDR); // down right
 
  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the difference of up and down
  int dhoriz = avl - avr;// check the difference of left and right

  // -0 > dvert > 0
  if (-1 * TOL > dvert || dvert > TOL){
    if (avt > avd){
      setVerticalSteps(true, avt-avd);
    }else if (avt < avd){
      setVerticalSteps(false,avd-avt);
    }else{
      stopMotor(true);
    }
  }
  // -0 > dhorz > 0
  if (-1 * TOL > dhoriz || dhoriz > TOL){
    if (avl > avr){
      setHorizontalSteps(false,avl-avr);
    }else if (avl < avr){
      setHorizontalSteps(true,avr-avl);
    }else if (avl = avr){
      stopMotor(false);
    }  
  }

  Serial.print(vertDegree); Serial.print("\t");
  Serial.print(horzDegree); Serial.print("\t");
  Serial.print("\t");

  Serial.print(lt); Serial.print("\t");
  Serial.print(rt); Serial.print("\t");
  Serial.print(ld); Serial.print("\t");
  Serial.print(rd); Serial.print("\t");
  Serial.print("\t");

  Serial.print(avt); Serial.print("\t");
  Serial.print(avd); Serial.print("\t");
  Serial.print(avl); Serial.print("\t");
  Serial.print(avr); Serial.print("\t"); 
  Serial.print("\t");
  
  Serial.print(vertPadding); Serial.print("\t"); 
  Serial.print(horzPadding); Serial.print("\t"); 
  Serial.println();
  
  //delay(100);
}


void setVerticalSteps(boolean up, int padding){
  vertPadding= padding;
  if(up){    
      vertDegree++;
      if (vertDegree > VERT_MAX_DEGREE){
        vertDegree = VERT_MAX_DEGREE;
       }
  }else{
    vertDegree--;
    if (vertDegree < 0){
      vertDegree = 0;
    }
  }
  if(padding <= VERT_PADDING){
    stopMotor(true);
    //delay(1000);
  }else{
    digitalWrite(IN1, up);
    digitalWrite(IN2, !up);
    delay(14);
  }
}
void setHorizontalSteps(boolean right, int padding){
  horzPadding = padding;
  if(right){    
      horzDegree++;
      if (horzDegree > HORZ_MAX_DEGREE){
        horzDegree = HORZ_MAX_DEGREE;
      }
  }else{
    horzDegree--;
    if (horzDegree < 0){
      horzDegree = 0;
    }
  }
  /*
  if(horzDegree >  HORZ_MAX_DEGREE ){
    right = !right;
    horzDegree= horzDegree * -1;
  }else if(horzDegree < HORZ_MAX_DEGREE*-1){
    right = !right;
    horzDegree= horzDegree * 1;
  }*/
  
  if(padding <= HORZ_PADDING){
    stopMotor(false);
  }else{
    digitalWrite(IN4, right);
    digitalWrite(IN3, !right);
    delay(14);
  }
}

void stopMotor(boolean vertical){
  if(vertical==true){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }else{
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
  }
  if(RESET_DEGREE){
    resetDegree(vertical);
  }
}

void resetDegree(boolean vertical){
  if(vertical==true){
    vertDegree = 0;
  }else{
    horzDegree = 0;
  }
}

