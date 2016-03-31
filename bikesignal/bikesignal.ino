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
// image 
////////////////////////////////////////////////////////

long image0[8] = {
  B11111001,
  B11110001,
  B11100001,
  B11000000,
  B11000000,
  B11100001,
  B11110001,
  B11111001
};

long image1[8] = {
  B11110011,
  B11100011,
  B11000011,
  B10000000,
  B10000000,
  B11000011,
  B11100011,
  B11110011
};

long image2[8] = {
  B11100111,
  B11000111,
  B10000111,
  B00000000,
  B00000000,
  B10000111,
  B11000111,
  B11100111
};

long image3[8] = {
  B11001111,
  B10001111,
  B00001111,
  B00000001,
  B00000001,
  B00001111,
  B10001111,
  B11001111
};



long* leftArrow[4] = {
  image0,
  image1,
  image2,
  image3,
};

int imageSize = (sizeof(image1)/sizeof(long));

void setup() {
  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  displayPixels(50);
}

void displayPixels(long delayTime) {
  for (int i=0; i<sizeof(leftArrow)/sizeof(imageSize); i++) {
    for (int j=0; j<delayTime; j++) {
      for (int k=0; k<imageSize; k++) {
        int offset = k % imageSize;
        long row = B10000000 >> offset;
        long col = leftArrow[i][offset];
        
        shiftOut(dataPin2, clockPin2, LSBFIRST, col);
        digitalWrite(latchPin2, HIGH);
        digitalWrite(latchPin2, LOW);
      
        shiftOut(dataPin1, clockPin1, LSBFIRST, row);
        digitalWrite(latchPin1, HIGH);
        digitalWrite(latchPin1, LOW);
      
        shiftOut(dataPin1, clockPin1, LSBFIRST, 0);
        digitalWrite(latchPin1, HIGH);
        digitalWrite(latchPin1, LOW);
      }
    }
  }
}

