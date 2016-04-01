////////////////////////////////////////////////////////
// WRITTEN BY NICOLAS TRUONG
// Arduino bike turning signalization project
////////////////////////////////////////////////////////

//Rows
//Pin connected to ST_CP of 74HC595(1)
int latchPin1 = 13;
//Pin connected to SH_CP of 74HC595(1)
int clockPin1 = 12;
////Pin connected to DS of 74HC595(1)
int dataPin1 = 11;

////////////////////////////////////////////////////////
//Columns
//Pin connected to ST_CP of 74HC595(2)
int latchPin2 = 9;
//Pin connected to SH_CP of 74HC595(2)
int clockPin2 = 8;
////Pin connected to DS of 74HC595(2)
int dataPin2 = 7;

////////////////////////////////////////////////////////
// IMAGES
////////////////////////////////////////////////////////

long arrow0[8] = {
  B11111001,
  B11110001,
  B11100001,
  B11000000,
  B11000000,
  B11100001,
  B11110001,
  B11111001
};

long arrow1[8] = {
  B11110011,
  B11100011,
  B11000011,
  B10000000,
  B10000000,
  B11000011,
  B11100011,
  B11110011
};

long arrow2[8] = {
  B11100111,
  B11000111,
  B10000111,
  B00000000,
  B00000000,
  B10000111,
  B11000111,
  B11100111
};

long arrow3[8] = {
  B11001111,
  B10001111,
  B00001111,
  B00000001,
  B00000001,
  B00001111,
  B10001111,
  B11001111
};

long* arrow[4] = {
  arrow0,
  arrow1,
  arrow2,
  arrow3,
};

long stop0[8] = {
  B11000011,
  B10000001,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000001,
  B11000011,
};

long stop1[8] = {
  B11000011,
  B11000011,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B11000011,
  B11000011,
};

long* stop[4] = {
  stop0,
  stop1,
  stop0,
  stop1
};

////////////////////////////////////////////////////////
// CONSTANTS
////////////////////////////////////////////////////////
#define IMAGE_SIZE 8
#define ANIMATION_SIZE 4
#define LEFT 0
#define RIGHT 1

const int  leftButtonPin = 2;
const int  rightButtonPin = 4;
////////////////////////////////////////////////////////

int leftButtonState = 0;
int leftLastButtonState = 0;

int rightButtonState = 0;
int rightLastButtonState = 0;

void setup() {
  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);

  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);

  Serial.begin(9600); 
}

void loop() {
  button();
}

void button() {
  leftButtonState = digitalRead(leftButtonPin);
  rightButtonState = digitalRead(rightButtonPin);

  if (leftButtonState != leftLastButtonState || rightButtonState != rightLastButtonState) {

    while (leftButtonState == HIGH && rightButtonState == HIGH) {
      
      displayAnimation(40, stop, LEFT);
      
      leftButtonState = digitalRead(leftButtonPin);
      rightButtonState = digitalRead(rightButtonPin);
    }
    
    while (leftButtonState == HIGH && rightButtonState == LOW) {  
      
      displayAnimation(40, arrow, LEFT);
      
      leftButtonState = digitalRead(leftButtonPin);
      rightButtonState = digitalRead(rightButtonPin);
    }
    
    while (rightButtonState == HIGH && leftButtonState == LOW) {
 
      displayAnimation(40, arrow, RIGHT);
      
      rightButtonState = digitalRead(rightButtonPin);
      leftButtonState = digitalRead(leftButtonPin);
    }
  }

  leftLastButtonState = leftButtonState;
  rightLastButtonState = rightButtonState;
}

void displayAnimation(long delayTime, long** animation, int side) {
  
  uint8_t order;
  
  if (side == LEFT) {
    order = LSBFIRST;
  }else{
    order = MSBFIRST;
  }

  for (int i=0; i<ANIMATION_SIZE; i++) {
    for (int j=0; j<delayTime; j++) {
      for (int k=0; k<IMAGE_SIZE; k++) {
        int offset = k % IMAGE_SIZE;
        long row = B10000000 >> offset;
        long col = animation[i][offset];
        
        shiftOut(dataPin2, clockPin2, order, col);
        digitalWrite(latchPin2, HIGH);
        digitalWrite(latchPin2, LOW);
      
        shiftOut(dataPin1, clockPin1, order, row);
        digitalWrite(latchPin1, HIGH);
        digitalWrite(latchPin1, LOW);
      
        shiftOut(dataPin1, clockPin1, order, 0);
        digitalWrite(latchPin1, HIGH);
        digitalWrite(latchPin1, LOW);
      }
    }
  }
}

